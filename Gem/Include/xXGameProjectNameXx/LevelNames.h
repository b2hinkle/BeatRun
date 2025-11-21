
#pragma once

#include <AzCore/std/string/string_view.h>

namespace xXGameProjectNameXx::LevelNames
{
    constexpr AZStd::string_view DefaultLevel = "DefaultLevel";
    constexpr AZStd::string_view GameplayDevelopmentLevel = "GameplayDevelopmentLevel";
    constexpr AZStd::string_view MainMenuLevel = "MainMenuLevel";

    // @Christian: TODO: [todo][level][placeholder] These values just redirect to the development level, for now. These level names are kind of
    // placeholder anyway. But if we were serious, we would have actual level prefabs for each level.
    constexpr AZStd::string_view TheRocks = GameplayDevelopmentLevel;
    constexpr AZStd::string_view CaveRave = GameplayDevelopmentLevel;
    constexpr AZStd::string_view GreenLand = GameplayDevelopmentLevel;
    constexpr AZStd::string_view SandLand = GameplayDevelopmentLevel;
    constexpr AZStd::string_view MemtoPeak = GameplayDevelopmentLevel;
}
