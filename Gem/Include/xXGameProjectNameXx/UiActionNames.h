
#pragma once

#if !AZ_TRAIT_CLIENT
#error "This file assumes it's being used for client code."
#endif // #if !AZ_TRAIT_CLIENT

#include <AzCore/std/string/string_view.h>

namespace xXGameProjectNameXx::UiActionNames
{
    constexpr AZStd::string_view StageButton_TheRocks_Released = "StageButton_TheRocks_Released";
    constexpr AZStd::string_view StageButton_CaveRave_Released = "StageButton_CaveRave_Released";
    constexpr AZStd::string_view StageButton_GreenLand_Released = "StageButton_GreenLand_Released";
    constexpr AZStd::string_view StageButton_SandLand_Released = "StageButton_SandLand_Released";
    constexpr AZStd::string_view StageButton_MemtoPeak_Released = "StageButton_MemtoPeak_Released";

    constexpr AZStd::string_view InGamePause_MainMenuButton_Released = "InGamePause_MainMenuButton_Released";
    constexpr AZStd::string_view InGamePause_SettingsButton_Released = "InGamePause_SettingsButton_Released";
}
