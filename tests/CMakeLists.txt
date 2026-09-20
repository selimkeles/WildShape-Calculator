enable_testing()

# Non-main sources from src/ so test targets can call project functions
file(GLOB_RECURSE PROJECT_SRC_FILES
    "${CMAKE_SOURCE_DIR}/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)
list(REMOVE_ITEM PROJECT_SRC_FILES
    "${CMAKE_SOURCE_DIR}/src/main.c"
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
)

# Usage: add_unit_test(name src1 [src2 ...])
function(add_unit_test test_name)
    add_executable(${test_name} ${ARGN} ${PROJECT_SRC_FILES})
    target_include_directories(${test_name} PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/unity/src
    )
    target_compile_options(${test_name} PRIVATE -Wall -Wextra -pedantic)
    add_test(NAME ${test_name} COMMAND $<TARGET_FILE:${test_name}> WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    set_tests_properties(${test_name} PROPERTIES TIMEOUT 30)
endfunction()

set(UNITY_SRC ${CMAKE_CURRENT_SOURCE_DIR}/unity/src/unity.c)

add_unit_test(test_main          ${CMAKE_CURRENT_SOURCE_DIR}/test.c)
