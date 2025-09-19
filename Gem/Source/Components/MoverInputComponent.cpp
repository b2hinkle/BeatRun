
#include <Source/Components/MoverInputComponent.h>

namespace xXGameProjectNameXx
{
    MoverInputComponentController::MoverInputComponentController(MoverInputComponent& parent)
        : MoverInputComponentControllerBase(parent)
    {
    }

    void MoverInputComponentController::OnActivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
    }

    void MoverInputComponentController::OnDeactivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
    }
}
