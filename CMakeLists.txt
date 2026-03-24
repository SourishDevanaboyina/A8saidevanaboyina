cmake_minimum_required(VERSION 3.16)
project(A8_Vector_Matrix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT tests)

add_library(vector INTERFACE)
target_include_directories(vector INTERFACE include)

add_executable(tests
    tests/test_vector_1.cpp
    tests/test_vector_2.cpp
    tests/test_matrix.cpp
)

target_include_directories(tests PRIVATE include tests)
target_link_libraries(tests PRIVATE vector)

enable_testing()
add_test(NAME VectorMatrixTests COMMAND tests)