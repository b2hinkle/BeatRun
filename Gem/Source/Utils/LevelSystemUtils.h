
#pragma once

#include <AzCore/std/string/string_view.h>

namespace xXGameProjectNameXx::LevelSystemUtils
{
    void TryLoadLevel(const AZStd::string_view& levelName);

    void LoadLevel(const AZStd::string_view& levelName);
} // namespace xXGameProjectNameXx::LevelSystemUtils
