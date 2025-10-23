
#pragma once

namespace AZ
{
    class Component;
}

namespace Multiplayer
{
    class NetBindComponent;
}

namespace xXGameProjectNameXx::MultiplayerUtils
{
    Multiplayer::NetBindComponent& GetNetBindComponentAsserted(const AZ::Component& component);
} // namespace xXGameProjectNameXx::Utils::Multiplayer
