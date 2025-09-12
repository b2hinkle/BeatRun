
#pragma once

#include <AzCore/Component/ComponentBus.h>

namespace xXGameProjectNameXx
{
    class MyExperimentRequests
        : public AZ::ComponentBus
    {
    public:
        AZ_RTTI(xXGameProjectNameXx::MyExperimentRequests, "{A23C0621-3CC6-48AE-A07C-3694195E3077}");

        // Put your public request methods here.
        
        // Put notification events here. Examples:
        // void RegisterEvent(AZ::EventHandler<...> notifyHandler);
        // AZ::Event<...> m_notifyEvent1;
        
    };

    using MyExperimentRequestBus = AZ::EBus<MyExperimentRequests>;

} // namespace xXGameProjectNameXx
