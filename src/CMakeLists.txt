aux_source_directory(. LIB_DIR_SRC)

add_library(deepSea SHARED ${LIB_DIR_SRC})

add_library(static_deepSea STATIC ${LIB_DIR_SRC})

set_target_properties(deepSea PROPERTIES 
    VERSION 0.0.1 
    SOVERSION 0.0.1
)

set_target_properties(static_deepSea PROPERTIES 
    OUTPUT_NAME deepSea
)

set_target_properties(deepSea PROPERTIES 
    CLEAN_DIRECT_OUTPUT 1
)

set_target_properties(static_deepSea PROPERTIES 
    CLEAN_DIRECT_OUTPUT 1
)

install(TARGETS deepSea static_deepSea
    LIBRARY DESTINATION lib/deepSea
    ARCHIVE DESTINATION lib/deepSea
)