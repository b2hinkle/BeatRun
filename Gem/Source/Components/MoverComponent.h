
#pragma once

#include <AzCore/Component/Component.h>
#include <xXGameProjectNameXx/MoverInterface.h>

namespace Multiplayer
{
    class NetworkCharacterComponentController;
}

namespace xXGameProjectNameXx
{
    //! @class MoverComponent
    //! @brief Local gameplay functionality of movement. This is driven by local input values and manually ticked which
    //! can be controlled by the `MoverRequestBus`.
    class MoverComponent
        : public AZ::Component
        , protected MoverRequestBus::Handler
    {
    public:

        AZ_COMPONENT_DECL(MoverComponent);

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

        //! MoverGameplayInputRequestBus::Handler overrides.
        //! @{
        void TickGameplay(float deltaTime) const override;
        float GetMoveForwardAxis() const override;
        float GetMoveRightAxis() const override;
        void SetMoveForwardAxis(float newValue) override;
        void SetMoveRightAxis(float newValue) override;
        //! @}

        Multiplayer::NetworkCharacterComponentController& GetNetworkCharacterComponentControllerAsserted() const;

    private:

        //! @brief Local values that will determine the gameplay of this component whenever ticked.
        struct
        {
            float m_moveForwardAxis = 0.f;
            float m_moveRightAxis = 0.f;
        } m_localGameplayInputs;
    };
} // namespace xXGameProjectNameXx
