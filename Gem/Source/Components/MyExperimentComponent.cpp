
#include <Source/Components/MyExperimentComponent.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/RTTI/BehaviorContext.h>

namespace xXGameProjectNameXx
{
    AZ_COMPONENT_IMPL(MyExperimentComponent, "MyExperimentComponent", "{E696F584-5D34-422F-AE9A-51967ADCAA64}");

    void MyExperimentComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<MyExperimentComponent, AZ::Component>()
                ->Version(1)
                ;

            if (AZ::EditContext* editContext = serializeContext->GetEditContext())
            {
                editContext->Class<MyExperimentComponent>("MyExperimentComponent", "[Description of functionality provided by this component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Category, "ComponentCategory")
                    ->Attribute(AZ::Edit::Attributes::Icon, "Icons/Components/Component_Placeholder.svg")
                    ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC_CE("Game"))
                    ;
            }
        }

        if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->Class<MyExperimentComponent>("MyExperiment Component Group")
                ->Attribute(AZ::Script::Attributes::Category, "xXGameProjectNameXx Gem Group")
                ;
        }
    }

    void MyExperimentComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("MyExperimentComponentService"));
    }

    void MyExperimentComponent::GetIncompatibleServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
    }

    void MyExperimentComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void MyExperimentComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    void MyExperimentComponent::Activate()
    {
        MyExperimentRequestBus::Handler::BusConnect(GetEntityId());
    }

    void MyExperimentComponent::Deactivate()
    {
        MyExperimentRequestBus::Handler::BusDisconnect(GetEntityId());
    }
} // namespace xXGameProjectNameXx
