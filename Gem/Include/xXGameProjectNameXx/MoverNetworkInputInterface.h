
#pragma once

#include <AzCore/Component/ComponentBus.h>

namespace xXGameProjectNameXx
{
    class MoverNetworkInputRequests
        : public AZ::ComponentBus
    {
    public:

        AZ_RTTI(xXGameProjectNameXx::MoverNetworkInputRequests, "{0AD58EEE-6A70-4146-9378-295321F4FF51}");

        virtual float GetMoveForwardAxis() const = 0;
        virtual float GetMoveRightAxis() const = 0;

        virtual void SetMoveForwardAxis(float newValue) = 0;
        virtual void SetMoveRightAxis(float newValue) = 0;
    };

    using MoverNetworkInputRequestBus = AZ::EBus<MoverNetworkInputRequests>;

    namespace MoverNetworkInputRequestFunctions
    {
        AZ_FORCE_INLINE float GetMoveForwardAxis(const AZ::EntityId& entityId)
        {
            float result = {};
            MoverNetworkInputRequestBus::EventResult(result, entityId, &MoverNetworkInputRequestBus::Events::GetMoveForwardAxis);
            return result;
        }

        AZ_FORCE_INLINE float GetMoveRightAxis(const AZ::EntityId& entityId)
        {
            float result = {};
            MoverNetworkInputRequestBus::EventResult(result, entityId, &MoverNetworkInputRequestBus::Events::GetMoveRightAxis);
            return result;
        }

        AZ_FORCE_INLINE void SetMoveForwardAxis(const AZ::EntityId& entityId, float newValue)
        {
            MoverNetworkInputRequestBus::Event(entityId, &MoverNetworkInputRequestBus::Events::SetMoveForwardAxis, newValue);
        }

        AZ_FORCE_INLINE void SetMoveRightAxis(const AZ::EntityId& entityId, float newValue)
        {
            MoverNetworkInputRequestBus::Event(entityId, &MoverNetworkInputRequestBus::Events::SetMoveRightAxis, newValue);
        }
    }

} // namespace xXGameProjectNameXx
