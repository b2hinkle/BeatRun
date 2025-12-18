
# Setup the gem meta variables that includes the "gem_path", "gem_name" and "gem_version"
# The "pal_dir" variable is also set which refers to the Platform/<platform-name> directory
# based on the directory of this CMakeLists.txt
o3de_gem_setup("xXGameProjectNameXx")

# Now that we have the platform abstraction layer (PAL) folder for this folder, thats where we will find the
# traits for this platform. Traits for a platform are defines for things like whether or not something in this project
# is supported by this platform.
include(${pal_dir}/PAL_${PAL_PLATFORM_NAME_LOWERCASE}.cmake)

# Now that we have loaded our project traits for this platform, see if this project is even supported on this platform.
# If its not supported we just return after including the unsupported.
if(NOT PAL_TRAIT_XXGAMEPROJECTNAMEXX_SUPPORTED)
    return()
endif()

# We are on a supported platform, so add the ${gem_name} target

# These variables contain common items that are used in all unified, server, and client versions of our static target.

set(MY_COMMON_STATIC_FILES_CMAKE
    xxgameprojectnamexx_files.cmake
    ${pal_dir}/xxgameprojectnamexx_${PAL_PLATFORM_NAME_LOWERCASE}_files.cmake
    xxgameprojectnamexx_autogen_files.cmake
)

set(MY_COMMON_STATIC_INCLUDE_DIRECTORIES
    PUBLIC
        Include
    PRIVATE
        .
)

# @Christian: TODO: [todo][techdebt][cmake][multiplayer]: I think we should take the multiplayer dependencies out of and and only directly use the "unified" "server" or "client" versions for each case.
set(MY_COMMON_STATIC_BUILD_DEPENDENCIES
    PUBLIC
        AZ::AzFramework
        AZ::AzNetworking
        Gem::Multiplayer
        Gem::GameState
        Gem::O3deUtils_Core
        Gem::O3deUtils_Misc
    PRIVATE
        AZ::AzGameFramework
        Gem::Atom_AtomBridge.Static
        Legacy::CryCommon
        CppUtils::Concepts::Include
)

set(MY_COMMON_STATIC_AUTOGEN_RULES
    *.AutoComponent.xml,AutoComponent_Header.jinja,$path/$fileprefix.AutoComponent.h
    *.AutoComponent.xml,AutoComponent_Source.jinja,$path/$fileprefix.AutoComponent.cpp
    *.AutoComponent.xml,AutoComponentTypes_Header.jinja,$path/AutoComponentTypes.h
    *.AutoComponent.xml,AutoComponentTypes_Source.jinja,$path/AutoComponentTypes.cpp
    *.GameStateLevelComponent.xml,GameStateLevelComponent_Header.jinja,$path/$fileprefix.GameStateLevelComponent.h
    *.GameStateLevelComponent.xml,GameStateLevelComponent_Source.jinja,$path/$fileprefix.GameStateLevelComponent.cpp
)

# These variables contain common items that are only used in unified versions of our static target.

set(MY_UNIFIED_STATIC_FILES_CMAKE
    xxgameprojectnamexx_client_files.cmake
)

set(MY_UNIFIED_STATIC_BUILD_DEPENDENCIES
    PUBLIC
        Gem::StartingPointInput.Unified
        Gem::LyShine.Unified
    PRIVATE
        Gem::Multiplayer.Unified.Static
        Gem::O3deUtils_Core.Unified.Static
        Gem::O3deUtils_Misc.Unified.Static
)

# Add our static targets.

ly_add_target(
    NAME ${gem_name}.Unified.Static STATIC
    NAMESPACE Gem
    FILES_CMAKE
        ${MY_COMMON_STATIC_FILES_CMAKE}
        ${MY_UNIFIED_STATIC_FILES_CMAKE}
    INCLUDE_DIRECTORIES
        ${MY_COMMON_STATIC_INCLUDE_DIRECTORIES}
    BUILD_DEPENDENCIES
        ${MY_COMMON_STATIC_BUILD_DEPENDENCIES}
        ${MY_UNIFIED_STATIC_BUILD_DEPENDENCIES}
    AUTOGEN_RULES
        ${MY_COMMON_STATIC_AUTOGEN_RULES}
)

