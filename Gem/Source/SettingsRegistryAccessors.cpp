
#include <xXGameProjectNameXx/SettingsRegistryAccessors.h>

#include <AzCore/Settings/SettingsRegistry.h>
#include <AzCore/Console/ILogger.h>
#include <AzCore/Debug/Trace.h>

namespace xXGameProjectNameXx::SettingsRegistryAccessors
{
#if AZ_TRAIT_CLIENT
    namespace Canvases
    {
        AZ::SettingsRegistryInterface::FixedValueString GetStageSelectCanvasPathname()
        {
            const AZ::SettingsRegistryInterface* settingsRegistry = AZ::SettingsRegistry::Get();
            AZ_Assert(settingsRegistry, "Should be valid.");

            AZ::SettingsRegistryInterface::FixedValueString result;
            const bool hasRetrievedValue = settingsRegistry->Get(result, StageSelectCanvasPathnameRegistryPath);

            if (!hasRetrievedValue)
            {
                AZStd::fixed_string<256> message;
                message += "No value specified for settings registry path '";
                message += StageSelectCanvasPathnameRegistryPath;
                message += "'.";

                AZLOG_ERROR(message.data());
            }

            return result;
        }
    }
#endif // #if AZ_TRAIT_CLIENT

#if AZ_TRAIT_CLIENT
    namespace UI
    {
        AZ::SettingsRegistryInterface::FixedValueString GetCursorTexturePathname()
        {
            const AZ::SettingsRegistryInterface* settingsRegistry = AZ::SettingsRegistry::Get();
            AZ_Assert(settingsRegistry, "Should be valid.");

            AZ::SettingsRegistryInterface::FixedValueString result;
            const bool hasRetrievedValue = settingsRegistry->Get(result, CursorTexturePathnameRegistryPath);

            if (!hasRetrievedValue)
            {
                AZStd::fixed_string<256> message;
                message += "No value specified for settings registry path '";
                message += CursorTexturePathnameRegistryPath;
                message += "'.";

                AZLOG_ERROR(message.data());
            }

            return result;
        }
    }
#endif // #if AZ_TRAIT_CLIENT
} // namespace xXGameProjectNameXx::Canvases
