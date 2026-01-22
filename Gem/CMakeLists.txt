
# Setup the gem meta variables that includes the "gem_path", "gem_name" and "gem_version"
# The "pal_dir" variable is also set which refers to the Platform/<platform-name> directory
# based on the directory of this CMakeLists.txt
o3de_gem_setup("xXGameProjectNameXx")

string(TOLOWER ${gem_name} gem_name_lowercase)
string(TOUPPER ${gem_name} gem_name_uppercase)

# Now that we have the platform abstraction layer (PAL) folder for this folder, thats where we will find the
# traits for this platform. Traits for a platform are defines for things like whether or not something in this project
# is supported by this platform.
include(${pal_dir}/PAL_${PAL_PLATFORM_NAME_LOWERCASE}.cmake)

# Now that we have loaded our project traits for this platform, see if this project is even supported on this platform.
# If its not supported we just return after including the unsupported.
if(NOT PAL_TRAIT_${gem_name_uppercase}_SUPPORTED)
    return()
endif()

# We are on a supported platform, so add the ${gem_name} target

# Define common data used by all unified, server, and client versions of our ".API" target.

set(${gem_name}_COMMON_API_FILES_CMAKE
    gem_common_api_files.cmake
    ${pal_dir}/gem_common_api_files.cmake
)

ly_add_target(
    NAME ${gem_name}.Common.API INTERFACE
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_API_FILES_CMAKE}
    TARGET_PROPERTIES
        O3DE_PRIVATE_TARGET TRUE
    INCLUDE_DIRECTORIES
        INTERFACE
            Include
    BUILD_DEPENDENCIES
        INTERFACE
            CppUtils::Core::Include
            CppUtils::Misc::Include
            CppUtils::StdReimpl::Include
            AZ::AzFramework
            AZ::AzNetworking
            Gem::GameState
)

# Add our actual ".API" targets.

ly_add_target(
    NAME ${gem_name}.Unified.API INTERFACE
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_API_FILES_CMAKE}
        gem_client_api_files.cmake
    BUILD_DEPENDENCIES
        INTERFACE
            Gem::${gem_name}.Common.API
            Gem::O3deUtils_Core.Unified.API
            Gem::O3deUtils_Misc.Unified.API
            Gem::Multiplayer.Unified
            Gem::StartingPointInput.Unified
            Gem::LyShine.Unified.API
)

ly_add_target(
    NAME ${gem_name}.Servers.API INTERFACE
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_API_FILES_CMAKE}
    BUILD_DEPENDENCIES
        INTERFACE
            Gem::${gem_name}.Common.API
            Gem::O3deUtils_Core.Servers.API
            Gem::O3deUtils_Misc.Servers.API
            Gem::Multiplayer.Servers
)

ly_add_target(
    NAME ${gem_name}.Clients.API INTERFACE
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_API_FILES_CMAKE}
        gem_client_api_files.cmake
    BUILD_DEPENDENCIES
        INTERFACE
            Gem::${gem_name}.Common.API
            Gem::O3deUtils_Core.Clients.API
            Gem::O3deUtils_Misc.Clients.API
            Gem::Multiplayer.Clients
            Gem::StartingPointInput.Clients
            Gem::LyShine.Clients.API
)

# Define common data used by all unified, server, and client versions of our ".Private.Object" target.

set(${gem_name}_COMMON_PRIVATE_OBJECT_FILES_CMAKE
    gem_common_private_files.cmake
    ${pal_dir}/gem_common_private_files.cmake
)

set(${gem_name}_COMMON_PRIVATE_OBJECT_TARGET_PROPERTIES
    O3DE_PRIVATE_TARGET TRUE
)

ly_add_target(
    NAME ${gem_name}.Common.Private.Object INTERFACE
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_PRIVATE_OBJECT_FILES_CMAKE}
    COMPILE_DEFINITIONS
        INTERFACE
            ${gem_name_uppercase}_EXPORTS
    TARGET_PROPERTIES
        O3DE_PRIVATE_TARGET TRUE
        ${${gem_name}_COMMON_PRIVATE_OBJECT_TARGET_PROPERTIES}
    INCLUDE_DIRECTORIES
        INTERFACE
            .
    BUILD_DEPENDENCIES
        INTERFACE
            CppUtils::Core::Static
            CppUtils::Misc::Static
            CppUtils::StdReimpl::Static
            AZ::AzCore
            AZ::AzGameFramework
            Gem::Atom_AtomBridge.Static
            Legacy::CryCommon
)

