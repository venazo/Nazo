cmake_minimum_required(VERSION 3.28.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(nazo)

#set executable directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../CMAKE_BUILD_TYPE)

file(GLOB_RECURSE SRC
 "src/*.h"
 "src/*.cpp"
)

find_package(Boost 1.82.0 REQUIRED COMPONENTS filesystem)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(Freetype REQUIRED)

add_definitions(-D_WIN)

add_executable(nazo ${SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_CURRENT_SOURCE_DIR}/../Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/../Release
)

target_include_directories(nazo PRIVATE src ../zewada/src ${Stb_INCLUDE_DIR})

target_link_libraries(nazo PRIVATE zewada imgui::imgui ${YAML_CPP_LIBRARIES} Boost::boost Boost::filesystem glm::glm  yaml-cpp glfw glad::glad OpenAL::OpenAL Freetype::Freetype)

target_precompile_headers(nazo PUBLIC ../zewada/src/zpch.h)