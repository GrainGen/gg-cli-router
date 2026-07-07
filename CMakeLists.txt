cmake_minimum_required(VERSION 3.20)

project(CLIRouterDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(clirouter INTERFACE)

target_include_directories(clirouter INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_executable(demo
    example/demo.cc
)

target_link_libraries(demo PRIVATE clirouter)

enable_testing()

add_executable(run_tests
    tests/test_main.cc
)

target_link_libraries(run_tests PRIVATE clirouter)

add_test(NAME CoreRoutingTests COMMAND run_tests)
