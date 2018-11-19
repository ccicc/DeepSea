# create by lq on 2018/11/18

if(ENABLE_DS_TEST)
    enable_testing()

    aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Unity/src UNITY_SOURCE_DIR)

    add_library(unity STATIC ${UNITY_SOURCE_DIR})

    target_compile_options(unity PRIVATE "-Wno-error")
    target_compile_options(unity PRIVATE "-fvisibility=default")
    target_compile_options(unity PRIVATE "-fno-sanitize=float-divide-by-zero")
    target_compile_options(unity PRIVATE "-Wno-switch-enum")

    set_target_properties(unity PROPERTIES PUBLIC_HEADER "Unity/src/unity_internals.h;Unity/src/unity.h")

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Unity/src)

    set(UNITY_TESTS test_ds_stack)

    message("-- be ready to run test case. Usage: make && make test")

    foreach(UNITY_TEST ${UNITY_TESTS})
        add_executable(${UNITY_TEST} ${UNITY_TEST}.c)
        target_link_libraries(${UNITY_TEST} ${unity} ${DS_LIB})
        add_test(NAME ${UNITY_TEST} COMMAND ./${UNITY_TEST})
    endforeach()
endif()