# Add our ".Private.Object" targets. @Christian: TODO: [todo][techdebt][cmake][multiplayer] Support multiplayer compile definitions (`AZ_TRAIT_CLIENT` and `AZ_TRAIT_SERVER`) without needing to depend on the multiplayer gem?

ly_add_target(
    NAME ${gem_name}.Unified.Private.Object INTERFACE
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_PRIVATE_OBJECT_FILES_CMAKE}
        gem_client_private_files.cmake
    TARGET_PROPERTIES
        ${${gem_name}_COMMON_PRIVATE_OBJECT_TARGET_PROPERTIES}
    BUILD_DEPENDENCIES
        INTERFACE
            Gem::${gem_name}.Common.Private.Object
            Gem::${gem_name}.Unified.API
            Gem::Multiplayer.Unified.Static
            Gem::O3deUtils_Core.Unified
            Gem::O3deUtils_Misc.Unified
            Gem::StartingPointInput.Unified
            Gem::LyShine.Unified
)

ly_add_target(
    NAME ${gem_name}.Servers.Private.Object INTERFACE
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_PRIVATE_OBJECT_FILES_CMAKE}
    TARGET_PROPERTIES
        ${${gem_name}_COMMON_PRIVATE_OBJECT_TARGET_PROPERTIES}
    BUILD_DEPENDENCIES
        INTERFACE
            Gem::${gem_name}.Common.Private.Object
            Gem::${gem_name}.Servers.API
            Gem::Multiplayer.Server.Static
            Gem::O3deUtils_Core.Servers
            Gem::O3deUtils_Misc.Servers
)

ly_add_target(
    NAME ${gem_name}.Clients.Private.Object INTERFACE
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_PRIVATE_OBJECT_FILES_CMAKE}
        gem_client_private_files.cmake
    TARGET_PROPERTIES
        ${${gem_name}_COMMON_PRIVATE_OBJECT_TARGET_PROPERTIES}
    BUILD_DEPENDENCIES
        INTERFACE
            Gem::${gem_name}.Common.Private.Object
            Gem::${gem_name}.Clients.API
            Gem::Multiplayer.Client.Static
            Gem::O3deUtils_Core.Clients
            Gem::O3deUtils_Misc.Clients
            Gem::StartingPointInput.Clients
            Gem::LyShine.Clients
)

# Unset these variables, as they are no longer needed.
unset(${gem_name}_COMMON_PRIVATE_OBJECT_TARGET_PROPERTIES)

# Define common data used by all unified, server, and client versions of our main gem target.

set(${gem_name}_COMMON_FILES_CMAKE
    ${${gem_name}_COMMON_API_FILES_CMAKE}
    ${${gem_name}_COMMON_PRIVATE_OBJECT_FILES_CMAKE}
    gem_common_shared_files.cmake
    ${pal_dir}/gem_common_shared_files.cmake
    gem_common_autogen_files.cmake
)

set(${gem_name}_COMMON_AUTOGEN_RULES
    *.AutoComponent.xml,AutoComponent_Header.jinja,$path/$fileprefix.AutoComponent.h
    *.AutoComponent.xml,AutoComponent_Source.jinja,$path/$fileprefix.AutoComponent.cpp
    *.AutoComponent.xml,AutoComponentTypes_Header.jinja,$path/AutoComponentTypes.h
    *.AutoComponent.xml,AutoComponentTypes_Source.jinja,$path/AutoComponentTypes.cpp
    *.GameStateLevelComponent.xml,GameStateLevelComponent_Header.jinja,$path/$fileprefix.GameStateLevelComponent.h
    *.GameStateLevelComponent.xml,GameStateLevelComponent_Source.jinja,$path/$fileprefix.GameStateLevelComponent.cpp
)

# Add our main gem targets. These depend on their corresponding ".Private.Object" and ".API" targets.

