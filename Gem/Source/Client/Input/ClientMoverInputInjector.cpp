
#if !AZ_TRAIT_CLIENT
#error "This file assumes it's being used for client code."
#endif // #if !AZ_TRAIT_CLIENT

#include <Source/Client/Input/ClientMoverInputInjector.h>

#include <xXGameProjectNameXx/Client/InputEventNames.h>
#include <xXGameProjectNameXx/MoverNetworkInputInterface.h>
#include <Multiplayer/Components/NetBindComponent.h>
#include <AzCore/Console/ILogger.h>
#include <AzCore/Debug/Trace.h>
#include <O3deUtils_Misc/MultiplayerUtils.h>

namespace
{
    // @Christian: TODO: [todo][techdebt][log] There might be a better way to control logs than this. The `AZLOG` macro does
    // have a tag you can specify, but it's disabled by default and I don't know how to enable them easily. But try to see
    // if we can use log tags rather than console variables like this. Also, one thing that's weird is that the `AZLOG` macro
    // doesn't let you specify the log level (info, warning, error, etc.).
    AZ_CVAR(bool, cl_xxgpnxx_moverInput_enableClientInputEventLogs, false, nullptr, AZ::ConsoleFunctorFlags::Null, "Enables logs for client-side input events.");

    void LogInputEvent(
        const AZStd::string_view& funcName,
        const AZStd::string_view& inputEventName,
        const float value);
}

namespace xXGameProjectNameXx
{
    ClientMoverInputInjector::ClientMoverInputInjector(const AZ::Component& parentComponent)
        : m_parentComponent(parentComponent)
    {
    }

    void ClientMoverInputInjector::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        constexpr AZ::Crc32 netBindService = AZ_CRC_CE("NetBindService");
        // Require the `MoverNetworkInputComponent`, as that is the component we will inject values into.
        constexpr AZ::Crc32 moverNetworkInputComponentService = AZ_CRC_CE("MoverNetworkInputComponent");

        // Add them, if not already.

        if (AZStd::find(required.begin(), required.end(), netBindService) == required.end())
        {
            required.push_back(netBindService);
        }

        if (AZStd::find(required.begin(), required.end(), moverNetworkInputComponentService) == required.end())
        {
            required.push_back(moverNetworkInputComponentService);
        }
    }

    void ClientMoverInputInjector::GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        constexpr AZ::Crc32 netBindService = AZ_CRC_CE("NetBindService");

        // Add them, if not already.

        if (AZStd::find(dependent.begin(), dependent.end(), netBindService) == dependent.end())
        {
            dependent.push_back(netBindService);
        }
    }

    void ClientMoverInputInjector::OnActivate()
    {
        if (O3deUtils::Misc::MultiplayerUtils::GetNetBindComponentAsserted(m_parentComponent).IsNetEntityRoleAutonomous())
        {
            // @Christian: TODO: [todo][techdebt][local_multiplayer] Actually get the local user id of the player that owns
            // this component. Important for supporting local multiplayer / splitscreen.
            const AzFramework::LocalUserId& localUserId = AzFramework::LocalUserIdAny;

            m_moveForwardAxisNotificationId =
                StartingPointInput::InputEventNotificationId(
                    localUserId,
                    AZ::Crc32(InputEventNames::MoveForwardAxis)
                );

            m_moveRightAxisNotificationId =
                StartingPointInput::InputEventNotificationId(
                    localUserId,
                    AZ::Crc32(InputEventNames::MoveRightAxis)
                );

            StartingPointInput::InputEventNotificationBus::MultiHandler::BusConnect(m_moveForwardAxisNotificationId);
            StartingPointInput::InputEventNotificationBus::MultiHandler::BusConnect(m_moveRightAxisNotificationId);
        }
    }

    void ClientMoverInputInjector::OnDeactivate()
    {
        if (O3deUtils::Misc::MultiplayerUtils::GetNetBindComponentAsserted(m_parentComponent).IsNetEntityRoleAutonomous())
        {
            StartingPointInput::InputEventNotificationBus::MultiHandler::BusDisconnect();

            m_moveForwardAxisNotificationId = {};
            m_moveRightAxisNotificationId = {};
        }
    }

    void ClientMoverInputInjector::OnPressed(float value)
    {
        const StartingPointInput::InputEventNotificationId* currentBusIdPtr = StartingPointInput::InputEventNotificationBus::GetCurrentBusId();
        AZ_Assert(currentBusIdPtr, "We, as a multi handler, expect to have a current bus id.");
        const StartingPointInput::InputEventNotificationId& currentBusId = *currentBusIdPtr;

        AZStd::string_view eventNameString;

        if (currentBusId == m_moveForwardAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveForwardAxis;

            MoverNetworkInputRequestFunctions::SetMoveForwardAxis(m_parentComponent.GetEntityId(), value);
        }
        else if (currentBusId == m_moveRightAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveRightAxis;

            MoverNetworkInputRequestFunctions::SetMoveRightAxis(m_parentComponent.GetEntityId(), value);
        }

        if (cl_xxgpnxx_moverInput_enableClientInputEventLogs)
        {
            LogInputEvent(__func__, eventNameString, value);
        }
    }

    void ClientMoverInputInjector::OnHeld(float value)
    {
        const StartingPointInput::InputEventNotificationId* currentBusIdPtr = StartingPointInput::InputEventNotificationBus::GetCurrentBusId();
        AZ_Assert(currentBusIdPtr, "We, as a multi handler, expect to have a current bus id.");
        const StartingPointInput::InputEventNotificationId& currentBusId = *currentBusIdPtr;

        AZStd::string_view eventNameString;

        if (currentBusId == m_moveForwardAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveForwardAxis;

            MoverNetworkInputRequestFunctions::SetMoveForwardAxis(m_parentComponent.GetEntityId(), value);
        }
        else if (currentBusId == m_moveRightAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveRightAxis;

            MoverNetworkInputRequestFunctions::SetMoveRightAxis(m_parentComponent.GetEntityId(), value);
        }

        if (cl_xxgpnxx_moverInput_enableClientInputEventLogs)
        {
            LogInputEvent(__func__, eventNameString, value);
        }
    }

    void ClientMoverInputInjector::OnReleased(float value)
    {
        const StartingPointInput::InputEventNotificationId* currentBusIdPtr = StartingPointInput::InputEventNotificationBus::GetCurrentBusId();
        AZ_Assert(currentBusIdPtr, "We, as a multi handler, expect to have a current bus id.");
        const StartingPointInput::InputEventNotificationId& currentBusId = *currentBusIdPtr;

        AZStd::string_view eventNameString;

        if (currentBusId == m_moveForwardAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveForwardAxis;

            MoverNetworkInputRequestFunctions::SetMoveForwardAxis(m_parentComponent.GetEntityId(), value);
        }
        else if (currentBusId == m_moveRightAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveRightAxis;

            MoverNetworkInputRequestFunctions::SetMoveRightAxis(m_parentComponent.GetEntityId(), value);
        }

        if (cl_xxgpnxx_moverInput_enableClientInputEventLogs)
        {
            LogInputEvent(__func__, eventNameString, value);
        }
    }
} // namespace xXGameProjectNameXx

namespace
{
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
}
