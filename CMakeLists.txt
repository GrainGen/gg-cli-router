cmake_minimum_required(VERSION 3.20)

project(CLIRouterDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(demo
    example/demo.cc
)

target_include_directories(demo PRIVATE
    include
)
