
#include <Source/GameStates/StageSelect.h>

#if AZ_TRAIT_CLIENT
#include <Source/UI/Canvases.h>
#include <LyShine/Bus/UiCanvasManagerBus.h>
#include <LyShine/Bus/UiCanvasBus.h>
#include <Source/Utils/CanvasUtils.h>
#endif // #if AZ_TRAIT_CLIENT
#include <AzCore/Console/ILogger.h>
#include <AzCore/Component/ComponentApplicationBus.h>

namespace xXGameProjectNameXx::GameStates
{
    void StageSelect::OnPushed()
    {
        GameState::IGameState::OnPushed();

#if AZ_TRAIT_CLIENT
        UiCanvasManagerBus::BroadcastResult(
            m_canvasEntityId,
            &UiCanvasManagerInterface::LoadCanvas,
            AZStd::string(Canvases::GetStageSelectCanvasPathname()));

        if (!m_canvasEntityId.IsValid())
        {
            AZStd::fixed_string<256> message;
            message += "Failed to load canvas '";
            message += Canvases::GetStageSelectCanvasPathname();
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
    }

    void StageSelect::OnExit()
    {
        GameState::IGameState::OnExit();
    }

    void StageSelect::OnUpdate()
    {
        GameState::IGameState::OnUpdate();
    }
} // namespace xXGameProjectNameXx::GameStates
