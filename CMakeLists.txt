# create by lq on 2018/11/16

cmake_minimum_required(VERSION 3.4)

project(DeepSea)

set(CMAKE_INSTALL_PREFIX /c/DeepSea/build)

include_directories(BEFORE /c/DeepSea/build/include)

link_directories(/c/DeepSea/build/lib)

add_subdirectory(src)

add_executable(main main.c)

target_link_libraries(main DeepSea)

install(DIRECTORY include DESTINATION /)

install(FILES README.md DESTINATION /)

message(STATUS "source dir: " ${PROJECT_SOURCE_DIR})
message(STATUS "binary dir: " ${PROJECT_BINARY_DIR})