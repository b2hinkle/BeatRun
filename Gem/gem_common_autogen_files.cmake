
# It's our job to define this cmake variable which the `ly_include_cmake_file_list` function looks at after this file is done being processed.
set(FILES)

# Append required multiplayer gem files.
block(SCOPE_FOR VARIABLES PROPAGATE FILES)
    get_property(multiplayer_gem_root GLOBAL PROPERTY "@GEMROOT:Multiplayer@")

    list(APPEND FILES
        ${multiplayer_gem_root}/Code/Include/Multiplayer/AutoGen/AutoComponent_Common.jinja
        ${multiplayer_gem_root}/Code/Include/Multiplayer/AutoGen/AutoComponent_Header.jinja
        ${multiplayer_gem_root}/Code/Include/Multiplayer/AutoGen/AutoComponent_Source.jinja
        ${multiplayer_gem_root}/Code/Include/Multiplayer/AutoGen/AutoComponentTypes_Header.jinja
        ${multiplayer_gem_root}/Code/Include/Multiplayer/AutoGen/AutoComponentTypes_Source.jinja
    )
endblock()

# Append our custom AutoGen jinja files.
list(APPEND FILES
    Include/xXGameProjectNameXx/AutoGen/GameStateLevelComponent_Header.jinja
    Include/xXGameProjectNameXx/AutoGen/GameStateLevelComponent_Source.jinja
)

# Append our AutoGen xml files.
list(APPEND FILES
    Source/AutoGen/MoverNetworkInputComponent.AutoComponent.xml
    Source/AutoGen/MoverClientInputInjectorComponent.AutoComponent.xml
    Source/AutoGen/PlayerEntityManagerComponent.AutoComponent.xml
    Source/AutoGen/StageSelectGameStateLevelComponent.GameStateLevelComponent.xml
)
