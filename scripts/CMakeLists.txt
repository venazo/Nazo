cmake_minimum_required(VERSION 3.28.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set executable directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../)

project(scripts)

file(GLOB_RECURSE SRC
 "src/*.h"
 "src/*.cpp"
)

find_package(Boost 1.82.0 REQUIRED COMPONENTS filesystem)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)
find_package(Stb REQUIRED)

add_definitions(-D_WIN)

add_library(scripts SHARED ${SRC})

target_include_directories(scripts PRIVATE src ../zewada/src ${Stb_INCLUDE_DIR})

target_link_libraries(scripts PRIVATE zewada ${YAML_CPP_LIBRARIES} glm::glm Boost::boost Boost::filesystem yaml-cpp glfw glad::glad box2d::box2d)

target_precompile_headers(scripts PUBLIC ../zewada/src/zpch.h)