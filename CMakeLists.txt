cmake_minimum_required(VERSION 3.10)

project(main VERSION 0.0.1 LANGUAGES C)

set(CMAKE_PROJECT_DESCRIPTION "c library")

add_subdirectory(src)

add_executable(main main.c)

target_link_libraries(main deepSea)

set(CMAKE_INSTALL_PREFIX /usr)

configure_file(deepSea.pc.in deepSea.pc @ONLY)

install(DIRECTORY include/ 
    DESTINATION include/deepSea
)

install(FILES ${CMAKE_BINARY_DIR}/deepSea.pc 
    DESTINATION lib/deepSea/pkgconfig
)

message(STATUS "source dir: " ${PROJECT_SOURCE_DIR})

message(STATUS "binary dir: " ${PROJECT_SOURCE_DIR})
