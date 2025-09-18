
#include <AzCore/Serialization/SerializeContext.h>

#include <Source/xXGameProjectNameXxSystemComponent.h>

#include <xXGameProjectNameXx/xXGameProjectNameXxTypeIds.h>
#include <Source/AutoGen/AutoComponentTypes.h>

namespace xXGameProjectNameXx
{
    AZ_COMPONENT_IMPL(xXGameProjectNameXxSystemComponent, "xXGameProjectNameXxSystemComponent",
        xXGameProjectNameXxSystemComponentTypeId);

    void xXGameProjectNameXxSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<xXGameProjectNameXxSystemComponent, AZ::Component>()
                ->Version(0)
                ;
        }
    }

    void xXGameProjectNameXxSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("xXGameProjectNameXxService"));
    }

    void xXGameProjectNameXxSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("xXGameProjectNameXxService"));
    }

    void xXGameProjectNameXxSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void xXGameProjectNameXxSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    xXGameProjectNameXxSystemComponent::xXGameProjectNameXxSystemComponent()
    {
        if (xXGameProjectNameXxInterface::Get() == nullptr)
        {
            xXGameProjectNameXxInterface::Register(this);
        }
    }

    xXGameProjectNameXxSystemComponent::~xXGameProjectNameXxSystemComponent()
    {
        if (xXGameProjectNameXxInterface::Get() == this)
        {
            xXGameProjectNameXxInterface::Unregister(this);
        }
    }

    void xXGameProjectNameXxSystemComponent::Init()
    {
    }

    void xXGameProjectNameXxSystemComponent::Activate()
    {
        xXGameProjectNameXxRequestBus::Handler::BusConnect();

        // Register our auto-components.
        RegisterMultiplayerComponents();
    }

    void xXGameProjectNameXxSystemComponent::Deactivate()
    {
        xXGameProjectNameXxRequestBus::Handler::BusDisconnect();
    }
}
