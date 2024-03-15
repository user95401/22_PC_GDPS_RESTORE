cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /MANIFEST:NO")
cmake_policy(SET CMP0057 NEW)

project ("gdPlatformerMode")

#curly-eureka
include($ENV{CE_INCL})

#mod
add_library(${PROJECT_NAME} SHARED "main_NEW.cpp" "verInf.rc" ${CURLY_EUREKA_SRC})
set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_LIST_DIR}/../../../adaf-dll")