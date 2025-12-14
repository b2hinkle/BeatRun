
#pragma once

#include <AzCore/std/string/string_view.h>

namespace xXGameProjectNameXx
{
    class xXGameProjectNameXxSystemComponent;
    class xXGameProjectNameXxModule;
    class xXGameProjectNameXxRequests;
    class PlayerSystemComponent;
    class PlayerRequests;
}

namespace xXGameProjectNameXx
{
    //! @brief Primary "type id" type traits template definition.
    template <class T>
    struct TypeIdTrait
    {
        static_assert(false && sizeof(T), "No `TypeIdTrait` specialization defined for `T`!");
    };

    template <class T>
    consteval AZStd::string_view GetTypeId()
    {
        return TypeIdTrait<T>::value;
    }

    template <>
    struct TypeIdTrait<xXGameProjectNameXxSystemComponent>
    {
        static inline constexpr AZStd::string_view value = "{F702E51B-D126-40F2-A2B0-15A13E088636}";
    };

    template <>
    struct TypeIdTrait<xXGameProjectNameXxModule>
    {
        static inline constexpr AZStd::string_view value = "{314CCCF8-1076-48FE-8398-FAEEAB4AC891}";
    };

    template <>
    struct TypeIdTrait<xXGameProjectNameXxRequests>
    {
        static inline constexpr AZStd::string_view value = "{5FBFF715-E25D-4E0F-BDA6-8810CC66D8F1}";
    };

    template <>
    struct TypeIdTrait<PlayerSystemComponent>
    {
        static inline constexpr AZStd::string_view value = "{44C0F7ED-BE60-4C79-9B51-12F9A801EFC4}";
    };

    template <>
    struct TypeIdTrait<PlayerRequests>
    {
        static inline constexpr AZStd::string_view value = "{D865EBE8-0ACC-4500-A2CF-4DF0CD66D8D6}";
    };
} // namespace xXGameProjectNameXx
