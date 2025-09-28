
#include <Source/Components/ClientMoverInputInjectorComponent.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <xXGameProjectNameXx/InputEventNames.h>
#include <xXGameProjectNameXx/MoverInputInterface.h>
#include <Multiplayer/IMultiplayer.h>
#include <Multiplayer/Components/NetBindComponent.h>

namespace
{
    // @Christian: TODO: [todo][techdebt][log] There might be a better way to control logs than this. The `AZLOG` macro does
    // have a tag you can specify, but it's disabled by default and I don't know how to enable them easily. But try to see
    // if we can use log tags rather than console variables like this. Also, one thing that's weird is that the `AZLOG` macro
    // doesn't let you specify the log level (info, warning, error, etc.).
    AZ_CVAR(bool, cl_xxgpnxx_moverInput_enableClientInputEventLogs, false, nullptr, AZ::ConsoleFunctorFlags::Null, "Enables logs for client-side input events.");

#if AZ_TRAIT_CLIENT
    void LogInputEvent(
        const AZStd::string_view& funcName,
        const AZStd::string_view& inputEventName,
        const float value);
#endif // #if AZ_TRAIT_CLIENT

    Multiplayer::NetBindComponent& GetNetBindComponentAsserted(const AZ::Component& component);
}

namespace xXGameProjectNameXx
{
    AZ_COMPONENT_IMPL(ClientMoverInputInjectorComponent, "ClientMoverInputInjectorComponent", "{3D1A880A-98A2-474D-8A9A-541C135146B6}");

    void ClientMoverInputInjectorComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<ClientMoverInputInjectorComponent, AZ::Component>()
                ->Version(1)
                ;

            if (AZ::EditContext* editContext = serializeContext->GetEditContext())
            {
                editContext->Class<ClientMoverInputInjectorComponent>("ClientMoverInputInjectorComponent", "[Description of functionality provided by this component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Category, "ComponentCategory")
                    ->Attribute(AZ::Edit::Attributes::Icon, "Icons/Components/Component_Placeholder.svg")
                    ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC_CE("Game"))
                    ;
            }
        }

        if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->Class<ClientMoverInputInjectorComponent>("ClientMoverInputInjector Component Group")
                ->Attribute(AZ::Script::Attributes::Category, "xXGameProjectNameXx Gem Group")
                ;
        }
    }

    void ClientMoverInputInjectorComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("ClientMoverInputInjectorComponentService"));
    }

    void ClientMoverInputInjectorComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("ClientMoverInputInjectorComponentService"));
    }

    void ClientMoverInputInjectorComponent::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        required.push_back(AZ_CRC_CE("NetBindService"));
        required.push_back(AZ_CRC_CE("MoverInputComponent"));
    }

    void ClientMoverInputInjectorComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        dependent.push_back(AZ_CRC_CE("NetBindService"));
    }

    void ClientMoverInputInjectorComponent::Activate()
    {
#if AZ_TRAIT_CLIENT
        // TODO: [todo] Listen servers always fail this on first activation, and they don't get reactivated when host autonomy becomes
        // enabled. The only way to get an event for when this happens is by making this a multiplayer component and moving this
        // logic to the `OnActivate` override. I wonder if we can generalize this, to avoid making this a multiplayer component unnecessarily. Or
        // maybe input logic should be in a multiplayer controller class anyway, though, it's only for local-only input events - completely unnetworked.
        if (GetNetBindComponentAsserted(*this).IsNetEntityRoleAutonomous())
        {
            // @Christian: TODO: [todo][techdebt][local_multiplayer] Actually get the local user id of the player that owns
            // this component. Important for supporting local multiplayer / splitscreen.
            const AzFramework::LocalUserId& localUserId = AzFramework::LocalUserIdAny;

            MoveForwardAxisNotificationId =
                StartingPointInput::InputEventNotificationId(
                    localUserId,
                    AZ::Crc32(InputEventNames::MoveForwardAxis)
                );

            MoveRightAxisNotificationId =
                StartingPointInput::InputEventNotificationId(
                    localUserId,
                    AZ::Crc32(InputEventNames::MoveRightAxis)
                );

            StartingPointInput::InputEventNotificationBus::MultiHandler::BusConnect(MoveForwardAxisNotificationId);
            StartingPointInput::InputEventNotificationBus::MultiHandler::BusConnect(MoveRightAxisNotificationId);
        }
#endif // #if AZ_TRAIT_CLIENT
    }

    void ClientMoverInputInjectorComponent::Deactivate()
    {
#if AZ_TRAIT_CLIENT
        if (GetNetBindComponentAsserted(*this).IsNetEntityRoleAutonomous())
        {
            StartingPointInput::InputEventNotificationBus::MultiHandler::BusDisconnect();

            MoveForwardAxisNotificationId = {};
            MoveRightAxisNotificationId = {};
        }
#endif // #if AZ_TRAIT_CLIENT
    }

