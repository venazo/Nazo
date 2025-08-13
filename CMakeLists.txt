cmake_minimum_required(VERSION 3.28.0)

project(nazo VERSION 1.0.0 LANGUAGES C CXX) 

#set cpp version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#enable intellisense in vs code
set(EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(zewada)
add_subdirectory(scripts)
add_subdirectory(nazo)
add_subdirectory(game)