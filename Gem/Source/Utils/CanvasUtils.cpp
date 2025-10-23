
#if !AZ_TRAIT_CLIENT
#error "This file assumes it's being used for client code."
#endif // #if !AZ_TRAIT_CLIENT

#include <Source/Utils/CanvasUtils.h>

#include <AzCore/Console/ILogger.h>
#include <AzCore/Component/ComponentApplicationBus.h>
#include <Source/UI/Canvases.h>
#include <LyShine/Bus/UiCanvasManagerBus.h>
#include <LyShine/Bus/UiCanvasBus.h>

namespace xXGameProjectNameXx::CanvasUtils
{
    void UnloadCanvasIfStillActive(const AZ::EntityId& canvasEntityId)
    {
        if (canvasEntityId.IsValid() == false)
        {
            return;
        }

        const AZ::Entity* foundCanvasEntity = nullptr;
        AZ::ComponentApplicationBus::BroadcastResult(foundCanvasEntity, &AZ::ComponentApplicationBus::Events::FindEntity, canvasEntityId);

        if (!foundCanvasEntity)
        {
            return;
        }

        if (foundCanvasEntity->GetState() != AZ::Entity::State::Active)
        {
            return;
        }

        UiCanvasManagerBus::Broadcast(
            &UiCanvasManagerInterface::UnloadCanvas,
            canvasEntityId);
    }
} // namespace xXGameProjectNameXx::CanvasUtils
