
#pragma once

#include <Source/AutoGen/MoverInputComponent.AutoComponent.h>

namespace xXGameProjectNameXx
{
    class MoverInputComponentController
        : public MoverInputComponentControllerBase
    {
    public:

        explicit MoverInputComponentController(MoverInputComponent& parent);

        //! MoverInputComponentControllerBase public overrides.
        //! @{
        void OnActivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;
        //! @}
    };
} // namespace xXGameProjectNameXx
