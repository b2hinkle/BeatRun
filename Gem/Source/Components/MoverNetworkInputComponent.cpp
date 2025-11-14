
#include <Source/Components/MoverNetworkInputComponent.h>

#include <Multiplayer/Components/NetworkCharacterComponent.h>
#include <AzCore/Debug/Trace.h>
#include <xXGameProjectNameXx/MoverInterface.h>

namespace xXGameProjectNameXx
{
    void MoverNetworkInputComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<MoverNetworkInputComponent, MoverNetworkInputComponentBase>()
                ->Version(1)
                ;
        }

        MoverNetworkInputComponentBase::Reflect(context);
    }

    void MoverNetworkInputComponent::OnActivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
    }

    void MoverNetworkInputComponent::OnDeactivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
    }

    MoverNetworkInputComponentController::MoverNetworkInputComponentController(MoverNetworkInputComponent& parent)
        : MoverNetworkInputComponentControllerBase(parent)
    {
    }

    void MoverNetworkInputComponentController::OnActivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
        MoverNetworkInputRequestBus::Handler::BusConnect(GetEntityId());
    }

    void MoverNetworkInputComponentController::OnDeactivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
        MoverNetworkInputRequestBus::Handler::BusDisconnect(GetEntityId());
    }

    void MoverNetworkInputComponentController::CreateInput(Multiplayer::NetworkInput& input, float deltaTime)
    {
        MoverNetworkInputComponentControllerBase::CreateInput(input, deltaTime);

        MoverNetworkInputComponentNetworkInput* moverNetworkInputPtr = input.FindComponentInput<MoverNetworkInputComponentNetworkInput>();
        AZ_Assert(moverNetworkInputPtr, "Network input for our own component will always exist.");
        MoverNetworkInputComponentNetworkInput& moverNetworkInput = *moverNetworkInputPtr;

        moverNetworkInput.m_moveForwardAxis = m_autonomousInputs.m_moveForwardAxis;
        moverNetworkInput.m_moveRightAxis = m_autonomousInputs.m_moveRightAxis;
    }

    void MoverNetworkInputComponentController::ProcessInput(Multiplayer::NetworkInput& input, float deltaTime)
    {
        MoverNetworkInputComponentControllerBase::ProcessInput(input, deltaTime);

        MoverNetworkInputComponentNetworkInput* moverNetworkInputPtr = input.FindComponentInput<MoverNetworkInputComponentNetworkInput>();
        AZ_Assert(moverNetworkInputPtr, "Network input for our own component will always exist.");
        MoverNetworkInputComponentNetworkInput& moverNetworkInput = *moverNetworkInputPtr;

        // Inject network input values as gameplay input.
        MoverRequestFunctions::SetMoveForwardAxis(GetEntityId(), moverNetworkInput.m_moveForwardAxis);
        MoverRequestFunctions::SetMoveRightAxis(GetEntityId(), moverNetworkInput.m_moveRightAxis);

        // Now, actually tick the gameplay.
        MoverRequestFunctions::TickGameplay(GetEntityId(), deltaTime);
    }

    float MoverNetworkInputComponentController::GetMoveForwardAxis() const
    {
        return m_autonomousInputs.m_moveForwardAxis;
    }

    float MoverNetworkInputComponentController::GetMoveRightAxis() const
    {
        return m_autonomousInputs.m_moveRightAxis;
    }

    void MoverNetworkInputComponentController::SetMoveForwardAxis(float newValue)
    {
        m_autonomousInputs.m_moveForwardAxis = newValue;
    }

    void MoverNetworkInputComponentController::SetMoveRightAxis(float newValue)
    {
        m_autonomousInputs.m_moveRightAxis = newValue;
    }
}
