
#pragma once

#include <Source/AutoGen/MoverClientInputInjectorComponent.AutoComponent.h>
#if AZ_TRAIT_CLIENT
#include <Source/Input/ClientMoverInputInjector.h>
#endif // #if AZ_TRAIT_CLIENT

namespace xXGameProjectNameXx
{
    //! @class MoverClientInputInjectorComponent
    class MoverClientInputInjectorComponent
        : public MoverClientInputInjectorComponentBase
    {
    public:

        AZ_MULTIPLAYER_COMPONENT(xXGameProjectNameXx::MoverClientInputInjectorComponent, s_moverClientInputInjectorComponentConcreteUuid, xXGameProjectNameXx::MoverClientInputInjectorComponentBase);

        //! Component descriptor interface.
        //! @{
        static void Reflect(AZ::ReflectContext* context);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);
        //! @}

        //! MoverClientInputInjectorComponentBase public overrides.
        //! @{
        void OnActivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;
        //! @}
    };

    //! @class MoverClientInputInjectorComponentController
    class MoverClientInputInjectorComponentController
        : public MoverClientInputInjectorComponentControllerBase
    {
    public:

        explicit MoverClientInputInjectorComponentController(MoverClientInputInjectorComponent& parent);

        //! MoverClientInputInjectorComponentControllerBase public overrides.
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
