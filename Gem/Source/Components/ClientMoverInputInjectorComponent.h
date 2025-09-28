
#pragma once

#include <Source/AutoGen/ClientMoverInputInjectorComponent.AutoComponent.h>
#if AZ_TRAIT_CLIENT
#include <Source/Input/ClientMoverInputInjector.h>
#endif // #if AZ_TRAIT_CLIENT

namespace xXGameProjectNameXx
{
    //! @class ClientMoverInputInjectorComponent
    class ClientMoverInputInjectorComponent
        : public ClientMoverInputInjectorComponentBase
    {
    public:

        AZ_MULTIPLAYER_COMPONENT(xXGameProjectNameXx::ClientMoverInputInjectorComponent, s_clientMoverInputInjectorComponentConcreteUuid, xXGameProjectNameXx::ClientMoverInputInjectorComponentBase);

        //! Component descriptor interface.
        //! @{
        static void Reflect(AZ::ReflectContext* context);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);
        //! @}

        //! ClientMoverInputInjectorComponentBase public overrides.
        //! @{
        void OnActivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;
        //! @}
    };

    //! @class ClientMoverInputInjectorComponentController
    class ClientMoverInputInjectorComponentController
        : public ClientMoverInputInjectorComponentControllerBase
    {
    public:

        explicit ClientMoverInputInjectorComponentController(ClientMoverInputInjectorComponent& parent);

        //! ClientMoverInputInjectorComponentControllerBase public overrides.
        //! @{
        void OnActivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;
        //! @}

    private:

#if AZ_TRAIT_CLIENT
        //! @brief The local input listening code, isolated from any multiplayer component logic.
        ClientMoverInputInjector m_implementation;
#endif // #if AZ_TRAIT_CLIENT
    };
} // namespace xXGameProjectNameXx
