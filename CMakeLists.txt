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
set(FIXTURES_SOURCE test/fixtures.cpp)

list(FILTER POKER_ENGINE_SOURCES EXCLUDE REGEX "main\\.cpp$")

add_library(SourceLibrary ${POKER_ENGINE_SOURCES})
add_library(FixtureLibrary ${FIXTURES_SOURCE})

target_link_libraries(FixtureLibrary PRIVATE gtest::gtest)

add_executable(poker-engine ${POKER_ENGINE_SOURCES} src/main.cpp)
add_executable(unit-runner ${UNIT_TEST_SOURCES} test/fixtures.cpp)
add_executable(integration-runner ${INTEGRATION_TEST_SOURCES} test/fixtures.cpp)

target_link_libraries(unit-runner PRIVATE gtest::gtest SourceLibrary FixtureLibrary)
target_link_libraries(integration-runner PRIVATE gtest::gtest SourceLibrary FixtureLibrary)

add_test(NAME UnitTests COMMAND unit-runner)
add_test(NAME IntegrationTests COMMAND integration-runner)