ly_add_target(
    NAME ${gem_name}.Unified ${PAL_TRAIT_MONOLITHIC_DRIVEN_MODULE_TYPE}
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_FILES_CMAKE}
        gem_client_api_files.cmake
        gem_client_private_files.cmake
    BUILD_DEPENDENCIES
        PUBLIC
            Gem::${gem_name}.Unified.API
        PRIVATE
            Gem::${gem_name}.Unified.Private.Object
            Gem::O3deUtils_Core.Unified
            Gem::O3deUtils_Misc.Unified
    AUTOGEN_RULES
        ${${gem_name}_COMMON_AUTOGEN_RULES}
)

ly_add_target(
    NAME ${gem_name}.Servers ${PAL_TRAIT_MONOLITHIC_DRIVEN_MODULE_TYPE}
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_FILES_CMAKE}
    BUILD_DEPENDENCIES
        PUBLIC
            Gem::${gem_name}.Servers.API
        PRIVATE
            Gem::${gem_name}.Servers.Private.Object
            Gem::O3deUtils_Core.Servers
            Gem::O3deUtils_Misc.Servers
    AUTOGEN_RULES
        ${${gem_name}_COMMON_AUTOGEN_RULES}
)

ly_add_target(
    NAME ${gem_name}.Clients ${PAL_TRAIT_MONOLITHIC_DRIVEN_MODULE_TYPE}
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_FILES_CMAKE}
        gem_client_api_files.cmake
        gem_client_private_files.cmake
    BUILD_DEPENDENCIES
        PUBLIC
            Gem::${gem_name}.Clients.API
        PRIVATE
            Gem::${gem_name}.Clients.Private.Object
            Gem::O3deUtils_Core.Clients
            Gem::O3deUtils_Misc.Clients
    AUTOGEN_RULES
        ${${gem_name}_COMMON_AUTOGEN_RULES}
)

# Unset these variables, as they are no longer needed.
unset(${gem_name}_COMMON_API_FILES_CMAKE)
unset(${gem_name}_COMMON_PRIVATE_OBJECT_FILES_CMAKE)

# Add in CMake dependencies for each gem dependency listed in this gem's gem.json file
# for the primary gem variants used in most o3de applications
o3de_add_variant_dependencies_for_gem_dependencies(GEM_NAME ${gem_name} VARIANTS Builders Tools Clients Servers Unified)

# Include the gem name into the Client Module source file
# for use with the AZ_DECLARE_MODULE_CLASS macro
# This is to allow renaming of the gem to also cause
# the CreateModuleClass_Gem_<gem-name> function which
# is used to bootstrap the gem in monolithic builds to link to the new gem name
ly_add_source_properties(
SOURCES
    Source/${gem_name}Module.cpp
PROPERTY COMPILE_DEFINITIONS
    VALUES
        O3DE_GEM_NAME=${gem_name}
        O3DE_GEM_VERSION=${gem_version})

if(PAL_TRAIT_BUILD_HOST_TOOLS)
    ly_add_target(
        NAME ${gem_name}.Tools ${PAL_TRAIT_MONOLITHIC_DRIVEN_MODULE_TYPE}
        NAMESPACE Gem
        FILES_CMAKE
            ${${gem_name}_COMMON_FILES_CMAKE}
            gem_client_api_files.cmake
            gem_client_private_files.cmake
        BUILD_DEPENDENCIES
            PUBLIC
                Gem::${gem_name}.Unified.API
            PRIVATE
                Gem::${gem_name}.Unified.Private.Object
                EditorCore
        AUTOGEN_RULES
            ${${gem_name}_COMMON_AUTOGEN_RULES}
    )

    ly_create_alias(NAME ${gem_name}.Builders NAMESPACE Gem TARGETS Gem::${gem_name}.Tools)
endif()

# Unset these variables, as they are no longer needed.
unset(${gem_name}_COMMON_FILES_CMAKE)
unset(${gem_name}_COMMON_AUTOGEN_RULES)

################################################################################
# Gem dependencies
################################################################################

# Query the project name from the nearest project.json file in a directory at or above
# the current one.
# This gem is the project gem and therefore should be part of the project that is using it
o3de_find_ancestor_project_root(project_path project_name "${CMAKE_CURRENT_SOURCE_DIR}")

# If the project name could not be queried from a project.json file, then fallback
# to using the name of the project provided when the project template was instantiated
if (NOT project_name)
    set(project_name ${gem_name})
endif()
