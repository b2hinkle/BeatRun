
#pragma once

#if !AZ_TRAIT_CLIENT
#error "This file assumes it's being used for client code."
#endif // #if !AZ_TRAIT_CLIENT

#include <AzCore/Settings/SettingsRegistry.h>

namespace xXGameProjectNameXx::Canvases
{
    constexpr AZStd::string_view StageSelectCanvasPathnameRegistryPath = "/xXGameProjectNameXx/Canvases/StageSelectPathname";

    AZ::SettingsRegistryInterface::FixedValueString GetStageSelectCanvasPathname();
} // namespace xXGameProjectNameXx::Canvases
