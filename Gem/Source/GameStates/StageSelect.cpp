
#include <Source/GameStates/StageSelect.h>

#include <Include/xXGameProjectNameXx/SettingsRegistryAccessors.h>
#if AZ_TRAIT_CLIENT
#include <LyShine/Bus/UiCanvasManagerBus.h>
#include <LyShine/Bus/UiCanvasBus.h>
#include <Source/Utils/CanvasUtils.h>
#include <LyShine/Bus/UiButtonBus.h>
#include <LyShine/Bus/UiCursorBus.h>
#endif // #if AZ_TRAIT_CLIENT
#include <AzCore/Console/ILogger.h>
#include <AzCore/Component/ComponentApplicationBus.h>

namespace xXGameProjectNameXx::GameStates
{
#if AZ_TRAIT_CLIENT
    void StageSelect::OnButtonClick()
    {
        const AZ::EntityId* currentBusIdPtr = UiButtonNotificationBus::GetCurrentBusId();
        AZ_Assert(currentBusIdPtr, "This cannot be null since we are currently in a bus callback.");
        [[maybe_unused]] const AZ::EntityId& currentBusId = *currentBusIdPtr;

        // @Christian: TODO: [todo][ui] Use this to handle cpp button click event callbacks if we ever convert
        // the UI canvas to cpp where we'd have to create each button individually. See: `LyShineExamplesCppExample` for reference.
    }
#endif // #if AZ_TRAIT_CLIENT

    void StageSelect::OnPushed()
    {
        GameState::IGameState::OnPushed();

#if AZ_TRAIT_CLIENT
        UiCanvasManagerBus::BroadcastResult(
            m_canvasEntityId,
            &UiCanvasManagerInterface::LoadCanvas,
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
#endif // #if AZ_TRAIT_CLIENT

        GameState::IGameState::OnPopped();
    }

    void StageSelect::OnEnter()
    {
        GameState::IGameState::OnEnter();

#if AZ_TRAIT_CLIENT
        UiCursorBus::Broadcast(&UiCursorInterface::IncrementVisibleCounter);
        UiButtonNotificationBus::MultiHandler::BusConnect(m_canvasEntityId);
#endif // #if AZ_TRAIT_CLIENT
    }

    void StageSelect::OnExit()
    {
#if AZ_TRAIT_CLIENT
        UiCursorBus::Broadcast(&UiCursorInterface::DecrementVisibleCounter);
        UiButtonNotificationBus::MultiHandler::BusDisconnect(m_canvasEntityId);
#endif // #if AZ_TRAIT_CLIENT

        GameState::IGameState::OnExit();
    }

    void StageSelect::OnUpdate()
    {
        GameState::IGameState::OnUpdate();
    }
} // namespace xXGameProjectNameXx::GameStates
