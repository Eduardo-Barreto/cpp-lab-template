file(GLOB_RECURSE MAIN_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*/main.cpp")

foreach(MAIN_FILE ${MAIN_FILES})
    get_filename_component(EXERCISE_DIR ${MAIN_FILE} DIRECTORY)
    get_filename_component(TARGET_NAME ${EXERCISE_DIR} NAME)

    file(GLOB EXTRA_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${EXERCISE_DIR}/*.cpp")
    list(REMOVE_ITEM EXTRA_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${MAIN_FILE}")

    add_executable(${TARGET_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/${MAIN_FILE}
        ${EXTRA_SOURCES}
    )
    set_target_properties(${TARGET_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )
    target_include_directories(${TARGET_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/${EXERCISE_DIR}
    )
endforeach()