#if AZ_TRAIT_CLIENT
    void ClientMoverInputInjectorComponent::OnPressed([[maybe_unused]] float value)
    {
        const StartingPointInput::InputEventNotificationId* currentBusIdPtr = StartingPointInput::InputEventNotificationBus::GetCurrentBusId();
        AZ_Assert(currentBusIdPtr, "We, as a multi handler, expect to have a current bus id.");
        const StartingPointInput::InputEventNotificationId& currentBusId = *currentBusIdPtr;

        AZStd::string_view eventNameString;

        if (currentBusId == MoveForwardAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveForwardAxis;

            MoverInputRequestFunctions::SetMoveForwardAxisAutonomousInput(GetEntityId(), value);
        }
        else if (currentBusId == MoveRightAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveRightAxis;

            MoverInputRequestFunctions::SetMoveRightAxisAutonomousInput(GetEntityId(), value);
        }

        if (cl_xxgpnxx_moverInput_enableClientInputEventLogs)
        {
            LogInputEvent(__func__, eventNameString, value);
        }
    }
#endif // #if AZ_TRAIT_CLIENT

#if AZ_TRAIT_CLIENT
    void ClientMoverInputInjectorComponent::OnHeld([[maybe_unused]] float value)
    {
        const StartingPointInput::InputEventNotificationId* currentBusIdPtr = StartingPointInput::InputEventNotificationBus::GetCurrentBusId();
        AZ_Assert(currentBusIdPtr, "We, as a multi handler, expect to have a current bus id.");
        const StartingPointInput::InputEventNotificationId& currentBusId = *currentBusIdPtr;

        AZStd::string_view eventNameString;

        if (currentBusId == MoveForwardAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveForwardAxis;

            MoverInputRequestFunctions::SetMoveForwardAxisAutonomousInput(GetEntityId(), value);
        }
        else if (currentBusId == MoveRightAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveRightAxis;

            MoverInputRequestFunctions::SetMoveRightAxisAutonomousInput(GetEntityId(), value);
        }

        if (cl_xxgpnxx_moverInput_enableClientInputEventLogs)
        {
            LogInputEvent(__func__, eventNameString, value);
        }
    }
#endif // #if AZ_TRAIT_CLIENT

#if AZ_TRAIT_CLIENT
    void ClientMoverInputInjectorComponent::OnReleased([[maybe_unused]] float value)
    {
        const StartingPointInput::InputEventNotificationId* currentBusIdPtr = StartingPointInput::InputEventNotificationBus::GetCurrentBusId();
        AZ_Assert(currentBusIdPtr, "We, as a multi handler, expect to have a current bus id.");
        const StartingPointInput::InputEventNotificationId& currentBusId = *currentBusIdPtr;

        AZStd::string_view eventNameString;

        if (currentBusId == MoveForwardAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveForwardAxis;

            MoverInputRequestFunctions::SetMoveForwardAxisAutonomousInput(GetEntityId(), value);
        }
        else if (currentBusId == MoveRightAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveRightAxis;

            MoverInputRequestFunctions::SetMoveRightAxisAutonomousInput(GetEntityId(), value);
        }

        if (cl_xxgpnxx_moverInput_enableClientInputEventLogs)
        {
            LogInputEvent(__func__, eventNameString, value);
        }
    }
#endif // #if AZ_TRAIT_CLIENT
} // namespace xXGameProjectNameXx

namespace
{
#if AZ_TRAIT_CLIENT
    void LogInputEvent(
        const AZStd::string_view& funcName,
        const AZStd::string_view& inputEventName,
        const float value)
    {
        AZStd::fixed_string<128> logString;

        logString += funcName;
        logString += " for '";
        logString += inputEventName;
        logString += "' with value '";

        {
            AZStd::fixed_string<32> valueString;
            AZStd::to_string(valueString, value);

            logString += valueString;
        }

        logString += "'.";

        AZLOG_INFO(logString.data());
    }
#endif // #if AZ_TRAIT_CLIENT

    Multiplayer::NetBindComponent& GetNetBindComponentAsserted(const AZ::Component& component)
    {
        const Multiplayer::INetworkEntityManager* networkEntityManagerPtr = Multiplayer::GetNetworkEntityManager();
        AZ_Assert(networkEntityManagerPtr, "This should always exist at this time.");
        const Multiplayer::INetworkEntityManager& networkEntityManager = *networkEntityManagerPtr;

        const Multiplayer::NetEntityId& netEntityId = networkEntityManager.GetNetEntityIdById(component.GetEntityId());
        const Multiplayer::ConstNetworkEntityHandle& netEntityHandle = networkEntityManager.GetEntity(netEntityId);

        Multiplayer::NetBindComponent* netBindComponentPtr = netEntityHandle.GetNetBindComponent();
        AZ_Assert(netBindComponentPtr, "This component is required and will always exist.");
        Multiplayer::NetBindComponent& netBindComponent = *netBindComponentPtr;

        return netBindComponent;
    }
}
