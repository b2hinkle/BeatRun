
#include <AzCore/Module/Module.h>
#include <AzCore/Memory/SystemAllocator.h>
#include <xXGameProjectNameXx/xXGameProjectNameXxTypeIds.h>
#include <Source/xXGameProjectNameXxSystemComponent.h>
#include <Source/AutoGen/AutoComponentTypes.h>
#include <Source/Components/MyExperimentComponent.h>
#include <Source/Components/MoverClientInputInjectorComponent.h>
// @Christian: TODO: [todo] Make our own `CreateComponentDescriptors` function for our own custom AutoGen components, similar to the Multiplayer gem's AutoComponents.
#include <Source/AutoGen/StageSelectGameStateLevelComponent.GameStateLevelComponent.h>
#include <Source/Components/RootAutonomousEntitySpawnerComponent.h>
#include <Source/Components/MoverComponent.h>
#include <Source/PlayerSystemComponent.h>

namespace xXGameProjectNameXx
{
    class xXGameProjectNameXxModule
        : public AZ::Module
    {
    public:

        AZ_RTTI(xXGameProjectNameXxModule, GetTypeId<xXGameProjectNameXxModule>(), AZ::Module);
        AZ_CLASS_ALLOCATOR(xXGameProjectNameXxModule, AZ::SystemAllocator);

        xXGameProjectNameXxModule()
            : AZ::Module()
        {
            m_descriptors.insert(m_descriptors.end(), {
                xXGameProjectNameXxSystemComponent::CreateDescriptor(),
                MyExperimentComponent::CreateDescriptor(),
                MoverClientInputInjectorComponent::CreateDescriptor(),
                StageSelectGameStateLevelComponent::CreateDescriptor(),
                RootAutonomousEntitySpawnerComponent::CreateDescriptor(),
                MoverComponent::CreateDescriptor(),
                PlayerSystemComponent::CreateDescriptor(),
            });

            // Create descriptors for our auto-components. Important: These are supposed to be the last descriptors added.
            CreateComponentDescriptors(m_descriptors);
        }

        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<xXGameProjectNameXxSystemComponent>(),
                azrtti_typeid<PlayerSystemComponent>(),
            };
        }
    };
}// namespace xXGameProjectNameXx

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME), xXGameProjectNameXx::xXGameProjectNameXxModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_xXGameProjectNameXx, xXGameProjectNameXx::xXGameProjectNameXxModule)
#endif
