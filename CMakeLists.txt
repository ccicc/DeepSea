cmake_minimum_required(VERSION 3.10)

project(deepSea)

aux_source_directory(. DIR_SRC)

add_subdirectory(src)

add_executable(deepSea ${DIR_SRC})

target_link_libraries(deepSea dsStack)

message(STATUS "source dir: " ${PROJECT_SOURCE_DIR})

message(STATUS "binary dir: " ${PROJECT_SOURCE_DIR})
