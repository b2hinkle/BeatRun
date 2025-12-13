
#pragma once

#include <AzCore/Component/Component.h>
#include <xXGameProjectNameXx/MyExperimentInterface.h>

namespace xXGameProjectNameXx
{
    class MyExperimentComponent
        : public AZ::Component
        , protected MyExperimentRequestBus::Handler
    {
    public:

        AZ_COMPONENT_DECL(MyExperimentComponent);

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
    };
} // namespace xXGameProjectNameXx
