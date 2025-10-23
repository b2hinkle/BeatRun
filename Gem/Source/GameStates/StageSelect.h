
#pragma once

#include <GameState/GameState.h>
#include <AzCore/Component/EntityId.h>

namespace xXGameProjectNameXx::GameStates
{
    //! @class StageSelect
    class StageSelect
        : public GameState::IGameState
    {
    public:

        AZ_CLASS_ALLOCATOR(GameStates::StageSelect, AZ::SystemAllocator);

        AZ_RTTI(GameStates::StageSelect, "{254EB57F-6827-45FF-9793-8742DC9DB542}", GameState::IGameState);

    protected:

        //! GameState::IGameState protected overrides.
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
