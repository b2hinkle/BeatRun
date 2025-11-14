
#pragma once

#include <AzCore/Component/ComponentBus.h>

namespace xXGameProjectNameXx
{
    class MoverRequests
        : public AZ::ComponentBus
    {
    public:

        AZ_RTTI(xXGameProjectNameXx::MoverRequests, "{F897F2EB-4A88-4E44-BBE9-CA8EA05BF9A2}");

        virtual void TickGameplay(float deltaTime) const = 0;

        virtual float GetMoveForwardAxis() const = 0;
        virtual float GetMoveRightAxis() const = 0;

        virtual void SetMoveForwardAxis(float newValue) = 0;
        virtual void SetMoveRightAxis(float newValue) = 0;
    };

    using MoverRequestBus = AZ::EBus<MoverRequests>;

    namespace MoverRequestFunctions
    {
        AZ_FORCE_INLINE float TickGameplay(const AZ::EntityId& entityId, float deltaTime)
        {
            MoverRequestBus::Event(entityId, &MoverRequestBus::Events::TickGameplay, deltaTime);
        }

        AZ_FORCE_INLINE float GetMoveForwardAxis(const AZ::EntityId& entityId)
        {
            float result = {};
            MoverRequestBus::EventResult(result, entityId, &MoverRequestBus::Events::GetMoveForwardAxis);
            return result;
        }

        AZ_FORCE_INLINE float GetMoveRightAxis(const AZ::EntityId& entityId)
        {
            float result = {};
            MoverRequestBus::EventResult(result, entityId, &MoverRequestBus::Events::GetMoveRightAxis);
            return result;
        }

        AZ_FORCE_INLINE void SetMoveForwardAxis(const AZ::EntityId& entityId, float newValue)
        {
            MoverRequestBus::Event(entityId, &MoverRequestBus::Events::SetMoveForwardAxis, newValue);
        }

        AZ_FORCE_INLINE void SetMoveRightAxis(const AZ::EntityId& entityId, float newValue)
        {
            MoverRequestBus::Event(entityId, &MoverRequestBus::Events::SetMoveRightAxis, newValue);
        }
    }

} // namespace xXGameProjectNameXx
