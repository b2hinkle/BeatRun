
#include <Source/Components/MoverComponent.h>

#include <Multiplayer/Components/NetworkCharacterComponent.h>
#include <AzCore/Debug/Trace.h>
#include <Source/Utils/AzCoreUtils.h>
#include <Source/Utils/AzCoreUtils.inl>

namespace
{
    // @Christian: TODO: [todo][techdebt][log] There might be a better way to control logs than this. The `AZLOG` macro does
    // have a tag you can specify, but it's disabled by default and I don't know how to enable them easily. But try to see
    // if we can use log tags rather than console variables like this. Also, one thing that's weird is that the `AZLOG` macro
    // doesn't let you specify the log level (info, warning, error, etc.).
    AZ_CVAR(bool, xxgpnxx_moverComponent_enableInputLogs, false, nullptr, AZ::ConsoleFunctorFlags::Null, "Enables logs for local gameplay input values whenever ticked.");
}

namespace xXGameProjectNameXx
{
    AZ_COMPONENT_IMPL(MoverComponent, "MoverComponent", "{C17F271D-5183-4059-B966-F5E1185E7269}");

    void MoverComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<MoverComponent, AZ::Component>()
                ->Version(1)
                ;

            if (AZ::EditContext* editContext = serializeContext->GetEditContext())
            {
                editContext->Class<MoverComponent>("MoverComponent", "[Description of functionality provided by this component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Category, "ComponentCategory")
                    ->Attribute(AZ::Edit::Attributes::Icon, "Icons/Components/Component_Placeholder.svg")
                    ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC_CE("Game"))
                    ;
            }
        }
    }

    void MoverComponent::GetProvidedServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
    }

    void MoverComponent::GetIncompatibleServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
    }

    void MoverComponent::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        required.push_back(AZ_CRC_CE("NetworkCharacterComponent"));
    }

    void MoverComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    void MoverComponent::Activate()
    {
        MoverRequestBus::Handler::BusConnect(GetEntityId());
    }

    void MoverComponent::Deactivate()
    {
        MoverRequestBus::Handler::BusDisconnect(GetEntityId());
    }

    void MoverComponent::TickGameplay(float deltaTime) const
    {
        // Log current net input values.
        if (xxgpnxx_moverComponent_enableInputLogs)
        {
            AZStd::fixed_string<128> logString;

            logString += __func__;
            logString += " executing. `m_localGameplayInputs.m_moveForwardAxis`: '";

            {
                AZStd::fixed_string<32> valueString;
                AZStd::to_string(valueString, m_localGameplayInputs.m_moveForwardAxis);

                logString += valueString;
            }

            logString += "'. `m_localGameplayInputs.m_moveRightAxis`: '";

            {
                AZStd::fixed_string<32> valueString;
                AZStd::to_string(valueString, m_localGameplayInputs.m_moveRightAxis);

                logString += valueString;
            }

            logString += "'.";

            AZLOG_INFO(logString.data());
        }

        // Now, actually move the entity.

        AZ::Vector2 netMoveAxisInputVector = AZ::Vector2(m_localGameplayInputs.m_moveRightAxis, m_localGameplayInputs.m_moveForwardAxis);
        constexpr float maxMoveSpeed = 4.f;

        AZ::Vector3 velocity = AZ::Vector3(netMoveAxisInputVector.GetNormalizedSafe(), 0.f) * maxMoveSpeed;

        GetNetworkCharacterComponentControllerAsserted().TryMoveWithVelocity(velocity, deltaTime);
    }

    float MoverComponent::GetMoveForwardAxis() const
    {
        return m_localGameplayInputs.m_moveForwardAxis;
    }

    float MoverComponent::GetMoveRightAxis() const
    {
        return m_localGameplayInputs.m_moveRightAxis;
    }

    void MoverComponent::SetMoveForwardAxis(float newValue)
    {
        m_localGameplayInputs.m_moveForwardAxis = newValue;
    }

    void MoverComponent::SetMoveRightAxis(float newValue)
    {
        m_localGameplayInputs.m_moveRightAxis = newValue;
    }

    Multiplayer::NetworkCharacterComponentController& MoverComponent::GetNetworkCharacterComponentControllerAsserted() const
    {
        const AZ::Entity* entityPtr = GetEntity();
        AZ_Assert(entityPtr, "");
        const AZ::Entity& entity = *entityPtr;

        Multiplayer::MultiplayerController* controllerPtr =
            AzCoreUtils::FindComponent<Multiplayer::NetworkCharacterComponent&>(entity).GetController();
        AZ_Assert(controllerPtr, "");
        Multiplayer::MultiplayerController& controller = *controllerPtr;

        // TODO: Assert static cast with dynamic cast result.
        return static_cast<Multiplayer::NetworkCharacterComponentController&>(controller);
    }
}
