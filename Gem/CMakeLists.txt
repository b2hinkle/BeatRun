
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

# This variable contains FILES_CMAKE items that are used in all unified, server, and client versions of our static target.
set(MY_FILES_CMAKE_STATIC_COMMON
    xxgameprojectnamexx_files.cmake
    ${pal_dir}/xxgameprojectnamexx_${PAL_PLATFORM_NAME_LOWERCASE}_files.cmake
    xxgameprojectnamexx_autogen_files.cmake
)

# This variable contains FILES_CMAKE items that are only used in the unified version of our static target.
set(MY_FILES_CMAKE_STATIC_UNIFIED_ONLY
)

# This variable contains FILES_CMAKE items that are only used in the server version of our static target.
set(MY_FILES_CMAKE_STATIC_SERVER_ONLY
)

# This variable contains FILES_CMAKE items that are only used in the client version of our static target.
set(MY_FILES_CMAKE_STATIC_CLIENT_ONLY
)

# This variable contains FILES_CMAKE items that are used in all unified, server, and client versions of our module target.
set(MY_FILES_CMAKE_MODULE_COMMON
    xxgameprojectnamexx_shared_files.cmake
    ${pal_dir}/xxgameprojectnamexx_shared_${PAL_PLATFORM_NAME_LOWERCASE}_files.cmake
)

# This variable contains INCLUDE_DIRECTORIES items that are used in all unified, server, and client versions of our static target.
set(MY_INCLUDE_DIRECTORIES_STATIC_COMMON
    PUBLIC
        Include
    PRIVATE
        .
)

# This variable contains INCLUDE_DIRECTORIES items that are used in all unified, server, and client versions of our module target.
set(MY_INCLUDE_DIRECTORIES_MODULE_COMMON
    PUBLIC
        Include
    PRIVATE
        .
)

# This variable contains BUILD_DEPENDENCIES items that are used in all unified, server, and client versions of our static target.
set(MY_BUILD_DEPENDENCIES_STATIC_COMMON
    PUBLIC
        AZ::AzFramework
        AZ::AzNetworking
        Gem::Multiplayer
    PRIVATE
        AZ::AzGameFramework
        Gem::Atom_AtomBridge.Static
        Gem::StartingPointInput
)

# This variable contains BUILD_DEPENDENCIES items that are only used in the unified version of our static target.
set(MY_BUILD_DEPENDENCIES_STATIC_UNIFIED_ONLY
    PRIVATE
        Gem::Multiplayer.Unified.Static
)

# This variable contains BUILD_DEPENDENCIES items that are only used in the server version of our static target.
set(MY_BUILD_DEPENDENCIES_STATIC_SERVER_ONLY
    PRIVATE
        Gem::Multiplayer.Server.Static
)

# This variable contains BUILD_DEPENDENCIES items that are only used in the client version of our static target.
set(MY_BUILD_DEPENDENCIES_STATIC_CLIENT_ONLY
    PRIVATE
        Gem::Multiplayer.Client.Static
)

# This variable contains BUILD_DEPENDENCIES items that are used in all unified, server, and client versions of our module target.
set(MY_BUILD_DEPENDENCIES_MODULE_COMMON
    PRIVATE
        AZ::AzCore
)

# This variable contains BUILD_DEPENDENCIES items that are only used in the unified version of our module target.
set(MY_BUILD_DEPENDENCIES_MODULE_UNIFIED_ONLY
    PRIVATE
        Gem::${gem_name}.Unified.Static
        Gem::Multiplayer.Unified.Static
)

# This variable contains BUILD_DEPENDENCIES items that are only used in the server version of our module target.
set(MY_BUILD_DEPENDENCIES_MODULE_SERVER_ONLY
    PRIVATE
        Gem::${gem_name}.Server.Static
        Gem::Multiplayer.Server.Static
)

# This variable contains BUILD_DEPENDENCIES items that are only used in the client version of our module target.
set(MY_BUILD_DEPENDENCIES_MODULE_CLIENT_ONLY
    PRIVATE
        Gem::${gem_name}.Client.Static
        Gem::Multiplayer.Client.Static
)

# This variable contains AUTOGEN_RULES items that are used in all unified, server, and client versions of our static target.
set(MY_AUTOGEN_RULES_STATIC_COMMON
    *.AutoComponent.xml,AutoComponent_Header.jinja,$path/$fileprefix.AutoComponent.h
    *.AutoComponent.xml,AutoComponent_Source.jinja,$path/$fileprefix.AutoComponent.cpp
    *.AutoComponent.xml,AutoComponentTypes_Header.jinja,$path/AutoComponentTypes.h
    *.AutoComponent.xml,AutoComponentTypes_Source.jinja,$path/AutoComponentTypes.cpp
)

