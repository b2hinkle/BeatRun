
#pragma once

#if !AZ_TRAIT_CLIENT
#error "This file assumes it's being used for client code."
#endif // #if !AZ_TRAIT_CLIENT

#include <AzCore/std/string/string_view.h>

namespace xXGameProjectNameXx::InputEventNames
{
    constexpr AZStd::string_view MoveForwardAxis = "MoveForwardAxis";
    constexpr AZStd::string_view MoveRightAxis = "MoveRightAxis";

    constexpr AZStd::string_view InGamePauseMenu = "InGamePauseMenu";
}
