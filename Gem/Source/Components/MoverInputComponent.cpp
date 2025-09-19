
#include <Source/Components/MoverInputComponent.h>

namespace
{
#if AZ_TRAIT_CLIENT
    void LogInputEvent(
        const AZStd::string_view& funcName,
        const AZStd::string_view& inputEventName,
        const float value);
#endif // #if AZ_TRAIT_CLIENT
}

namespace xXGameProjectNameXx
{
    MoverInputComponentController::MoverInputComponentController(MoverInputComponent& parent)
        : MoverInputComponentControllerBase(parent)
    {
    }

    void MoverInputComponentController::OnActivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
#if AZ_TRAIT_CLIENT
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

        if (IsNetEntityRoleAutonomous())
        {
            StartingPointInput::InputEventNotificationBus::MultiHandler::BusConnect(MoveForwardAxisNotificationId);
            StartingPointInput::InputEventNotificationBus::MultiHandler::BusConnect(MoveRightAxisNotificationId);
        }
#endif // #if AZ_TRAIT_CLIENT
    }

    void MoverInputComponentController::OnDeactivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
#if AZ_TRAIT_CLIENT
        if (IsNetEntityRoleAutonomous())
        {
            StartingPointInput::InputEventNotificationBus::MultiHandler::BusDisconnect();
        }

        MoveForwardAxisNotificationId = {};
        MoveRightAxisNotificationId = {};
#endif // #if AZ_TRAIT_CLIENT
    }

#if AZ_TRAIT_CLIENT
    void MoverInputComponentController::OnPressed([[maybe_unused]] float value)
    {
        const StartingPointInput::InputEventNotificationId* currentBusIdPtr = StartingPointInput::InputEventNotificationBus::GetCurrentBusId();
        AZ_Assert(currentBusIdPtr, "We, as a multi handler, expect to have a current bus id.");
        const StartingPointInput::InputEventNotificationId& currentBusId = *currentBusIdPtr;

        AZStd::string_view eventNameString;

        if (currentBusId == MoveForwardAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveForwardAxis;
        }
        else if (currentBusId == MoveRightAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveRightAxis;
        }

        LogInputEvent(__func__, eventNameString, value);
    }
#endif // #if AZ_TRAIT_CLIENT

#if AZ_TRAIT_CLIENT
    void MoverInputComponentController::OnHeld([[maybe_unused]] float value)
    {
        const StartingPointInput::InputEventNotificationId* currentBusIdPtr = StartingPointInput::InputEventNotificationBus::GetCurrentBusId();
        AZ_Assert(currentBusIdPtr, "We, as a multi handler, expect to have a current bus id.");
        const StartingPointInput::InputEventNotificationId& currentBusId = *currentBusIdPtr;

        AZStd::string_view eventNameString;

        if (currentBusId == MoveForwardAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveForwardAxis;
        }
        else if (currentBusId == MoveRightAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveRightAxis;
        }

        LogInputEvent(__func__, eventNameString, value);
    }
#endif // #if AZ_TRAIT_CLIENT

#if AZ_TRAIT_CLIENT
    void MoverInputComponentController::OnReleased([[maybe_unused]] float value)
    {
        const StartingPointInput::InputEventNotificationId* currentBusIdPtr = StartingPointInput::InputEventNotificationBus::GetCurrentBusId();
        AZ_Assert(currentBusIdPtr, "We, as a multi handler, expect to have a current bus id.");
        const StartingPointInput::InputEventNotificationId& currentBusId = *currentBusIdPtr;

        AZStd::string_view eventNameString;

        if (currentBusId == MoveForwardAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveForwardAxis;
        }
        else if (currentBusId == MoveRightAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveRightAxis;
        }

        LogInputEvent(__func__, eventNameString, value);
    }
#endif // #if AZ_TRAIT_CLIENT
}

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
}
