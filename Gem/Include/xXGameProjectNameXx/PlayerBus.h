
#pragma once

#include <xXGameProjectNameXx/xXGameProjectNameXxTypeIds.h>

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace xXGameProjectNameXx
{
    class PlayerRequests
    {
    public:

        AZ_RTTI(PlayerRequests, GetTypeId<PlayerRequests>());

        virtual ~PlayerRequests() = default;
    };

    class PlayerBusTraits
        : public AZ::EBusTraits
    {
    public:

        //! AZ::EBusTraits overrides.
        //! @{
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //! @}
    };

    using PlayerRequestBus = AZ::EBus<PlayerRequests, PlayerBusTraits>;
    using PlayerInterface = AZ::Interface<PlayerRequests>;

} // namespace xXGameProjectNameXx
