# create by lq on 2018/11/16

set(CMAKE_LEGACY_CYGWIN_WIN32 0)

cmake_minimum_required(VERSION 3.9.2)

project(DeepSea C)

set(CMAKE_C_STANDARD 99)
set(PROJECT_VERSION 0.0.1)
set(DS_VERSION_SO 1)
set(DS_LIB deepSea)

aux_source_directory(src SOURCE_DIR)
aux_source_directory(tests/Unity/src UNITY_SOURCE_DIR)

option(BUILD_SHARED_LIBS "Build shared libraries" on)
option(BUILD_STATIC_LIBS "Build static libraries" off)
option(BUILD_SHARED_AND_STATIC_LIBS "Build both shared and static libraries" on)
option(ENABLE_DS_TEST "Enable building deepSea test" on)
option(CMAKE_INSTALL_INCLUDEDIR "/")
option(CMAKE_INSTALL_LIBDIR "/")

if((BUILD_SHARED_LIBS AND (NOT BUILD_STATIC_LIBS)))
    set(DS_LIBRARY_TYPE SHARED)
else()
    set(DS_LIBRARY_TYPE STATIC)
endif()

if(NOT BUILD_SHARED_AND_STATIC_LIBS)
    add_library(${DS_LIB} ${DS_LIBRARY_TYPE} ${SOURCE_DIR})
else()
    add_library(${DS_LIB} SHARED ${SOURCE_DIR})
    add_library(${DS_LIB}-static STATIC ${SOURCE_DIR})
    set_target_properties(${DS_LIB}-static PROPERTIES OUTPUT_NAME ${DS_LIB})
    set_target_properties(${DS_LIB}-static PROPERTIES PREFIX lib)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/library_config/libdeepSea.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/libdeepSea.pc @ONLY)

install(DIRECTORY include
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libdeepSea.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/README.md
    DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS ${DS_LIB}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/lib EXPORT ${DS_LIB})

if(BUILD_SHARED_AND_STATIC_LIBS)
    install(TARGETS ${DS_LIB}-static DESTINATION ${CMAKE_INSTALL_LIBDIR}/lib)
endif()

set_target_properties(${DS_LIB} PROPERTIES
    SOVERSION ${DS_VERSION_SO}
    VERSION ${PROJECT_VERSION})

# test
if(ENABLE_DS_TEST)

    enable_testing()

    add_library(unity STATIC ${UNITY_SOURCE_DIR})

    set(dsTests
        test_ds_stack
    )

    foreach(dsTest ${dsTests})
        add_executable(${dsTest} ${CMAKE_CURRENT_SOURCE_DIR}/tests/${dsTest}.c)
        target_link_libraries(${dsTest} ${DS_LIB} unity)
        add_test(${dsTest} ${dsTest})
    endforeach()

endif()
