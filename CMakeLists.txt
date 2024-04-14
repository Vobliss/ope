# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(ope)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source files to the 'ope' executable
add_executable(ope src/main.cpp src/norm.cpp src/dist.cpp)

# Specify the directories that the compiler should look in for include files
target_include_directories(ope PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/include"
)

# Find the Boost package
find_package(Boost REQUIRED)

# Link the Boost libraries to the 'ope' target
target_link_libraries(ope PUBLIC ${Boost_LIBRARIES})

# Enable testing
enable_testing()

# Add the source files to the 'tests' executable
add_executable(tests test/test_norm.cpp src/norm.cpp src/dist.cpp)

# Specify the directories that the compiler should look in for include files for the 'tests' target
target_include_directories(tests PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/include"
)

# Link the Google Test libraries to the 'tests' target
target_link_libraries(tests gtest gtest_main)

# Add a test named 'tests' that runs the 'tests' executable
add_test(NAME tests COMMAND tests)

# Add a custom target named 'check' that runs the 'tests' target with verbose output
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)
add_dependencies(check tests)

# Set compiler and linker flags for code coverage
if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

find_package(benchmark REQUIRED)
add_executable(benchmarks benchmarks/benchmark_norm.cpp src/norm.cpp src/dist.cpp)
target_include_directories(benchmarks PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/include"
)
target_link_libraries(benchmarks benchmark::benchmark)
# Set compiler flags for benchmark optimization
set_target_properties(benchmarks PROPERTIES COMPILE_FLAGS "-O3")
