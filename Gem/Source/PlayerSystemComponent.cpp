
#include <Source/PlayerSystemComponent.h>

#include <xXGameProjectNameXx/xXGameProjectNameXxTypeIds.h>
#include <AzCore/Serialization/SerializeContext.h>
#include <Source/AutoGen/AutoComponentTypes.h>
#if AZ_TRAIT_CLIENT
#include <LyShine/Bus/UiCursorBus.h>
#endif // #if AZ_TRAIT_CLIENT
#include <xXGameProjectNameXx/SettingsRegistryAccessors.h>
#include <AzCore/Component/TickBus.h>

namespace xXGameProjectNameXx
{
    AZ_COMPONENT_IMPL(PlayerSystemComponent, "PlayerSystemComponent",
        GetTypeId<PlayerSystemComponent>());

    void PlayerSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<PlayerSystemComponent, AZ::Component>()
                ->Version(0)
                ;
        }
    }

    void PlayerSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("PlayerService"));
    }

    void PlayerSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("PlayerService"));
    }

    void PlayerSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void PlayerSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    PlayerSystemComponent::PlayerSystemComponent()
    {
        if (PlayerInterface::Get() == nullptr)
        {
            PlayerInterface::Register(this);
        }
    }

    PlayerSystemComponent::~PlayerSystemComponent()
    {
        if (PlayerInterface::Get() == this)
        {
            PlayerInterface::Unregister(this);
        }
    }

    void PlayerSystemComponent::Init()
    {
    }

    void PlayerSystemComponent::Activate()
    {
        PlayerRequestBus::Handler::BusConnect();

        CrySystemEventBus::Handler::BusConnect();
    }

    void PlayerSystemComponent::Deactivate()
    {
        PlayerRequestBus::Handler::BusDisconnect();

        CrySystemEventBus::Handler::BusDisconnect();
    }

    void PlayerSystemComponent::OnCrySystemInitialized(ISystem&, const SSystemInitParams&)
    {
    }
}