ly_add_target(
    NAME ${gem_name}.Server.Static STATIC
    NAMESPACE Gem
    FILES_CMAKE
        ${MY_COMMON_STATIC_FILES_CMAKE}
    INCLUDE_DIRECTORIES
        ${MY_COMMON_STATIC_INCLUDE_DIRECTORIES}
    BUILD_DEPENDENCIES
        ${MY_COMMON_STATIC_BUILD_DEPENDENCIES}
        PRIVATE
            Gem::Multiplayer.Server.Static
            Gem::O3deUtils_Core.Server.Static
            Gem::O3deUtils_Misc.Server.Static
    AUTOGEN_RULES
        ${MY_COMMON_STATIC_AUTOGEN_RULES}
)

ly_add_target(
    NAME ${gem_name}.Client.Static STATIC
    NAMESPACE Gem
    FILES_CMAKE
        ${MY_COMMON_STATIC_FILES_CMAKE}
        xxgameprojectnamexx_client_files.cmake
    INCLUDE_DIRECTORIES
        ${MY_COMMON_STATIC_INCLUDE_DIRECTORIES}
    BUILD_DEPENDENCIES
        ${MY_COMMON_STATIC_BUILD_DEPENDENCIES}
        PUBLIC
            Gem::StartingPointInput.Clients
            Gem::LyShine.Clients
        PRIVATE
            Gem::Multiplayer.Client.Static
            Gem::O3deUtils_Core.Client.Static
            Gem::O3deUtils_Misc.Client.Static
    AUTOGEN_RULES
        ${MY_COMMON_STATIC_AUTOGEN_RULES}
)

if(PAL_TRAIT_BUILD_HOST_TOOLS)
    ly_add_target(
        NAME ${gem_name}.Editor.Static STATIC
        NAMESPACE Gem
        FILES_CMAKE
            ${MY_COMMON_STATIC_FILES_CMAKE}
            ${MY_UNIFIED_STATIC_FILES_CMAKE}
        INCLUDE_DIRECTORIES
            ${MY_COMMON_STATIC_INCLUDE_DIRECTORIES}
        BUILD_DEPENDENCIES
            ${MY_COMMON_STATIC_BUILD_DEPENDENCIES}
            ${MY_UNIFIED_STATIC_BUILD_DEPENDENCIES}
            PRIVATE
                EditorCore
        AUTOGEN_RULES
            ${MY_COMMON_STATIC_AUTOGEN_RULES}
    )
endif()

# Unset these variables, as they are no longer needed.
unset(MY_COMMON_STATIC_FILES_CMAKE)
unset(MY_COMMON_STATIC_INCLUDE_DIRECTORIES)
unset(MY_COMMON_STATIC_BUILD_DEPENDENCIES)
unset(MY_COMMON_STATIC_AUTOGEN_RULES)
unset(MY_UNIFIED_STATIC_FILES_CMAKE)
unset(MY_UNIFIED_STATIC_BUILD_DEPENDENCIES)

# These variables contain common items that are used in all unified, server, and client versions of our module target.

set(MY_COMMON_MODULE_FILES_CMAKE
    xxgameprojectnamexx_shared_files.cmake
    ${pal_dir}/xxgameprojectnamexx_shared_${PAL_PLATFORM_NAME_LOWERCASE}_files.cmake
)

set(MY_COMMON_MODULE_INCLUDE_DIRECTORIES
    PUBLIC
        Include
    PRIVATE
        .
)

set(MY_COMMON_MODULE_BUILD_DEPENDENCIES
    PRIVATE
        AZ::AzCore
        Legacy::CryCommon
)

# These variables contain common items that are only used in unified versions of our module target.

set(MY_UNIFIED_MODULE_BUILD_DEPENDENCIES
    PRIVATE
        Gem::Multiplayer.Unified.Static
)

# Add our module targets.

