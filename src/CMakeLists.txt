# create by lq on 2018/11/16

aux_source_directory(. LIB_SRC_DIR)

add_library(${PROJECT_NAME} SHARED ${LIB_SRC_DIR})

install(TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION lib
)