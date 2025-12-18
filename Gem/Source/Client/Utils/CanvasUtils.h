
#pragma once

#if !AZ_TRAIT_CLIENT
#error "This file assumes it's being used for client code."
#endif // #if !AZ_TRAIT_CLIENT

namespace AZ
{
    class EntityId;
}

namespace xXGameProjectNameXx::CanvasUtils
{
    //! @brief Unload a canvas from the `UiCanvasManager`, but only if it's still active, because
    //!        the `UiCanvasManager` asserts if it's not active.
    void UnloadCanvasIfStillActive(const AZ::EntityId& canvasEntityId);
} // namespace xXGameProjectNameXx::CanvasUtils
