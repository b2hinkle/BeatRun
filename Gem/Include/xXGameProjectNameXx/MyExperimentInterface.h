
#pragma once

#include <AzCore/Component/ComponentBus.h>

namespace xXGameProjectNameXx
{
    class MyExperimentRequests
        : public AZ::ComponentBus
    {
    public:

        AZ_RTTI(xXGameProjectNameXx::MyExperimentRequests, "{A23C0621-3CC6-48AE-A07C-3694195E3077}");
    };

    using MyExperimentRequestBus = AZ::EBus<MyExperimentRequests>;

} // namespace xXGameProjectNameXx
