
#pragma once

namespace AZ
{
    template <typename T>
    class Interface;
}

namespace xXGameProjectNameXx::AzCoreUtils
{
    template <class T>
    T& GetInterfaceAsserted();

    template <class T>
    const char* TryGetTypeName();
} // namespace xXGameProjectNameXx::AzCoreUtils

#include <Source/Utils/AzCoreUtils.inl>
