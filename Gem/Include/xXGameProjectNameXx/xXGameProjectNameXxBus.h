
#pragma once

#include <xXGameProjectNameXx/xXGameProjectNameXxTypeIds.h>

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace xXGameProjectNameXx
{
    class xXGameProjectNameXxRequests
    {
    public:
        AZ_RTTI(xXGameProjectNameXxRequests, xXGameProjectNameXxRequestsTypeId);
        virtual ~xXGameProjectNameXxRequests() = default;
        // Put your public methods here
    };

    class xXGameProjectNameXxBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using xXGameProjectNameXxRequestBus = AZ::EBus<xXGameProjectNameXxRequests, xXGameProjectNameXxBusTraits>;
    using xXGameProjectNameXxInterface = AZ::Interface<xXGameProjectNameXxRequests>;

} // namespace xXGameProjectNameXx
