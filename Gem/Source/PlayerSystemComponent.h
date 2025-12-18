
#pragma once

#include <AzCore/Component/Component.h>

#include <xXGameProjectNameXx/PlayerBus.h>
#include <CryCommon/CrySystemBus.h>

namespace xXGameProjectNameXx
{
    //! @brief This intended to be a place to store a persistent local player data across level loads.
    class PlayerSystemComponent
        : public AZ::Component
        , protected PlayerRequestBus::Handler
        , protected CrySystemEventBus::Handler
    {
    public:

        AZ_COMPONENT_DECL(PlayerSystemComponent);

        PlayerSystemComponent();
        ~PlayerSystemComponent() override;

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
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        //! @}

        //! CrySystemEventBus::Handler overrides.
        //! @{
        void OnCrySystemInitialized(ISystem&, const SSystemInitParams&) override;
        //! @}
    };
}
