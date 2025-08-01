
#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Module/Module.h>

#include "xXGameProjectNameXxSystemComponent.h"

#include <xXGameProjectNameXx/xXGameProjectNameXxTypeIds.h>

namespace xXGameProjectNameXx
{
    class xXGameProjectNameXxModule
        : public AZ::Module
    {
    public:
        AZ_RTTI(xXGameProjectNameXxModule, xXGameProjectNameXxModuleTypeId, AZ::Module);
        AZ_CLASS_ALLOCATOR(xXGameProjectNameXxModule, AZ::SystemAllocator);

        xXGameProjectNameXxModule()
            : AZ::Module()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                xXGameProjectNameXxSystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<xXGameProjectNameXxSystemComponent>(),
            };
        }
    };
}// namespace xXGameProjectNameXx

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME), xXGameProjectNameXx::xXGameProjectNameXxModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_xXGameProjectNameXx, xXGameProjectNameXx::xXGameProjectNameXxModule)
#endif