ly_add_target(
    NAME ${gem_name}.Unified.Static STATIC
    NAMESPACE Gem
    FILES_CMAKE
        ${MY_FILES_CMAKE_STATIC_COMMON}
        ${MY_FILES_CMAKE_STATIC_UNIFIED_ONLY}
    INCLUDE_DIRECTORIES
        ${MY_INCLUDE_DIRECTORIES_STATIC_COMMON}
    BUILD_DEPENDENCIES
        ${MY_BUILD_DEPENDENCIES_STATIC_COMMON}
        ${MY_BUILD_DEPENDENCIES_STATIC_UNIFIED_ONLY}
    AUTOGEN_RULES
        ${MY_AUTOGEN_RULES_STATIC_COMMON}
)

ly_add_target(
    NAME ${gem_name}.Server.Static STATIC
    NAMESPACE Gem
    FILES_CMAKE
        ${MY_FILES_CMAKE_STATIC_COMMON}
        ${MY_FILES_CMAKE_STATIC_SERVER_ONLY}
    INCLUDE_DIRECTORIES
        ${MY_INCLUDE_DIRECTORIES_STATIC_COMMON}
    BUILD_DEPENDENCIES
        ${MY_BUILD_DEPENDENCIES_STATIC_COMMON}
        ${MY_BUILD_DEPENDENCIES_STATIC_SERVER_ONLY}
    AUTOGEN_RULES
        ${MY_AUTOGEN_RULES_STATIC_COMMON}
)

ly_add_target(
    NAME ${gem_name}.Client.Static STATIC
    NAMESPACE Gem
    FILES_CMAKE
        ${MY_FILES_CMAKE_STATIC_COMMON}
        ${MY_FILES_CMAKE_STATIC_CLIENT_ONLY}
    INCLUDE_DIRECTORIES
        ${MY_INCLUDE_DIRECTORIES_STATIC_COMMON}
    BUILD_DEPENDENCIES
        ${MY_BUILD_DEPENDENCIES_STATIC_COMMON}
        ${MY_BUILD_DEPENDENCIES_STATIC_CLIENT_ONLY}
    AUTOGEN_RULES
        ${MY_AUTOGEN_RULES_STATIC_COMMON}
)

ly_add_target(
    NAME ${gem_name} ${PAL_TRAIT_MONOLITHIC_DRIVEN_MODULE_TYPE}
    NAMESPACE Gem
    FILES_CMAKE
        ${MY_FILES_CMAKE_MODULE_COMMON}
    INCLUDE_DIRECTORIES
        ${MY_INCLUDE_DIRECTORIES_MODULE_COMMON}
    BUILD_DEPENDENCIES
        ${MY_BUILD_DEPENDENCIES_MODULE_COMMON}
        ${MY_BUILD_DEPENDENCIES_MODULE_UNIFIED_ONLY}
)

ly_add_target(
    NAME ${gem_name}.Server ${PAL_TRAIT_MONOLITHIC_DRIVEN_MODULE_TYPE}
    NAMESPACE Gem
    FILES_CMAKE
        ${MY_FILES_CMAKE_MODULE_COMMON}
    INCLUDE_DIRECTORIES
        ${MY_INCLUDE_DIRECTORIES_MODULE_COMMON}
    BUILD_DEPENDENCIES
        ${MY_BUILD_DEPENDENCIES_MODULE_COMMON}
        ${MY_BUILD_DEPENDENCIES_MODULE_SERVER_ONLY}
)

ly_add_target(
    NAME ${gem_name}.Client ${PAL_TRAIT_MONOLITHIC_DRIVEN_MODULE_TYPE}
    NAMESPACE Gem
    FILES_CMAKE
        ${MY_FILES_CMAKE_MODULE_COMMON}
    INCLUDE_DIRECTORIES
        ${MY_INCLUDE_DIRECTORIES_MODULE_COMMON}
    BUILD_DEPENDENCIES
        ${MY_BUILD_DEPENDENCIES_MODULE_COMMON}
        ${MY_BUILD_DEPENDENCIES_MODULE_CLIENT_ONLY}
)

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

# if enabled, ${gem_name} is used by all kinds of applications
ly_create_alias(NAME ${gem_name}.Builders NAMESPACE Gem TARGETS Gem::${gem_name})
ly_create_alias(NAME ${gem_name}.Tools    NAMESPACE Gem TARGETS Gem::${gem_name})
ly_create_alias(NAME ${gem_name}.Clients  NAMESPACE Gem TARGETS Gem::${gem_name}.Client)
ly_create_alias(NAME ${gem_name}.Servers  NAMESPACE Gem TARGETS Gem::${gem_name}.Server)
ly_create_alias(NAME ${gem_name}.Unified  NAMESPACE Gem TARGETS Gem::${gem_name})

# Add in CMake dependencies for each gem dependency listed in this gem's gem.json file
# for the primary gem variants used in most o3de applications
o3de_add_variant_dependencies_for_gem_dependencies(GEM_NAME ${gem_name} VARIANTS Builders Tools Clients Servers Unified)

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
