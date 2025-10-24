
#pragma once

#include <GameState/GameState.h>
#include <AzCore/Component/EntityId.h>
#if AZ_TRAIT_CLIENT
#include <LyShine/Bus/UiButtonBus.h>
#endif // #if AZ_TRAIT_CLIENT

namespace xXGameProjectNameXx::GameStates
{
    //! @class StageSelect
    class StageSelect
        : public GameState::IGameState
#if AZ_TRAIT_CLIENT
        , public UiButtonNotificationBus::MultiHandler
#endif // #if AZ_TRAIT_CLIENT
    {
    public:

        AZ_CLASS_ALLOCATOR(GameStates::StageSelect, AZ::SystemAllocator);

        AZ_RTTI(GameStates::StageSelect, "{254EB57F-6827-45FF-9793-8742DC9DB542}", GameState::IGameState);

    public:

#if AZ_TRAIT_CLIENT
        //! UiButtonNotificationBus::MultiHandler public overrides.
        //! @{
        void OnButtonClick() override;
        //! @}
#endif // #if AZ_TRAIT_CLIENT

    protected:

        //! GameState::IGameState protected overrides.
        //! @{
        void OnPushed() override;
        void OnPopped() override;
        void OnEnter() override;
        void OnExit() override;
        void OnUpdate() override;
        //! @}

    private:

        AZ::EntityId m_canvasEntityId = AZ::EntityId();
    };
} // namespace xXGameProjectNameXx::GameStates
