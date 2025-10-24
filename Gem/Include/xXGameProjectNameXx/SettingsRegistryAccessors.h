
#pragma once

#include <AzCore/Settings/SettingsRegistry.h>

namespace xXGameProjectNameXx::SettingsRegistryAccessors
{
#if AZ_TRAIT_CLIENT
    namespace Canvases
    {
        constexpr AZStd::string_view StageSelectCanvasPathnameRegistryPath = "/xXGameProjectNameXx/Canvases/StageSelectPathname";

        AZ::SettingsRegistryInterface::FixedValueString GetStageSelectCanvasPathname();
    }
#endif // #if AZ_TRAIT_CLIENT

#if AZ_TRAIT_CLIENT
    namespace UI
    {
        constexpr AZStd::string_view CursorTexturePathnameRegistryPath = "/xXGameProjectNameXx/UI/CursorTexturePathname";

        AZ::SettingsRegistryInterface::FixedValueString GetCursorTexturePathname();
    }
#endif // #if AZ_TRAIT_CLIENT
} // namespace xXGameProjectNameXx
