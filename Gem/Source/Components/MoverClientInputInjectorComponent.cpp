
#include <Source/Components/MoverClientInputInjectorComponent.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <Multiplayer/IMultiplayer.h>
#include <Multiplayer/Components/NetBindComponent.h>

namespace xXGameProjectNameXx
{
    void MoverClientInputInjectorComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<MoverClientInputInjectorComponent, MoverClientInputInjectorComponentBase>()
                ->Version(1)
                ;
        }

        MoverClientInputInjectorComponentBase::Reflect(context);
    }

    void MoverClientInputInjectorComponent::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
    {
#if AZ_TRAIT_CLIENT
        ClientMoverInputInjector::GetRequiredServices(required);
#endif // #if AZ_TRAIT_CLIENT

        MoverClientInputInjectorComponentBase::GetRequiredServices(required);
    }

    void MoverClientInputInjectorComponent::GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
#if AZ_TRAIT_CLIENT
        ClientMoverInputInjector::GetDependentServices(dependent);
#endif // #if AZ_TRAIT_CLIENT

        MoverClientInputInjectorComponentBase::GetDependentServices(dependent);
    }

    void MoverClientInputInjectorComponent::OnActivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
    }

    void MoverClientInputInjectorComponent::OnDeactivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
    }

    MoverClientInputInjectorComponentController::MoverClientInputInjectorComponentController(MoverClientInputInjectorComponent& parent)
        : MoverClientInputInjectorComponentControllerBase(parent)
#if AZ_TRAIT_CLIENT
        , m_implementation(parent)
#endif // #if AZ_TRAIT_CLIENT
    {
    }

    void MoverClientInputInjectorComponentController::OnActivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
#if AZ_TRAIT_CLIENT
        m_implementation.OnActivate();
#endif // #if AZ_TRAIT_CLIENT
    }

    void MoverClientInputInjectorComponentController::OnDeactivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
#if AZ_TRAIT_CLIENT
        m_implementation.OnDeactivate();
#endif // #if AZ_TRAIT_CLIENT
    }
} // namespace xXGameProjectNameXx
