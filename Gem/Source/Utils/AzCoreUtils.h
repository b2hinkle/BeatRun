
#pragma once

#include <CppUtils_Concepts/Std.h>
#include <AzCore/Component/Component.h>
#include <type_traits>
#include <CppUtils_Concepts.h>

namespace AZ
{
    template <typename T>
    class Interface;

    class Entity;
}

namespace xXGameProjectNameXx::AzCoreUtils
{
    template <class T>
    T& GetInterfaceAsserted();

    template <class T>
    const char* TryGetTypeName();

    template <CppUtils::Concepts::PointerToDerivedFrom<AZ::Component> TComponentPtr>
    TComponentPtr FindComponent(const AZ::Entity& entity);

    template <CppUtils::Concepts::ReferenceToDerivedFrom<AZ::Component> TComponentRef>
    TComponentRef FindComponent(const AZ::Entity& entity);
} // namespace xXGameProjectNameXx::AzCoreUtils

#include <Source/Utils/AzCoreUtils.inl>
