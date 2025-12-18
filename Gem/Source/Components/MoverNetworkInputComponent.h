
#pragma once

#include <Source/AutoGen/MoverNetworkInputComponent.AutoComponent.h>
#include <xXGameProjectNameXx/MoverNetworkInputInterface.h>

namespace xXGameProjectNameXx
{
    //! @class MoverNetworkInputComponent
    class MoverNetworkInputComponent
        : public MoverNetworkInputComponentBase
    {
    public:

        AZ_MULTIPLAYER_COMPONENT(xXGameProjectNameXx::MoverNetworkInputComponent, s_moverNetworkInputComponentConcreteUuid, xXGameProjectNameXx::MoverNetworkInputComponentBase);

        //! Component descriptor interface.
        //! @{
        static void Reflect(AZ::ReflectContext* context);
        //! @}

        //! MoverNetworkInputComponentBase public overrides.
        //! @{
        void OnActivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;
        //! @}
    };

    //! @class MoverNetworkInputComponentController
    class MoverNetworkInputComponentController
        : public MoverNetworkInputComponentControllerBase
        , protected MoverNetworkInputRequestBus::Handler
    {
    public:

        explicit MoverNetworkInputComponentController(MoverNetworkInputComponent& parent);

        //! MoverNetworkInputComponentControllerBase public overrides.
        //! @{
        void OnActivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;
        void CreateInput(Multiplayer::NetworkInput& input, float deltaTime) override;
        void ProcessInput(Multiplayer::NetworkInput& input, float deltaTime) override;
        //! @}

    protected:

        //! MoverNetworkInputRequestBus::Handler overrides.
        //! @{
        float GetMoveForwardAxis() const override;
        float GetMoveRightAxis() const override;
        void SetMoveForwardAxis(float newValue) override;
        void SetMoveRightAxis(float newValue) override;
        //! @}

    private:

        //! @brief Values of input that will properly determine our network input values.
        struct
        {
            float m_moveForwardAxis = 0.f;
            float m_moveRightAxis = 0.f;
        } m_autonomousInputs;
    };
} // namespace xXGameProjectNameXx
