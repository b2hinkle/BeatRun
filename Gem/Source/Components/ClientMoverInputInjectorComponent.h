
#pragma once

#include <AzCore/Component/Component.h>
#if AZ_TRAIT_CLIENT
#include <StartingPointInput/InputEventNotificationBus.h>
#endif // #if AZ_TRAIT_CLIENT

namespace xXGameProjectNameXx
{
    //! @class ClientMoverInputInjectorComponent
    //! @brief Listens for local input events and injects values into the `MoverInputComponent` via the `MoverInputInterface`.
    //! @note @Christian: TODO: [todo][techdebt][input][local_multiplayer] Handle multiple local players for local multiplayer.
    class ClientMoverInputInjectorComponent
        : public AZ::Component
#if AZ_TRAIT_CLIENT
        , private StartingPointInput::InputEventNotificationBus::MultiHandler
#endif // #if AZ_TRAIT_CLIENT
    {
    public:

        AZ_COMPONENT_DECL(ClientMoverInputInjectorComponent);

        //! Component descriptor interface.
        //! @{
        static void Reflect(AZ::ReflectContext* context);
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);
        //! @}

    protected:

        //! AZ::Component protected overrides.
        //! @{
        void Activate() override;
        void Deactivate() override;
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
