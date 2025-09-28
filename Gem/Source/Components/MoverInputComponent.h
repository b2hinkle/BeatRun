
#pragma once

#include <Source/AutoGen/MoverInputComponent.AutoComponent.h>
#include <Include/xXGameProjectNameXx/MoverInputInterface.h>

namespace xXGameProjectNameXx
{
    //! @class MoverInputComponent
    class MoverInputComponent
        : public MoverInputComponentBase
    {
    public:

        AZ_MULTIPLAYER_COMPONENT(xXGameProjectNameXx::MoverInputComponent, s_moverInputComponentConcreteUuid, xXGameProjectNameXx::MoverInputComponentBase);

        //! Component descriptor interface.
        //! @{
        static void Reflect(AZ::ReflectContext* context);
        //! @}

        //! MoverInputComponentBase public overrides.
        //! @{
        void OnActivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;
        //! @}
    };

    //! @class MoverInputComponentController
    class MoverInputComponentController
        : public MoverInputComponentControllerBase
        , public MoverInputRequestBus::Handler
    {
    public:

        explicit MoverInputComponentController(MoverInputComponent& parent);

        //! MoverInputComponentControllerBase public overrides.
        //! @{
        void OnActivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;
        void CreateInput(Multiplayer::NetworkInput& input, float deltaTime) override;
        void ProcessInput(Multiplayer::NetworkInput& input, float deltaTime) override;
        //! @}

        //! MoverInputRequestBus::Handler public overrides.
        //! @{
        float GetMoveForwardAxisAutonomousInput() const override;
        float GetMoveRightAxisAutonomousInput() const override;
        void SetMoveForwardAxisAutonomousInput(float newValue) override;
        void SetMoveRightAxisAutonomousInput(float newValue) override;
        float GetMoveForwardAxisNetInput() const override;
        float GetMoveRightAxisNetInput() const override;
        //! @}

    private:

        //! @brief Values of input that will properly determine our network input values.
        //! @note @Christian: TODO: [todo][input][techdebt][ai][multiplayer] Make sure these values can be used to drive AI on the
        //!       server (including dedicated server).
        struct
        {
            float m_moveForwardAxis = 0.f;
            float m_moveRightAxis = 0.f;
        } m_autonomousInputs;

        //! @brief Network input values that will determine the gameplay of this component.
        struct
        {
            float m_moveForwardAxis = 0.f;
            float m_moveRightAxis = 0.f;
        } m_netInputs;
    };
} // namespace xXGameProjectNameXx
