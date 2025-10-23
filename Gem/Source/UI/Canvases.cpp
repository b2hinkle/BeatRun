
#if !AZ_TRAIT_CLIENT
#error "This file assumes it's being used for client code."
#endif // #if !AZ_TRAIT_CLIENT

#include <Source/UI/Canvases.h>

#include <AzCore/Settings/SettingsRegistry.h>
#include <AzCore/Console/ILogger.h>

namespace xXGameProjectNameXx::Canvases
{
    AZ::SettingsRegistryInterface::FixedValueString GetStageSelectCanvasPathname()
    {
        const AZ::SettingsRegistryInterface* settingsRegistry = AZ::SettingsRegistry::Get();
        AZ_Assert(settingsRegistry, "Should be valid.");

        AZ::SettingsRegistryInterface::FixedValueString pathname;
        const bool hasRetrievedValue = settingsRegistry->Get(pathname, StageSelectCanvasPathnameRegistryPath);

        if (!hasRetrievedValue)
        {
            AZStd::fixed_string<256> message;
            message += "No value specified for settings registry path '";
            message += StageSelectCanvasPathnameRegistryPath;
            message += "'.";

            AZLOG_ERROR(message.data());
        }

        return pathname;
    }
} // namespace xXGameProjectNameXx::Canvases
