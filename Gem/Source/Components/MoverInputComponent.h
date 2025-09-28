
#pragma once

#include <Source/AutoGen/MoverInputComponent.AutoComponent.h>
#include <StartingPointInput/InputEventNotificationBus.h>
#include <xXGameProjectNameXx/InputEventNames.h>

namespace xXGameProjectNameXx
{
    //! @class MoverInputComponentController
    //! @note @Christian: TODO: [todo][techdebt][input][local_multiplayer] Decouple the input handling code out of this component so
    //!       that any input can be injected from anywhere. This would allow us to handle multiple local players too for local multiplayer.
    class MoverInputComponentController
        : public MoverInputComponentControllerBase
#if AZ_TRAIT_CLIENT
        , private StartingPointInput::InputEventNotificationBus::MultiHandler
#endif // #if AZ_TRAIT_CLIENT
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

    private:

#if AZ_TRAIT_CLIENT
        //! StartingPointInput::InputEventNotificationBus::MultiHandler private overrides.
        //! @{
        void OnPressed(float value) override;
        void OnHeld(float value) override;
        void OnReleased(float value) override;
        //! @}
#endif // #if AZ_TRAIT_CLIENT

    private:

#if AZ_TRAIT_CLIENT
        StartingPointInput::InputEventNotificationId MoveForwardAxisNotificationId;
        StartingPointInput::InputEventNotificationId MoveRightAxisNotificationId;
#endif // #if AZ_TRAIT_CLIENT

        //! @brief Values of input that will properly determine our network input values.
        //! @note @Christian: TODO: [todo][input][techdebt] Expose public setters for these autonomous inputs so that we can
        //!       externalize autonomous input handling from this class.
        //! @note @Christian: TODO: [todo][input][techdebt][ai][multiplayer] Make sure these values can be used to drive AI on the
        //!       server (including dedicated server).
        struct
        {
            float m_moveForwardAxis = 0.f;
            float m_moveRightAxis = 0.f;
        } m_autonomousInputs;

        //! @brief Network input values that will determine the gameplay of this component.
        //! @note @Christian: TODO: [todo][input][techdebt] Expose public getters to these network input values so that other systems
        //!       can use them if needed.
        struct
        {
            float m_moveForwardAxis = 0.f;
            float m_moveRightAxis = 0.f;
        } m_netInputs;
    };
} // namespace xXGameProjectNameXx
