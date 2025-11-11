
#include <Source/Components/PlayerEntityManagerComponent.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <Multiplayer/NetworkEntity/INetworkEntityManager.h>
#include <Multiplayer/IMultiplayer.h>
#include <Source/Utils/MultiplayerUtils.h>
#include <AzCore/Console/ILogger.h>
#include <Multiplayer/NetworkEntity/NetworkEntityHandle.h>
#include <Multiplayer/Components/NetBindComponent.h>
#include <AzCore/Component/TransformBus.h>
#include "AzCore/Component/Entity.h"
#include <AzCore/Console/ILogger.h>

namespace xXGameProjectNameXx
{
    void PlayerEntityManagerComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<PlayerEntityManagerComponent, PlayerEntityManagerComponentBase>()
                ->Field("PlayerEntitySpawnable", &PlayerEntityManagerComponent::m_playerEntitySpawnable)
                ->Field("NumPlayersToCreate", &PlayerEntityManagerComponent::m_numPlayersToCreate)
                ->Version(1)
                ;

            if (AZ::EditContext* editContext = serializeContext->GetEditContext())
            {
                editContext->Class<PlayerEntityManagerComponent>("PlayerEntityManagerComponent", "[Description of functionality provided by this component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Category, "ComponentCategory")
                    ->Attribute(AZ::Edit::Attributes::Icon, "Icons/Components/Component_Placeholder.svg")
                    ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC_CE("Game"))
                    ->DataElement(
                        AZ::Edit::UIHandlers::Default,
                        &PlayerEntityManagerComponent::m_playerEntitySpawnable,
                        "Player Entity Spawn",
                        "The network spawnable asset to create for each player.")
                    ->DataElement(
                        AZ::Edit::UIHandlers::Default,
                        &PlayerEntityManagerComponent::m_numPlayersToCreate,
                        "Num Players To Create",
                        "The number of players to create per connection.")
                    ;
            }
        }

        PlayerEntityManagerComponentBase::Reflect(context);
    }

    void PlayerEntityManagerComponent::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        PlayerEntityManagerComponentBase::GetRequiredServices(required);
    }

    void PlayerEntityManagerComponent::GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        PlayerEntityManagerComponentBase::GetDependentServices(dependent);
    }

    void PlayerEntityManagerComponent::OnActivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
    }

    void PlayerEntityManagerComponent::OnDeactivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
    }

    int PlayerEntityManagerComponent::GetNumPlayersToCreate() const
    {
        return m_numPlayersToCreate;
    }

    const Multiplayer::NetworkSpawnable& PlayerEntityManagerComponent::GetPlayerEntitySpawnable() const
    {
        return m_playerEntitySpawnable;
    }

    void PlayerEntityManagerComponent::SetNumPlayersToCreate(int newValue)
    {
        m_numPlayersToCreate = newValue;
    }

    void PlayerEntityManagerComponent::SetPlayerEntitySpawnable(Multiplayer::NetworkSpawnable&& newValue)
    {
        m_playerEntitySpawnable = AZStd::move(newValue);
    }

    PlayerEntityManagerComponentController::PlayerEntityManagerComponentController(PlayerEntityManagerComponent& parent)
        : PlayerEntityManagerComponentControllerBase(parent)
    {
    }

    void PlayerEntityManagerComponentController::OnActivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
#if AZ_TRAIT_SERVER
        {
            const AZ::Entity* entityPtr = GetEntity();
            AZ_Assert(entityPtr, "Should not be null.");
            const AZ::Entity& entity = *entityPtr;

            // Only perform our initial logic if our entity is not already active. As a multiplayer component controller, this is
            // important to check because because we may be activated a 2nd time in the case of the server enabling autonomous
            // control, which would cause us to deactivate and reactivate. See `MultiplayerSystemComponent::EnableAutonomousControl` and
            // `NetBindComponent::EnablePlayerHostAutonomy`.
            if (entity.GetState() != AZ::Entity::State::Active)
            {
                const Multiplayer::NetBindComponent& netBindComponent = MultiplayerUtils::GetNetBindComponentAsserted(GetOwner());
                if (netBindComponent.IsNetEntityRoleAuthority())
                {
                    CreatePlayerEntities();
                }
            }
        }
#endif // #if AZ_TRAIT_SERVER
    }

    void PlayerEntityManagerComponentController::OnDeactivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
    }

#if AZ_TRAIT_SERVER
    void PlayerEntityManagerComponentController::CreatePlayerEntities()
    {
        AZ_Assert(MultiplayerUtils::GetNetBindComponentAsserted(GetOwner()).IsNetEntityRoleAuthority(), "Should only be called on the authority.");

        for (int i = 0; i < GetOwnerCasted().m_numPlayersToCreate; ++i)
        {
            AZ::Name entitySpawnableAssetHintName{ GetOwnerCasted().m_playerEntitySpawnable.m_spawnableAsset.GetHint() };

            Multiplayer::NetworkEntityHandle playerEntityHandle =
                CreatePlayerEntity(Multiplayer::PrefabEntityId{ entitySpawnableAssetHintName });

            AZ::Entity* playerEntity = playerEntityHandle.GetEntity();
            if (!playerEntity)
            {
                AZStd::fixed_string<256> logString;

                logString += '`';
                logString += __func__;
                logString += "`: ";
                logString += "Attempt to spawn prefab '";
                logString += entitySpawnableAssetHintName.GetStringView();
                logString += "' failed. No entities were spawned.";
                logString += ' ';
                logString += "Ensure that the prefab contains a single entity that is network enabled with a network binding component.";

                AZLOG_ERROR(logString.data());
                continue;
            }

            const AZ::EntityId& owningEntityId = GetEntityId();
            AZ::TransformBus::Event(playerEntity->GetId(), &AZ::TransformInterface::SetParentRelative, owningEntityId);

            ModifyPlayerNetEntityIds().emplace_back(playerEntityHandle.GetNetEntityId());
        }
    }
#endif // #if AZ_TRAIT_SERVER

#if AZ_TRAIT_SERVER
    Multiplayer::NetworkEntityHandle PlayerEntityManagerComponentController::CreatePlayerEntity(
        const Multiplayer::PrefabEntityId& playerEntityPrefab)
    {
        constexpr Multiplayer::NetEntityRole netEntityRole = Multiplayer::NetEntityRole::Authority;

        Multiplayer::INetworkEntityManager::EntityList createdEntities =
            MultiplayerUtils::GetNetworkEntityManagerAsserted().CreateEntitiesImmediate(
                playerEntityPrefab,
                netEntityRole,
                AZ::Transform::CreateIdentity());

        if (createdEntities.empty())
        {
            // Failure: The prefab has no networked entities in it.
            AZLOG_ERROR(
                "Attempt to spawn prefab '%s' failed, no entities were spawned. Ensure that the prefab contains a single entity "
                "that is network enabled with a Network Binding component.",
                playerEntityPrefab.m_prefabName.GetCStr());
            return Multiplayer::NetworkEntityHandle{};
        }

        // Return the spawned entity. This will be made autonomous by the multiplayer system.
        return AZStd::move(createdEntities[0]);
    }
#endif // #if AZ_TRAIT_SERVER
} // namespace xXGameProjectNameXx
