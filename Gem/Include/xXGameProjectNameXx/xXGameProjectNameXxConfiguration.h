
#pragma once

#include <AzCore/PlatformDef.h>

#if defined(AZ_MONOLITHIC_BUILD)
#   define XXGAMEPROJECTNAMEXX_API
#else
#   if defined(XXGAMEPROJECTNAMEXX_EXPORTS)
#       define XXGAMEPROJECTNAMEXX_API AZ_DLL_EXPORT
#   else
#       define XXGAMEPROJECTNAMEXX_API AZ_DLL_IMPORT
#   endif
#endif
