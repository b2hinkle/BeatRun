
#pragma once

#if !AZ_TRAIT_CLIENT
#error "This file assumes it's being used for client code."
#endif // #if !AZ_TRAIT_CLIENT

#include <StartingPointInput/InputEventNotificationBus.h>
#include <AzCore/Component/Component.h>

namespace xXGameProjectNameXx
{
    //! @class ClientMoverInputInjector
    //! @brief Listens for local input events and injects values into the `MoverNetworkInputComponent` via the `MoverInputInterface`.
    //! @note @Christian: TODO: [todo][techdebt][input][local_multiplayer] Handle multiple local players for local multiplayer.
    class ClientMoverInputInjector
        : private StartingPointInput::InputEventNotificationBus::MultiHandler
    {
    public:

        ClientMoverInputInjector(const AZ::Component& parentComponent);

        //! Component descriptor interface.
        //! @{
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);
        //! @}

        //! Multiplayer controller interface.
        //! @{
        void OnActivate();
        void OnDeactivate();
        //! @}

    private:

        //! StartingPointInput::InputEventNotificationBus::MultiHandler private overrides.
        //! @{
        void OnPressed(float value) override;
        void OnHeld(float value) override;
        void OnReleased(float value) override;
        //! @}

    private:

        StartingPointInput::InputEventNotificationId m_moveForwardAxisNotificationId;
        StartingPointInput::InputEventNotificationId m_moveRightAxisNotificationId;

        const AZ::Component& m_parentComponent;
    };
} // namespace xXGameProjectNameXx
