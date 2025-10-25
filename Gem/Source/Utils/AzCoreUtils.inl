
#pragma once

#include <Source/Utils/AzCoreUtils.h>

#include <AzCore/Interface/Interface.h>
#include <AzCore/Debug/Trace.h>
#include <AzCore/Console/ILogger.h>
#include <AzCore/RTTI/TypeInfo.h>
#include <AzCore/RTTI/TypeInfoSimple.h>
#include <AzCore/std/string/string_view.h>

template <class T>
T& xXGameProjectNameXx::AzCoreUtils::GetInterfaceAsserted()
{
    T* interface = AZ::Interface<T>::Get();

#if AZ_ENABLE_TRACING
    {
        AZStd::fixed_string<128> assertString;

        assertString += '`';
        assertString += __func__;
        assertString += "`: ";
        assertString += "The interface for `";
        assertString += TryGetTypeName<T>();
        assertString += "` is currently null!";

        AZ_Assert(interface, assertString.data());
    }
#endif // #if AZ_ENABLE_TRACING

    return *interface;
}

template <class T>
const char* xXGameProjectNameXx::AzCoreUtils::TryGetTypeName()
{
    if constexpr (AZ::Internal::HasAzTypeInfo_v)
    {
        return AZ::AzTypeInfo<T>::Name();
    }

    {
        AZStd::fixed_string<128> logString;

        logString += '`';
        logString += __func__;
        logString += "`: ";
        logString += "No type info defined. I.e., it does not use an `AZ_TYPE_INFO` macro.";

        AZLOG_WARN(logString.data());
    }

    return "(no type info defined)";
}
