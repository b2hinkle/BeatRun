
#include <Source/Components/MoverInputComponent.h>

#if AZ_TRAIT_CLIENT
#include <xXGameProjectNameXx/InputEventNames.h>
#endif // #if AZ_TRAIT_CLIENT
#include <Multiplayer/Components/NetworkCharacterComponent.h>

namespace
{
    // @Christian: TODO: [todo][techdebt][log] There might be a better way to control logs than this. The `AZLOG` macro does
    // have a tag you can specify, but it's disabled by default and I don't know how to enable them easily. But try to see
    // if we can use log tags rather than console variables like this. Also, one thing that's weird is that the `AZLOG` macro
    // doesn't let you specify the log level (info, warning, error, etc.).
    AZ_CVAR(bool, cl_xxgpnxx_moverInput_enableClientInputEventLogs, false, nullptr, AZ::ConsoleFunctorFlags::Null, "Enables logs for client-side input events.");
    AZ_CVAR(bool, cl_xxgpnxx_moverInput_enableProcessInputLogs, false, nullptr, AZ::ConsoleFunctorFlags::Null, "Enables logs for the ProcessInput event.");

#if AZ_TRAIT_CLIENT
    void LogInputEvent(
        const AZStd::string_view& funcName,
        const AZStd::string_view& inputEventName,
        const float value);
#endif // #if AZ_TRAIT_CLIENT
}

namespace xXGameProjectNameXx
{
    void MoverInputComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<MoverInputComponent, MoverInputComponentBase>()
                ->Version(1);
        }

        MoverInputComponentBase::Reflect(context);
    }

    void MoverInputComponent::OnActivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
    }

    void MoverInputComponent::OnDeactivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
    }

    MoverInputComponentController::MoverInputComponentController(MoverInputComponent& parent)
        : MoverInputComponentControllerBase(parent)
    {
    }

    void MoverInputComponentController::OnActivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
#if AZ_TRAIT_CLIENT
        if (IsNetEntityRoleAutonomous())
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

    void MoverInputComponentController::OnDeactivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
#if AZ_TRAIT_CLIENT
        if (IsNetEntityRoleAutonomous())
        {
            StartingPointInput::InputEventNotificationBus::MultiHandler::BusDisconnect();

            MoveForwardAxisNotificationId = {};
            MoveRightAxisNotificationId = {};
        }
#endif // #if AZ_TRAIT_CLIENT
    }

    void MoverInputComponentController::CreateInput(Multiplayer::NetworkInput& input, float deltaTime)
    {
        MoverInputComponentControllerBase::CreateInput(input, deltaTime);

        MoverInputComponentNetworkInput* moverNetworkInputPtr = input.FindComponentInput<MoverInputComponentNetworkInput>();
        AZ_Assert(moverNetworkInputPtr, "Network input for our own component will always exist.");
        MoverInputComponentNetworkInput& moverNetworkInput = *moverNetworkInputPtr;

        moverNetworkInput.m_moveForwardAxis = m_autonomousInputs.m_moveForwardAxis;
        moverNetworkInput.m_moveRightAxis = m_autonomousInputs.m_moveRightAxis;
    }

    void MoverInputComponentController::ProcessInput(Multiplayer::NetworkInput& input, float deltaTime)
    {
        MoverInputComponentControllerBase::ProcessInput(input, deltaTime);

        MoverInputComponentNetworkInput* moverNetworkInputPtr = input.FindComponentInput<MoverInputComponentNetworkInput>();
        AZ_Assert(moverNetworkInputPtr, "Network input for our own component will always exist.");
        MoverInputComponentNetworkInput& moverNetworkInput = *moverNetworkInputPtr;

        m_netInputs.m_moveForwardAxis = moverNetworkInput.m_moveForwardAxis;
        m_netInputs.m_moveRightAxis = moverNetworkInput.m_moveRightAxis;

        // Log current net input values.
        if (cl_xxgpnxx_moverInput_enableProcessInputLogs)
        {
            AZStd::fixed_string<128> logString;

            logString += __func__;
            logString += " executing. `m_netInputs.m_moveForwardAxis`: '";

            {
                AZStd::fixed_string<32> valueString;
                AZStd::to_string(valueString, m_netInputs.m_moveForwardAxis);

                logString += valueString;
            }

            logString += "'. `m_netInputs.m_moveRightAxis`: '";

            {
                AZStd::fixed_string<32> valueString;
                AZStd::to_string(valueString, m_netInputs.m_moveRightAxis);

                logString += valueString;
            }

            logString += "'.";

            AZLOG_INFO(logString.data());
        }

        // Now, actually move the entity.

        Multiplayer::NetworkCharacterComponentController* networkCharacterComponentControllerPtr = GetNetworkCharacterComponentController();
        AZ_Assert(moverNetworkInputPtr, "This component is required and will always exist.");
        Multiplayer::NetworkCharacterComponentController& networkCharacterComponentController = *networkCharacterComponentControllerPtr;

        AZ::Vector2 netMoveAxisInputVector = AZ::Vector2(m_netInputs.m_moveRightAxis, m_netInputs.m_moveForwardAxis);
        constexpr float maxMoveSpeed = 4.f;

        AZ::Vector3 velocity = AZ::Vector3(netMoveAxisInputVector.GetNormalizedSafe(), 0.f) * maxMoveSpeed;

        networkCharacterComponentController.TryMoveWithVelocity(velocity, deltaTime);
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

            m_autonomousInputs.m_moveForwardAxis = value;
        }
        else if (currentBusId == MoveRightAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveRightAxis;

            m_autonomousInputs.m_moveRightAxis = value;
        }

        if (cl_xxgpnxx_moverInput_enableClientInputEventLogs)
        {
            LogInputEvent(__func__, eventNameString, value);
        }
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

            m_autonomousInputs.m_moveForwardAxis = value;
        }
        else if (currentBusId == MoveRightAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveRightAxis;

            m_autonomousInputs.m_moveRightAxis = value;
        }

        if (cl_xxgpnxx_moverInput_enableClientInputEventLogs)
        {
            LogInputEvent(__func__, eventNameString, value);
        }
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

            m_autonomousInputs.m_moveForwardAxis = value;
        }
        else if (currentBusId == MoveRightAxisNotificationId)
        {
            eventNameString = InputEventNames::MoveRightAxis;

            m_autonomousInputs.m_moveRightAxis = value;
        }

        if (cl_xxgpnxx_moverInput_enableClientInputEventLogs)
        {
            LogInputEvent(__func__, eventNameString, value);
        }
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
