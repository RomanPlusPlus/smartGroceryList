cmake_minimum_required(VERSION 2.8.12)

project(SmartGroceryList)

# Disable in-source builds
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("${CMAKE_CURRENT_LIST_DIR}/include")
add_subdirectory(src)
