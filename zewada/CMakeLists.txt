cmake_minimum_required(VERSION 3.28.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(zewada)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../)

#add packages from vcpkg
#vcpkg install should run automatically before the cmake compilation
find_package(Boost 1.82.0 REQUIRED COMPONENTS filesystem)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(OpenAL CONFIG REQUIRED) 
find_package(Freetype REQUIRED)
add_definitions(-D_WIN)

file(GLOB_RECURSE SRC
 "src/*.h"
 "src/*.cpp"
)

include_directories(AFTER src)
 
add_library(zewada STATIC ${SRC})

target_include_directories(zewada PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(zewada PRIVATE ${YAML_CPP_LIBRARIES} Boost::boost Boost::filesystem glm::glm yaml-cpp glfw glad::glad box2d::box2d OpenAL::OpenAL Freetype::Freetype)

target_precompile_headers(zewada PUBLIC src/zpch.h)

