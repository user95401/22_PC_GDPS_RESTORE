# CMakeList.txt: проект CMake для 22_PC_GDPS_MAIN; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /MANIFEST:NO")
set(LIBRARY_OUTPUT_PATH "D:/Games/user666/2.2 PC GDPS v1.13/mods")
cmake_policy(SET CMP0057 NEW)

project ("22_PC_GDPS_MAIN")

#curly-eureka
include($ENV{CE_INCL})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE ALLOCCONSOLEA src/ALLOCCONSOLEA/*)
add_library(ALLOCCONSOLEA SHARED ${ALLOCCONSOLEA} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE FUSES src/FUSES/*)
add_library(FUSES SHARED ${FUSES} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE SAI_STUFF_CONTROLLER src/SAI_STUFF_CONTROLLER/*)
add_library(SAI_STUFF_CONTROLLER SHARED ${SAI_STUFF_CONTROLLER} "src/customLayerxd.cpp" "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE SUPPORT_LAYER_EXT src/SUPPORT_LAYER_EXT/*)
add_library(SUPPORT_LAYER_EXT SHARED ${SUPPORT_LAYER_EXT} "src/customLayerxd.cpp" "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE GAREGE_LAYER_EXT src/GAREGE_LAYER_EXT/*)
add_library(GAREGE_LAYER_EXT SHARED ${GAREGE_LAYER_EXT} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE KEYS_LAYER_EXT src/KEYS_LAYER_EXT/*)
add_library(KEYS_LAYER_EXT SHARED ${KEYS_LAYER_EXT} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE SOCIALBTNS src/SOCIALBTNS/*)
add_library(SOCIALBTNS SHARED ${SOCIALBTNS} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE THE_SAFE_BTN src/THE_SAFE_BTN/*)
add_library(THE_SAFE_BTN SHARED ${THE_SAFE_BTN} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE VERSION_CHECKER src/VERSION_CHECKER/*)
add_library(VERSION_CHECKER SHARED ${VERSION_CHECKER} "src/customLayerxd.cpp" "verInf.rc" ${CURLY_EUREKA_SRC})
include_directories(src)

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE TRIGGERS src/TRIGGERS/*)
add_library(TRIGGERS SHARED ${TRIGGERS} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE LOAD_RESOURCES src/LOAD_RESOURCES/*)
add_library(LOAD_RESOURCES SHARED ${LOAD_RESOURCES} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE HACKS src/HACKS/*)
add_library(HACKS SHARED ${HACKS} "verInf.rc" ${CURLY_EUREKA_SRC})

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE PLAT src/PLAT/*)
add_library(PLAT SHARED ${PLAT} "verInf.rc" ${CURLY_EUREKA_SRC})