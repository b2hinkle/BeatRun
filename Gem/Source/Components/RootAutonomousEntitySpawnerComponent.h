
#pragma once

#include <AzCore/Component/Component.h>
#include <Multiplayer/IMultiplayerSpawner.h>
#include <Multiplayer/MultiplayerTypes.h>

namespace xXGameProjectNameXx
{
    //! @brief Handles spawning the root autonomous entity for new connections that join the server.
    class RootAutonomousEntitySpawnerComponent
        : public AZ::Component
        , protected Multiplayer::IMultiplayerSpawner
    {
    public:

        AZ_COMPONENT_DECL(RootAutonomousEntitySpawnerComponent);

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

        //! Multiplayer::IMultiplayerSpawner protected overrides.
        //! @{
        Multiplayer::NetworkEntityHandle OnPlayerJoin(uint64_t userId, const Multiplayer::MultiplayerAgentDatum& agentDatum) override;
        void OnPlayerLeave(Multiplayer::ConstNetworkEntityHandle entityHandle, const Multiplayer::ReplicationSet& replicationSet, AzNetworking::DisconnectReason reason) override;
        //! @}

    private:

        Multiplayer::NetworkSpawnable m_rootAutonomousEntitySpawnable;

        // @Christian: TODO: [todo][techdebt][multiplayer] Move this to new component which would handle spawning actual player and character entities.
        AZ::EntityId m_spawnTransformEntityReference;
    };
} // namespace xXGameProjectNameXx
