cmake_minimum_required(VERSION 3.16)

project(re2-runner)

set(ABSL_ENABLE_INSTALL ON)
set(ABSL_PROPAGATE_CXX_STD ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Set the build type to Debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${CMAKE_SOURCE_DIR}/abseil-cpp)
include_directories(${CMAKE_SOURCE_DIR}/re2)

# Import Abseil's CMake targets
set(SAVED_CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
add_subdirectory(abseil-cpp)
set(CMAKE_INSTALL_PREFIX ${SAVED_CMAKE_INSTALL_PREFIX})
add_subdirectory(re2)
add_library(re2-runner-lib STATIC src/re2-runner-lib.cc src/re2-runner-lib.h)
add_library(re2::re2 ALIAS re2)

add_executable(re2-runner src/re2-runner.cc)
add_executable(test_re2 tests/test_re2.cc)

target_link_libraries(re2-runner re2-runner-lib re2::re2 absl::log_initialize)
target_link_libraries(test_re2 re2-runner-lib re2::re2 gtest_main absl::log_initialize)
