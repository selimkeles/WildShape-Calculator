cmake_minimum_required(VERSION 3.20)
project(WildShapeCalculator VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY         ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/bin/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release)

option(BUILD_TESTS "Build test programs" ON)

file(GLOB_RECURSE SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src"
"${CMAKE_CURRENT_SOURCE_DIR}/src/table"
"${CMAKE_CURRENT_SOURCE_DIR}/src/specs"
"${CMAKE_CURRENT_SOURCE_DIR}/src/calculator"
"${CMAKE_CURRENT_SOURCE_DIR}/src/creatures")
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