ly_add_target(
    NAME ${gem_name} ${PAL_TRAIT_MONOLITHIC_DRIVEN_MODULE_TYPE}
    NAMESPACE Gem
    FILES_CMAKE
        ${MY_COMMON_MODULE_FILES_CMAKE}
    INCLUDE_DIRECTORIES
        ${MY_COMMON_MODULE_INCLUDE_DIRECTORIES}
    BUILD_DEPENDENCIES
        ${MY_COMMON_MODULE_BUILD_DEPENDENCIES}
        ${MY_UNIFIED_MODULE_BUILD_DEPENDENCIES}
        PRIVATE
            Gem::${gem_name}.Unified.Static
)

ly_add_target(
    NAME ${gem_name}.Server ${PAL_TRAIT_MONOLITHIC_DRIVEN_MODULE_TYPE}
    NAMESPACE Gem
    FILES_CMAKE
        ${MY_COMMON_MODULE_FILES_CMAKE}
    INCLUDE_DIRECTORIES
        ${MY_COMMON_MODULE_INCLUDE_DIRECTORIES}
    BUILD_DEPENDENCIES
        ${MY_COMMON_MODULE_BUILD_DEPENDENCIES}
        PRIVATE
            Gem::${gem_name}.Server.Static
            Gem::Multiplayer.Server.Static
)

ly_add_target(
    NAME ${gem_name}.Client ${PAL_TRAIT_MONOLITHIC_DRIVEN_MODULE_TYPE}
    NAMESPACE Gem
    FILES_CMAKE
        ${MY_COMMON_MODULE_FILES_CMAKE}
    INCLUDE_DIRECTORIES
        ${MY_COMMON_MODULE_INCLUDE_DIRECTORIES}
    BUILD_DEPENDENCIES
        ${MY_COMMON_MODULE_BUILD_DEPENDENCIES}
        PRIVATE
            Gem::${gem_name}.Client.Static
            Gem::Multiplayer.Client.Static
)

if(PAL_TRAIT_BUILD_HOST_TOOLS)
    ly_add_target(
        NAME ${gem_name}.Editor ${PAL_TRAIT_MONOLITHIC_DRIVEN_MODULE_TYPE}
        NAMESPACE Gem
        FILES_CMAKE
            ${MY_COMMON_MODULE_FILES_CMAKE}
        INCLUDE_DIRECTORIES
            ${MY_COMMON_MODULE_INCLUDE_DIRECTORIES}
        BUILD_DEPENDENCIES
            ${MY_COMMON_MODULE_BUILD_DEPENDENCIES}
            ${MY_UNIFIED_MODULE_BUILD_DEPENDENCIES}
            PRIVATE
                Gem::${gem_name}.Editor.Static
    )

    ly_create_alias(NAME ${gem_name}.Tools NAMESPACE Gem TARGETS Gem::${gem_name}.Editor)
    ly_create_alias(NAME ${gem_name}.Builders NAMESPACE Gem TARGETS Gem::${gem_name}.Editor)
endif()

# Unset these variables, as they are no longer needed.
unset(MY_COMMON_MODULE_FILES_CMAKE)
unset(MY_COMMON_MODULE_INCLUDE_DIRECTORIES)
unset(MY_COMMON_MODULE_BUILD_DEPENDENCIES)
unset(MY_UNIFIED_MODULE_BUILD_DEPENDENCIES)

# Define all the kinds of applications ${gem_name} needs to be used by.
ly_create_alias(NAME ${gem_name}.Unified NAMESPACE Gem TARGETS Gem::${gem_name})
ly_create_alias(NAME ${gem_name}.Servers NAMESPACE Gem TARGETS Gem::${gem_name}.Server)
ly_create_alias(NAME ${gem_name}.Clients NAMESPACE Gem TARGETS Gem::${gem_name}.Client)

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
    Source/xXGameProjectNameXxModule.cpp
PROPERTY COMPILE_DEFINITIONS
    VALUES
        O3DE_GEM_NAME=${gem_name}
        O3DE_GEM_VERSION=${gem_version})

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
    set(project_name xXGameProjectNameXx)
endif()
