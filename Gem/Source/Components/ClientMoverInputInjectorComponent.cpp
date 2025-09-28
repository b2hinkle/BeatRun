
#include <Source/Components/ClientMoverInputInjectorComponent.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <xXGameProjectNameXx/InputEventNames.h>
#include <xXGameProjectNameXx/MoverInputInterface.h>
#include <Multiplayer/IMultiplayer.h>
#include <Multiplayer/Components/NetBindComponent.h>

namespace xXGameProjectNameXx
{
    void ClientMoverInputInjectorComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<ClientMoverInputInjectorComponent, ClientMoverInputInjectorComponentBase>()
                ->Version(1)
                ;
        }

        ClientMoverInputInjectorComponentBase::Reflect(context);
    }

    void ClientMoverInputInjectorComponent::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
    {
#if AZ_TRAIT_CLIENT
        ClientMoverInputInjector::GetRequiredServices(required);
#endif // #if AZ_TRAIT_CLIENT

        ClientMoverInputInjectorComponentBase::GetRequiredServices(required);
    }

    void ClientMoverInputInjectorComponent::GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
#if AZ_TRAIT_CLIENT
        ClientMoverInputInjector::GetDependentServices(dependent);
#endif // #if AZ_TRAIT_CLIENT

        ClientMoverInputInjectorComponentBase::GetDependentServices(dependent);
    }

    void ClientMoverInputInjectorComponent::OnActivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
    }

    void ClientMoverInputInjectorComponent::OnDeactivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
    }

    ClientMoverInputInjectorComponentController::ClientMoverInputInjectorComponentController(ClientMoverInputInjectorComponent& parent)
        : ClientMoverInputInjectorComponentControllerBase(parent)
#if AZ_TRAIT_CLIENT
        , m_implementation(parent)
#endif // #if AZ_TRAIT_CLIENT
    {
    }

    void ClientMoverInputInjectorComponentController::OnActivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
#if AZ_TRAIT_CLIENT
        m_implementation.OnActivate();
#endif // #if AZ_TRAIT_CLIENT
    }

    void ClientMoverInputInjectorComponentController::OnDeactivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
#if AZ_TRAIT_CLIENT
        m_implementation.OnDeactivate();
#endif // #if AZ_TRAIT_CLIENT
    }
} // namespace xXGameProjectNameXx
