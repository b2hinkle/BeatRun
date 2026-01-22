
# It's our job to define this cmake variable which the `ly_include_cmake_file_list` function looks at after this file is done being processed.
set(FILES)

list(APPEND FILES
    Source/xXGameProjectNameXxSystemComponent.cpp
    Source/xXGameProjectNameXxSystemComponent.h
    Source/Components/MyExperimentComponent.h
    Source/Components/MyExperimentComponent.cpp
    Source/Components/MoverComponent.h
    Source/Components/MoverComponent.cpp
    Source/Components/MoverNetworkInputComponent.h
    Source/Components/MoverNetworkInputComponent.cpp
    Source/Components/MoverClientInputInjectorComponent.h
    Source/Components/MoverClientInputInjectorComponent.cpp
    Source/GameStates/StageSelect.h
    Source/GameStates/StageSelect.cpp
    Source/SettingsRegistryAccessors.cpp
    Source/Components/RootAutonomousEntitySpawnerComponent.h
    Source/Components/RootAutonomousEntitySpawnerComponent.cpp
    Source/Components/PlayerEntityManagerComponent.h
    Source/Components/PlayerEntityManagerComponent.cpp
    Source/PlayerSystemComponent.cpp
    Source/PlayerSystemComponent.h
)
