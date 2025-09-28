
#pragma once

#include <AzCore/Component/ComponentBus.h>

namespace xXGameProjectNameXx
{
    class MoverInputRequests
        : public AZ::ComponentBus
    {
    public:

        AZ_RTTI(xXGameProjectNameXx::MoverInputRequests, "{0AD58EEE-6A70-4146-9378-295321F4FF51}");

        virtual float GetMoveForwardAxisAutonomousInput() const = 0;
        virtual float GetMoveRightAxisAutonomousInput() const = 0;

        virtual void SetMoveForwardAxisAutonomousInput(float newValue) = 0;
        virtual void SetMoveRightAxisAutonomousInput(float newValue) = 0;

        virtual float GetMoveForwardAxisNetInput() const = 0;
        virtual float GetMoveRightAxisNetInput() const = 0;
    };

    using MoverInputRequestBus = AZ::EBus<MoverInputRequests>;

    namespace MoverInputRequestFunctions
    {
        AZ_FORCE_INLINE float GetMoveForwardAxisAutonomousInput(const AZ::EntityId& entityId)
        {
            float result = {};
            MoverInputRequestBus::EventResult(result, entityId, &MoverInputRequestBus::Events::GetMoveForwardAxisAutonomousInput);
            return result;
        }

        AZ_FORCE_INLINE float GetMoveRightAxisAutonomousInput(const AZ::EntityId& entityId)
        {
            float result = {};
            MoverInputRequestBus::EventResult(result, entityId, &MoverInputRequestBus::Events::GetMoveRightAxisAutonomousInput);
            return result;
        }

        AZ_FORCE_INLINE void SetMoveForwardAxisAutonomousInput(const AZ::EntityId& entityId, float newValue)
        {
            MoverInputRequestBus::Event(entityId, &MoverInputRequestBus::Events::SetMoveForwardAxisAutonomousInput, newValue);
        }

        AZ_FORCE_INLINE void SetMoveRightAxisAutonomousInput(const AZ::EntityId& entityId, float newValue)
        {
            MoverInputRequestBus::Event(entityId, &MoverInputRequestBus::Events::SetMoveRightAxisAutonomousInput, newValue);
        }

        AZ_FORCE_INLINE float GetMoveForwardAxisNetInput(const AZ::EntityId& entityId)
        {
            float result = {};
            MoverInputRequestBus::EventResult(result, entityId, &MoverInputRequestBus::Events::GetMoveForwardAxisNetInput);
            return result;
        }

        AZ_FORCE_INLINE float GetMoveRightAxisNetInput(const AZ::EntityId& entityId)
        {
            float result = {};
            MoverInputRequestBus::EventResult(result, entityId, &MoverInputRequestBus::Events::GetMoveRightAxisNetInput);
            return result;
        }
    }

} // namespace xXGameProjectNameXx
