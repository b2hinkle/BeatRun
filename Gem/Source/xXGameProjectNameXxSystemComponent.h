
#pragma once

#include <AzCore/Component/Component.h>

#include <xXGameProjectNameXx/xXGameProjectNameXxBus.h>
#include <CryCommon/CrySystemBus.h>

namespace xXGameProjectNameXx
{
    class xXGameProjectNameXxSystemComponent
        : public AZ::Component
        , protected xXGameProjectNameXxRequestBus::Handler
        , protected CrySystemEventBus::Handler
    {
    public:
        AZ_COMPONENT_DECL(xXGameProjectNameXxSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        xXGameProjectNameXxSystemComponent();
        ~xXGameProjectNameXxSystemComponent();

    protected:
        ////////////////////////////////////////////////////////////////////////
        // xXGameProjectNameXxRequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////

        //! CrySystemEventBus::Handler overrides.
        //! @{
        void OnCrySystemInitialized(ISystem&, const SSystemInitParams&) override;
        //! @}
    };
}
