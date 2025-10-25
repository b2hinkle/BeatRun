
#include <Source/Components/MyMultiplayerSpawnerComponent.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <Multiplayer/NetworkEntity/INetworkEntityManager.h>
#include <Multiplayer/IMultiplayer.h>
#include <Source/Utils/MultiplayerUtils.h>
#include <AZCore/Console/ILogger.h>
#include <Multiplayer/NetworkEntity/NetworkEntityHandle.h>
#include <AzCore/Component/TransformBus.h>

namespace xXGameProjectNameXx
{
    AZ_COMPONENT_IMPL(MyMultiplayerSpawnerComponent, "MyMultiplayerSpawnerComponent", "{5C317DF1-7BD8-4CB2-8A4C-263740B14064}");

    void MyMultiplayerSpawnerComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<MyMultiplayerSpawnerComponent, AZ::Component>()
                ->Version(1)
                ->Field("RootAutonomousEntitySpawnable", &MyMultiplayerSpawnerComponent::m_rootAutonomousEntitySpawnable)
                ->Field("SpawnTransformEntityReference", &MyMultiplayerSpawnerComponent::m_spawnTransformEntityReference)
                ;

            if (AZ::EditContext* editContext = serializeContext->GetEditContext())
            {
                editContext->Class<MyMultiplayerSpawnerComponent>("MyMultiplayerSpawnerComponent", "[Description of functionality provided by this component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Category, "ComponentCategory")
                    ->Attribute(AZ::Edit::Attributes::Icon, "Icons/Components/Component_Placeholder.svg")
                    ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC_CE("Level"))
                    ->DataElement(
                        AZ::Edit::UIHandlers::Default,
                        &MyMultiplayerSpawnerComponent::m_rootAutonomousEntitySpawnable,
                        "Root Autonomous Entity Spawnable Asset",
                        "The network spawnable asset which will be created as an autonomous entity for each connection that joins.")
                    ->DataElement(
                        AZ::Edit::UIHandlers::Default,
                        &MyMultiplayerSpawnerComponent::m_spawnTransformEntityReference,
                        "Spawn Transform Entity Reference",
                        "Reference to the entity to use as a spawn transform for the root autonomous entity.")
                    ;
            }
        }

        if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->Class<MyMultiplayerSpawnerComponent>("MyMultiplayerSpawner Component Group")
                ->Attribute(AZ::Script::Attributes::Category, "xXGameProjectNameXx Gem Group")
                ;
        }
    }

    void MyMultiplayerSpawnerComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("MyMultiplayerSpawnerComponentService"));
    }

    void MyMultiplayerSpawnerComponent::GetIncompatibleServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("MyMultiplayerSpawnerComponentService"));
    }

    void MyMultiplayerSpawnerComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void MyMultiplayerSpawnerComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    Multiplayer::NetworkEntityHandle MyMultiplayerSpawnerComponent::OnPlayerJoin(
        [[maybe_unused]] uint64_t userId,
        [[maybe_unused]] const Multiplayer::MultiplayerAgentDatum& agentDatum)
    {
        const Multiplayer::PrefabEntityId prefabEntityId(AZ::Name(m_rootAutonomousEntitySpawnable.m_spawnableAsset.GetHint()));
        constexpr Multiplayer::NetEntityRole netEntityRole = Multiplayer::NetEntityRole::Authority;

        // Pull the transform to spawn at from the spawn transform entity reference.
        AZ::Transform transform = {};
        AZ::TransformBus::EventResult(transform, m_spawnTransformEntityReference, &AZ::TransformBus::Events::GetWorldTM);

        Multiplayer::INetworkEntityManager::EntityList entityList =
            MultiplayerUtils::GetNetworkEntityManagerAsserted().CreateEntitiesImmediate(
                prefabEntityId,
                netEntityRole,
                transform);

        if (entityList.empty())
        {
            // Failure: The prefab has no networked entities in it.
            AZLOG_ERROR(
                "Attempt to spawn prefab '%s' failed, no entities were spawned. Ensure that the prefab contains a single entity "
                "that is network enabled with a Network Binding component.",
                prefabEntityId.m_prefabName.GetCStr());
            return Multiplayer::NetworkEntityHandle{};
        }

        // Return the spawned entity. This will be made autonomous by the multiplayer system.
        return AZStd::move(entityList[0]);
    }

    void MyMultiplayerSpawnerComponent::OnPlayerLeave(
        Multiplayer::ConstNetworkEntityHandle entityHandle,
        [[maybe_unused]] const Multiplayer::ReplicationSet& replicationSet,
        [[maybe_unused]] AzNetworking::DisconnectReason reason)
    {
        Multiplayer::INetworkEntityManager& networkEntityManager = MultiplayerUtils::GetNetworkEntityManagerAsserted();

        // Walk hierarchy backwards to remove all children before parents
        AZStd::vector<AZ::EntityId> hierarchy = entityHandle.GetEntity()->GetTransform()->GetEntityAndAllDescendants();
        for (auto it = hierarchy.rbegin(); it != hierarchy.rend(); ++it)
        {
            Multiplayer::ConstNetworkEntityHandle hierarchyEntityHandle = networkEntityManager.GetEntity(networkEntityManager.GetNetEntityIdById(*it));
            if (hierarchyEntityHandle)
            {
                networkEntityManager.MarkForRemoval(hierarchyEntityHandle);
            }
        }
    }

    void MyMultiplayerSpawnerComponent::Activate()
    {
        AZ::Interface<IMultiplayerSpawner>::Register(this);
    }

    void MyMultiplayerSpawnerComponent::Deactivate()
    {
        AZ::Interface<IMultiplayerSpawner>::Unregister(this);
    }
} // namespace xXGameProjectNameXx
