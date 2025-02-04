cmake_minimum_required(VERSION 3.15)
project(poker-engine)

enable_testing()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

find_package(gtest REQUIRED CONFIG)

file(GLOB_RECURSE POKER_ENGINE_SOURCES src/*.cpp)
file(GLOB_RECURSE UNIT_TEST_SOURCES test/unit/*.cpp)
file(GLOB_RECURSE INTEGRATION_TEST_SOURCES test/integration/*.cpp)

add_executable(poker-engine ${POKER_ENGINE_SOURCES})
add_executable(unit-runner ${UNIT_TEST_SOURCES})
add_executable(integration-runner ${INTEGRATION_TEST_SOURCES})

target_link_libraries(unit-runner PRIVATE gtest::gtest)
target_link_libraries(integration-runner PRIVATE gtest::gtest)

add_test(NAME UnitTests COMMAND unit-runner)
add_test(NAME IntegrationTests COMMAND integration-runner)