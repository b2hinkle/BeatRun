
#include <Source/Components/StageSelectComponent.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <GameState/GameStateRequestBus.h>
#include <Source/GameStates/StageSelect.h>

namespace xXGameProjectNameXx
{
    AZ_COMPONENT_IMPL(StageSelectComponent, "StageSelectComponent", "{96A1C17F-77D9-42D0-A6E8-9DAC3B5CAB71}");

    void StageSelectComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<StageSelectComponent, AZ::Component>()
                ->Version(1)
                ;

            if (AZ::EditContext* editContext = serializeContext->GetEditContext())
            {
                editContext->Class<StageSelectComponent>("StageSelectComponent", "[Description of functionality provided by this component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Category, "ComponentCategory")
                    ->Attribute(AZ::Edit::Attributes::Icon, "Icons/Components/Component_Placeholder.svg")
                    ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC_CE("Level"))
                    ;
            }
        }

        if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->Class<StageSelectComponent>("StageSelect Component Group")
                ->Attribute(AZ::Script::Attributes::Category, "xXGameProjectNameXx Gem Group")
                ;
        }
    }

    void StageSelectComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("StageSelectComponentService"));
    }

    void StageSelectComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("StageSelectComponentService"));
    }

    void StageSelectComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void StageSelectComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    void StageSelectComponent::Activate()
    {
        // @Christian: [editor] Usages of the GameState gem are disabled in editor because the GameState gem does not provide an editor version of their target. So
        // their system component does not activate or anything.
#ifndef EDITOR
        GameState::GameStateRequests::CreateAndPushNewOverridableGameStateOfType<GameStates::StageSelect>();
#endif // #ifndef EDITOR
    }

    void StageSelectComponent::Deactivate()
    {
        // @Christian: [editor] Usages of the GameState gem are disabled in editor because the GameState gem does not provide an editor version of their target. So
        // their system component does not activate or anything.
#ifndef EDITOR
        // First, pop any game states on top of the stage select state.
        GameState::GameStateRequests::PopActiveGameStateUntilOfType<GameStates::StageSelect>();

        // Now, pop the stage select state itself.
        GameState::GameStateRequestBus::Broadcast(&GameState::GameStateRequests::PopActiveGameState);

        // @Christian: [ui][bug[engine]] Note: When the game is shutdown, we get the assertion message: "The following font is being freed but still in use by a FontFamily". This is
        // okay. It's not caused by anything we're doing wrong. I debugged it, and all of the shared pointers to the loaded `FontFamily` get destructed and its ref count
        // decrements to zero, but it seems to be an engine but that `AZ::AtomFont::ReleaseFontFamily` is not getting called (which the code says it should be getting
        // called automatically when the "final FontFamily shared_ptr is destroyed"), so dangling pointers remain in their `AZ::AtomFont::m_fontFamilyReverseLookup` data
        // member. Dangling pointers sound bad, but it doesn't seem to be affecting our end product, the game is being shutdown anyway in this example and the `AZ::AtomFont` object
        // itself is in the process of destructing, so those dangling pointers are going to go away anyways right after. I guess the concern would be about possible crashes before
        // this point though. I guess there is a brief moment (maybe a few ticks Idk) where these dangling pointers are just hanging out.
#endif // #ifndef EDITOR
    }
} // namespace xXGameProjectNameXx
