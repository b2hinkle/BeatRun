
# It's our job to define this cmake variable which the `ly_include_cmake_file_list` function looks at after this file is done being processed.
set(FILES)

list(APPEND FILES
    Include/xXGameProjectNameXx/xXGameProjectNameXxConfiguration.h
    Include/xXGameProjectNameXx/xXGameProjectNameXxBus.h
    Include/xXGameProjectNameXx/xXGameProjectNameXxTypeIds.h
    Include/xXGameProjectNameXx/MyExperimentInterface.h
    Include/xXGameProjectNameXx/MoverInterface.h
    Include/xXGameProjectNameXx/MoverNetworkInputInterface.h
    Include/xXGameProjectNameXx/SettingsRegistryAccessors.h
    Include/xXGameProjectNameXx/LevelNames.h
    Include/xXGameProjectNameXx/PlayerEntityManagerInterface.h
    Include/xXGameProjectNameXx/PlayerBus.h
)
