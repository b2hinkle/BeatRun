
#include <Source/Utils/AzFrameworkUtils.h>

#include <AzFramework/Spawnable/RootSpawnableInterface.h>
#include <AzCore/PlatformDef.h>

namespace
{
    //! @brief Listens for root spawnable notifications and stores the latest state from them.
    class RootSpawnableStateTracker final
        : private AzFramework::RootSpawnableNotificationBus::Handler
    {
    public:

        RootSpawnableStateTracker();
        ~RootSpawnableStateTracker();

        AZ_INLINE bool IsRootSpawnableReady() const { return m_isRootSpawnableReady; }

    private:

        //! AzFramework::RootSpawnableNotificationBus::Handler overrides.
        //! @{
        void OnRootSpawnableAssigned(AZ::Data::Asset<AzFramework::Spawnable>, uint32_t) override;
        void OnRootSpawnableReady(AZ::Data::Asset<AzFramework::Spawnable>, uint32_t) override;
        void OnRootSpawnableReleased(uint32_t) override;
        //! @}

    private:

        bool m_isRootSpawnableReady = false;
    } theRootSpawnableStateTracker;
}

namespace xXGameProjectNameXx::AzFrameworkUtils
{
    bool IsRootSpawnableReady()
    {
        return theRootSpawnableStateTracker.IsRootSpawnableReady();
    }
} // namespace xXGameProjectNameXx::AzFrameworkUtils

namespace
{
    RootSpawnableStateTracker::RootSpawnableStateTracker()
    {
        AzFramework::RootSpawnableNotificationBus::Handler::BusConnect();
    }

    RootSpawnableStateTracker::~RootSpawnableStateTracker()
    {
        AzFramework::RootSpawnableNotificationBus::Handler::BusDisconnect();
    }

    void RootSpawnableStateTracker::OnRootSpawnableAssigned(AZ::Data::Asset<AzFramework::Spawnable>, uint32_t)
    {
        m_isRootSpawnableReady = false;
    }

    void RootSpawnableStateTracker::OnRootSpawnableReady(AZ::Data::Asset<AzFramework::Spawnable>, uint32_t)
    {
        m_isRootSpawnableReady = true;
    }

    void RootSpawnableStateTracker::OnRootSpawnableReleased(uint32_t)
    {
        m_isRootSpawnableReady = false;
    }
}
