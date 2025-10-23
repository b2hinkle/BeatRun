
#include <Source/Utils/MultiplayerUtils.h>

#include <AzCore/Console/ILogger.h>
#include <Multiplayer/IMultiplayer.h>
#include <Multiplayer/Components/NetBindComponent.h>

namespace xXGameProjectNameXx::MultiplayerUtils
{
    Multiplayer::NetBindComponent& GetNetBindComponentAsserted(const AZ::Component& component)
    {
        const Multiplayer::INetworkEntityManager* networkEntityManagerPtr = Multiplayer::GetNetworkEntityManager();
        AZ_Assert(networkEntityManagerPtr, "This should always exist at this time.");
        const Multiplayer::INetworkEntityManager& networkEntityManager = *networkEntityManagerPtr;

        const Multiplayer::NetEntityId& netEntityId = networkEntityManager.GetNetEntityIdById(component.GetEntityId());
        const Multiplayer::ConstNetworkEntityHandle& netEntityHandle = networkEntityManager.GetEntity(netEntityId);

        Multiplayer::NetBindComponent* netBindComponentPtr = netEntityHandle.GetNetBindComponent();
        AZ_Assert(netBindComponentPtr, "This component is required and will always exist.");
        Multiplayer::NetBindComponent& netBindComponent = *netBindComponentPtr;

        return netBindComponent;
    }
} // namespace xXGameProjectNameXx::Utils::Multiplayer
