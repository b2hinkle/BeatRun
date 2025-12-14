
#pragma once

#include <xXGameProjectNameXx/xXGameProjectNameXxTypeIds.h>

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace xXGameProjectNameXx
{
    class xXGameProjectNameXxRequests
    {
    public:

        AZ_RTTI(xXGameProjectNameXxRequests, GetTypeId<xXGameProjectNameXxRequests>());

        virtual ~xXGameProjectNameXxRequests() = default;
    };

    class xXGameProjectNameXxBusTraits
        : public AZ::EBusTraits
    {
    public:

        //! AZ::EBusTraits overrides
        //! @{
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //! @}
    };

    using xXGameProjectNameXxRequestBus = AZ::EBus<xXGameProjectNameXxRequests, xXGameProjectNameXxBusTraits>;
    using xXGameProjectNameXxInterface = AZ::Interface<xXGameProjectNameXxRequests>;

} // namespace xXGameProjectNameXx
