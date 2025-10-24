
#pragma once

#include <AzCore/Component/Component.h>
#include <Multiplayer/IMultiplayerSpawner.h>
#include <Multiplayer/MultiplayerTypes.h>

namespace xXGameProjectNameXx
{
    class MyMultiplayerSpawnerComponent
        : public AZ::Component
        , public Multiplayer::IMultiplayerSpawner
    {
    public:

        AZ_COMPONENT_DECL(MyMultiplayerSpawnerComponent);

        //! Component descriptor interface.
        //! @{
        static void Reflect(AZ::ReflectContext* context);
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);
        //! @}

        //! Multiplayer::IMultiplayerSpawner public overrides.
        //! @{
        Multiplayer::NetworkEntityHandle OnPlayerJoin(uint64_t userId, const Multiplayer::MultiplayerAgentDatum& agentDatum) override;
        void OnPlayerLeave(Multiplayer::ConstNetworkEntityHandle entityHandle, const Multiplayer::ReplicationSet& replicationSet, AzNetworking::DisconnectReason reason) override;
        //! @}

    protected:

        //! AZ::Component protected overrides.
        //! @{
        void Activate() override;
        void Deactivate() override;
        //! @}

    private:

        Multiplayer::NetworkSpawnable m_playerSpawnable;

        AZ::EntityId m_spawnTransformEntity;
    };
} // namespace xXGameProjectNameXx
