# CMakeList.txt: проект CMake для 22_PC_GDPS_MAIN; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /MANIFEST:NO")
set(LIBRARY_OUTPUT_PATH "D:/Games/user666/2.2 PC GDPS v1.13-beta.1/mods")
cmake_policy(SET CMP0057 NEW)

project ("22_PC_GDPS_MAIN")

#curly-eureka
include($ENV{CE_INCL})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE ALLOCCONSOLEA src/ALLOCCONSOLEA/*.cpp)
add_library(ALLOCCONSOLEA SHARED ${ALLOCCONSOLEA} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE FUSES src/FUSES/*.cpp)
add_library(FUSES SHARED ${FUSES} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE SAI_STUFF_CONTROLLER src/SAI_STUFF_CONTROLLER/*.cpp)
add_library(SAI_STUFF_CONTROLLER SHARED ${SAI_STUFF_CONTROLLER} "src/customLayerxd.cpp" "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE SUPPORT_LAYER_EXT src/_UI/SUPPORT_LAYER_EXT/*.cpp)
add_library(SUPPORT_LAYER_EXT SHARED ${SUPPORT_LAYER_EXT} "src/customLayerxd.cpp" "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE GAREGE_LAYER_EXT src/_UI/GAREGE_LAYER_EXT/*.cpp)
add_library(GAREGE_LAYER_EXT SHARED ${GAREGE_LAYER_EXT} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE KEYS_LAYER_EXT src/_UI/KEYS_LAYER_EXT/*.cpp)
add_library(KEYS_LAYER_EXT SHARED ${KEYS_LAYER_EXT} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE SOCIALBTNS src/_UI/SOCIALBTNS/*.cpp)
add_library(SOCIALBTNS SHARED ${SOCIALBTNS} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE THE_SAFE_BTN src/_UI/THE_SAFE_BTN/*.cpp)
add_library(THE_SAFE_BTN SHARED ${THE_SAFE_BTN} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE VERSION_CHECKER src/_UI/VERSION_CHECKER/*.cpp)
add_library(VERSION_CHECKER SHARED ${VERSION_CHECKER} "src/customLayerxd.cpp" "verInf.rc" ${CURLY_EUREKA_SRC})
include_directories(src)

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE TRIGGERS src/_OBJECTS/TRIGGERS/*.cpp)
add_library(TRIGGERS SHARED ${TRIGGERS} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE SPIDER_ORB_N_PAD src/_OBJECTS/SPIDER_ORB_N_PAD/*.cpp)
add_library(SPIDER_ORB_N_PAD SHARED ${SPIDER_ORB_N_PAD} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE GREEN_PORTALE src/_OBJECTS/GREEN_PORTALE/*.cpp)
add_library(GREEN_PORTALE SHARED ${GREEN_PORTALE} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE DECOBLOCKY src/_OBJECTS/DECOBLOCKY/*.cpp)
add_library(DECOBLOCKY SHARED ${DECOBLOCKY} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE FREE_FLY_MODE src/FREE_FLY_MODE/*.cpp)
add_library(FREE_FLY_MODE SHARED ${FREE_FLY_MODE} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE LOAD_RESOURCES src/LOAD_RESOURCES/*.cpp)
add_library(LOAD_RESOURCES SHARED ${LOAD_RESOURCES} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE HACKS src/HACKS/*.cpp)
add_library(HACKS SHARED ${HACKS} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE PLAT src/PLAT/*.cpp)
add_library(PLAT SHARED ${PLAT} "verInf.rc" ${CURLY_EUREKA_SRC})