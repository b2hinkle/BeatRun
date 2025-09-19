
#pragma once

#include <Source/AutoGen/MoverInputComponent.AutoComponent.h>
#include <StartingPointInput/InputEventNotificationBus.h>
#include <xXGameProjectNameXx/InputEventNames.h>

namespace xXGameProjectNameXx
{
    //! @class MoverInputComponentController
    //! @par
    //!
    //! @Christian: TODO: [todo][techdebt][input][local_multiplayer] Decouple the input handling code out of this component so
    //! that any input can be injected from anywhere. This would allow us to handle multiple local players too for local multiplayer.
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
    };
} // namespace xXGameProjectNameXx
