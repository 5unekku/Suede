cmake_minimum_required(VERSION 3.21)
project (cb LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

# Find LLVM package installed on system
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(cb
  src/main.cpp
  src/runtime/runtime.c
)

target_include_directories(cb PRIVATE src src/runtime)
target_link_libraries(cb PRIVATE LLVM)