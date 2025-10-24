
#pragma once

namespace AZ
{
    class Component;
}

namespace Multiplayer
{
    class IMultiplayer;
    class NetBindComponent;
}

namespace xXGameProjectNameXx::MultiplayerUtils
{
    //! @brief A version of `Multiplayer::GetMultiplayer` that returns a reference rather than a pointer.
    Multiplayer::IMultiplayer& GetMultiplayerAsserted();

    //! @brief A mirrored implementation of `MultiplayerSystemComponent::IsHosting`.
    bool IsHosting();

    bool IsClient();

    //! @brief Starts hosting. Same behavior as the "Host" console command.
    void PerformHostCommand();

    Multiplayer::NetBindComponent& GetNetBindComponentAsserted(const AZ::Component& component);
} // namespace xXGameProjectNameXx::MultiplayerUtils
