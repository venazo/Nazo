cmake_minimum_required(VERSION 3.28.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(game)

#set executable directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../)

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

include_directories(AFTER game ../zewada/src)

add_executable(game ${SRC})

target_link_libraries(game PRIVATE zewada ${YAML_CPP_LIBRARIES} glm::glm Boost::filesystem yaml-cpp glfw glad::glad box2d::box2d)


target_precompile_headers(game PUBLIC ../zewada/src/zpch.h)