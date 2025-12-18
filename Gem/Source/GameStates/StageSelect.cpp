
#include <Source/GameStates/StageSelect.h>

#include <xXGameProjectNameXx/SettingsRegistryAccessors.h>
#if AZ_TRAIT_CLIENT
#include <LyShine/Bus/UiCanvasManagerBus.h>
#include <LyShine/Bus/UiCanvasBus.h>
#include <Source/Client/Utils/CanvasUtils.h>
#include <LyShine/Bus/UiCursorBus.h>
#include <xXGameProjectNameXx/Client/UiActionNames.h>
#endif // #if AZ_TRAIT_CLIENT
#include <AzCore/Console/ILogger.h>
#include <AzCore/Component/ComponentApplicationBus.h>
#include <xXGameProjectNameXx/LevelNames.h>
#include <O3deUtils_Misc/LevelSystemUtils.h>
#include <Source/Utils/MultiplayerUtils.h>
#include <Multiplayer/IMultiplayer.h>
#include <AzNetworking/ConnectionLayer/ConnectionEnums.h>

namespace xXGameProjectNameXx::GameStates
{
#if AZ_TRAIT_CLIENT
    void StageSelect::OnAction([[maybe_unused]] AZ::EntityId entityId, const LyShine::ActionName& actionName)
    {
        {
            AZStd::fixed_string<128> logString;

            logString += '`';
            logString += __func__;
            logString += "` called.";
            logString += ' ';
            logString += "Entity id: ";

            {
                AZStd::fixed_string<32> entityIdString;
                AZStd::to_string(entityIdString, entityId.operator AZ::u64());

                logString += entityIdString;
            }

            logString += "'.";
            logString += ' ';
            logString += "Action name: '";
            logString += actionName;
            logString += "'.";

            AZLOG_INFO(logString.data());
        }

        AZStd::string_view levelNameToLoad;

        if (actionName == UiActionNames::StageButton_TheRocks_Released)
        {
            levelNameToLoad = LevelNames::TheRocks;
        }
        else if (actionName == UiActionNames::StageButton_CaveRave_Released)
        {
            levelNameToLoad = LevelNames::CaveRave;
        }
        else if (actionName == UiActionNames::StageButton_GreenLand_Released)
        {
            levelNameToLoad = LevelNames::GreenLand;
        }
        else if (actionName == UiActionNames::StageButton_SandLand_Released)
        {
            levelNameToLoad = LevelNames::SandLand;
        }
        else if (actionName == UiActionNames::StageButton_MemtoPeak_Released)
        {
            levelNameToLoad = LevelNames::MemtoPeak;
        }

        // Make sure we aren't connected to any server before loading new levels.
        if (MultiplayerUtils::IsClient())
        {
            AZStd::fixed_string<128> logString;
            logString += "Disconnecting from the server we're currently connected to, before loading to the new level.";
            AZLOG_INFO(logString.data());

            MultiplayerUtils::GetMultiplayerAsserted().Terminate(AzNetworking::DisconnectReason::TerminatedByUser);
        }

#if AZ_TRAIT_SERVER
        // Make sure we are hosting before loading any network levels.
        if (!MultiplayerUtils::IsHosting())
        {
            MultiplayerUtils::PerformHostCommand();
        }
#endif // #if AZ_TRAIT_SERVER

        // Actually load the level now.
        O3deUtils::Misc::LevelSystemUtils::TryLoadLevel(levelNameToLoad);
    }
#endif // #if AZ_TRAIT_CLIENT

    void StageSelect::OnPushed()
    {
        GameState::IGameState::OnPushed();

#if AZ_TRAIT_CLIENT
        AZ_Assert(!m_canvasEntityId.IsValid(), "The current canvas entity ID should not have been set to anything yet!");

        // Note: [local_multiplayer] When it comes to stage selection, we want the UI to fill the entire screen, as this is a state of
        // the game where both players should see the same thing. They have to decide which stage they want to select together.
        UiCanvasManagerBus::BroadcastResult(m_canvasEntityId, &UiCanvasManagerBus::Events::LoadCanvas,
            AZStd::string(SettingsRegistryAccessors::Canvases::GetStageSelectCanvasPathname()));
        if (!m_canvasEntityId.IsValid())
        {
            AZStd::fixed_string<256> message;
            message += "Failed to load canvas '";
            message += SettingsRegistryAccessors::Canvases::GetStageSelectCanvasPathname();
            message += "'.";

            AZLOG_ERROR(message.data());
            return;
        }

        UiCanvasBus::Event(m_canvasEntityId, &UiCanvasInterface::SetEnabled, true);
#endif // #if AZ_TRAIT_CLIENT
    }

    void StageSelect::OnPopped()
    {
#if AZ_TRAIT_CLIENT
        CanvasUtils::UnloadCanvasIfStillActive(m_canvasEntityId);
        m_canvasEntityId = AZ::EntityId{AZ::EntityId::InvalidEntityId};
#endif // #if AZ_TRAIT_CLIENT

        GameState::IGameState::OnPopped();
    }

    void StageSelect::OnEnter()
    {
        GameState::IGameState::OnEnter();

#if AZ_TRAIT_CLIENT
        UiCursorBus::Broadcast(&UiCursorInterface::IncrementVisibleCounter);

        if (m_canvasEntityId.IsValid())
        {
            UiCanvasNotificationBus::Handler::BusConnect(m_canvasEntityId);
        }
#endif // #if AZ_TRAIT_CLIENT
    }

    void StageSelect::OnExit()
    {
#if AZ_TRAIT_CLIENT
        UiCursorBus::Broadcast(&UiCursorInterface::DecrementVisibleCounter);
        UiCanvasNotificationBus::Handler::BusDisconnect(m_canvasEntityId);
#endif // #if AZ_TRAIT_CLIENT

        GameState::IGameState::OnExit();
    }

    void StageSelect::OnUpdate()
    {
        GameState::IGameState::OnUpdate();
    }
} // namespace xXGameProjectNameXx::GameStates
