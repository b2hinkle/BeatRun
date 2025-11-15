
#include <Source/Components/RootAutonomousEntitySpawnerComponent.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <Multiplayer/NetworkEntity/INetworkEntityManager.h>
#include <Multiplayer/IMultiplayer.h>
#include <Source/Utils/MultiplayerUtils.h>
#include <AzCore/Console/ILogger.h>
#include <Multiplayer/NetworkEntity/NetworkEntityHandle.h>
#include <AzCore/Component/TransformBus.h>

namespace xXGameProjectNameXx
{
    AZ_COMPONENT_IMPL(RootAutonomousEntitySpawnerComponent, "RootAutonomousEntitySpawnerComponent", "{5C317DF1-7BD8-4CB2-8A4C-263740B14064}");

    void RootAutonomousEntitySpawnerComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<RootAutonomousEntitySpawnerComponent, AZ::Component>()
                ->Version(1)
                ->Field("RootAutonomousEntitySpawnable", &RootAutonomousEntitySpawnerComponent::m_rootAutonomousEntitySpawnable)
                ->Field("SpawnTransformEntityReference", &RootAutonomousEntitySpawnerComponent::m_spawnTransformEntityReference)
                ;

            if (AZ::EditContext* editContext = serializeContext->GetEditContext())
            {
                editContext->Class<RootAutonomousEntitySpawnerComponent>("RootAutonomousEntitySpawnerComponent", "[Description of functionality provided by this component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Category, "ComponentCategory")
                    ->Attribute(AZ::Edit::Attributes::Icon, "Icons/Components/Component_Placeholder.svg")
                    ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC_CE("Level"))
                    ->DataElement(
                        AZ::Edit::UIHandlers::Default,
                        &RootAutonomousEntitySpawnerComponent::m_rootAutonomousEntitySpawnable,
                        "Root Autonomous Entity Spawnable Asset",
                        "The network spawnable asset which will be created as an autonomous entity for each connection that joins. Only the first entity in the prefab will be spawned and used. Create hierarchy from it if you need multiple.")
                    ->DataElement(
                        AZ::Edit::UIHandlers::Default,
                        &RootAutonomousEntitySpawnerComponent::m_spawnTransformEntityReference,
                        "Spawn Transform Entity Reference",
                        "Reference to the entity to use as a spawn transform for the root autonomous entity.")
                    ;
            }
        }

        if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->Class<RootAutonomousEntitySpawnerComponent>("RootAutonomousEntitySpawner Component Group")
                ->Attribute(AZ::Script::Attributes::Category, "xXGameProjectNameXx Gem Group")
                ;
        }
    }

    void RootAutonomousEntitySpawnerComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("RootAutonomousEntitySpawnerComponentService"));
    }

    void RootAutonomousEntitySpawnerComponent::GetIncompatibleServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("RootAutonomousEntitySpawnerComponentService"));
    }

    void RootAutonomousEntitySpawnerComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void RootAutonomousEntitySpawnerComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    void RootAutonomousEntitySpawnerComponent::Activate()
    {
        AZ::Interface<IMultiplayerSpawner>::Register(this);
    }

    void RootAutonomousEntitySpawnerComponent::Deactivate()
    {
        AZ::Interface<IMultiplayerSpawner>::Unregister(this);
    }

    Multiplayer::NetworkEntityHandle RootAutonomousEntitySpawnerComponent::OnPlayerJoin(
        [[maybe_unused]] uint64_t userId,
        [[maybe_unused]] const Multiplayer::MultiplayerAgentDatum& agentDatum)
    {
        const AZ::Data::Asset<AzFramework::Spawnable>& spawnableAsset = m_rootAutonomousEntitySpawnable.m_spawnableAsset;

        AZ::Name spawnableAssetHintName{ spawnableAsset.GetHint() };

        const AZStd::size_t numEntitiesPerPrefab = spawnableAsset ? spawnableAsset->GetEntities().size() : 0u;
        if (numEntitiesPerPrefab > 2u)
        {
            AZStd::fixed_string<256> logString;

            logString += '`';
            logString += __func__;
            logString += "`: ";
            logString += "Prefab '";
            logString += spawnableAssetHintName.GetStringView();
            logString += "' has multiple entities. Only the first one will be used.";
            logString += ' ';
            logString += "Size of entity list: `";

            {
                AZStd::fixed_string<32> entityIdString;
                AZStd::to_string(entityIdString, numEntitiesPerPrefab);

                logString += entityIdString;
            }

            logString += "`.";
            logString += ' ';
            logString += "Two is the expected value for that array.";

            AZLOG_WARN(logString.data());
        }

        // Only spawn the first entity (ignoring the root) from the prefab, as this system expects only one entity.
        constexpr uint32_t prefabEntityOffset = 1u;
        Multiplayer::PrefabEntityId prefabEntityId{ spawnableAssetHintName, prefabEntityOffset };

        constexpr Multiplayer::NetEntityRole netEntityRole = Multiplayer::NetEntityRole::Authority;

        const AZ::Transform& spawnTransform = GetSpawnTransformFromEntityReference();

        Multiplayer::INetworkEntityManager::EntityList entityList =
            MultiplayerUtils::GetNetworkEntityManagerAsserted().CreateEntitiesImmediate(
                AZStd::move(prefabEntityId),
                netEntityRole,
                spawnTransform);

        if (entityList.empty())
        {
            AZStd::fixed_string<256> logString;

            logString += '`';
            logString += __func__;
            logString += "`: ";
            logString += "Attempt to spawn prefab '";
            logString += prefabEntityId.m_prefabName.GetStringView();
            logString += "' failed. No entities were spawned.";
            logString += ' ';
            logString += "Ensure that the prefab contains a single entity that is network enabled with a network binding component.";

            AZLOG_ERROR(logString.data());
            return Multiplayer::NetworkEntityHandle{};
        }

        // Return the spawned entity. This will be made autonomous by the multiplayer system.
        return AZStd::move(entityList[0]);
    }

    void RootAutonomousEntitySpawnerComponent::OnPlayerLeave(
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

    AZ::Transform RootAutonomousEntitySpawnerComponent::GetSpawnTransformFromEntityReference() const
    {
        AZ::Transform result = {};
        AZ::TransformBus::EventResult(result, m_spawnTransformEntityReference, &AZ::TransformBus::Events::GetWorldTM);
        return result;
    }
} // namespace xXGameProjectNameXx
