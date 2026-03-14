cmake_minimum_required(VERSION 3.15)
project(poker-engine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---------------------------------------------------------------------------
# WebAssembly build (invoked via `emcmake cmake`)
# ---------------------------------------------------------------------------
if(EMSCRIPTEN)
    file(GLOB_RECURSE WASM_SOURCES src/core/*.cpp src/bots/*.cpp)
    add_executable(poker-engine-wasm ${WASM_SOURCES} src/wasm/bindings.cpp)
    set_target_properties(poker-engine-wasm PROPERTIES
        OUTPUT_NAME "poker_engine"
        SUFFIX ".js"
    )
    target_link_options(poker-engine-wasm PRIVATE
        "--bind"
        "-sALLOW_MEMORY_GROWTH=1"
        "-sMODULARIZE=1"
        "-sEXPORT_NAME=PokerEngineModule"
        "-sENVIRONMENT=web"
    )
    return()
endif()

# ---------------------------------------------------------------------------
# Native build
# ---------------------------------------------------------------------------
enable_testing()

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

find_package(gtest REQUIRED CONFIG)
find_package(ftxui REQUIRED)

file(GLOB_RECURSE POKER_ENGINE_SOURCES src/*.cpp)
file(GLOB_RECURSE UNIT_TEST_SOURCES test/unit/*.cpp)
file(GLOB_RECURSE INTEGRATION_TEST_SOURCES test/integration/*.cpp)
set(FIXTURES_SOURCE test/fixtures.cpp)

list(FILTER POKER_ENGINE_SOURCES EXCLUDE REGEX "main\\.cpp$")

add_library(SourceLibrary ${POKER_ENGINE_SOURCES})
add_library(FixtureLibrary ${FIXTURES_SOURCE})

target_link_libraries(SourceLibrary PUBLIC ftxui::ftxui)
target_link_libraries(FixtureLibrary PRIVATE gtest::gtest)

add_executable(poker-engine ${POKER_ENGINE_SOURCES} src/main.cpp)
add_executable(unit-runner ${UNIT_TEST_SOURCES} test/fixtures.cpp)
add_executable(integration-runner ${INTEGRATION_TEST_SOURCES} test/fixtures.cpp)

target_link_libraries(poker-engine PRIVATE ftxui::ftxui)
target_link_libraries(unit-runner PRIVATE gtest::gtest SourceLibrary FixtureLibrary)
target_link_libraries(integration-runner PRIVATE gtest::gtest SourceLibrary FixtureLibrary)

add_test(NAME UnitTests COMMAND unit-runner)
add_test(NAME IntegrationTests COMMAND integration-runner)
