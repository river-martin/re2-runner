cmake_minimum_required(VERSION 3.16)

project(re2-runner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CDD_STANDARD_REQUIRED ON)

# Set the build type to Debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Import Abseil's CMake targets
add_subdirectory(abseil-cpp ${CMAKE_BINARY_DIR}/abseil-cpp)
add_subdirectory(re2 ${CMAKE_BINARY_DIR}/re2)

add_executable(re2-cla src/re2-cla.cc)
add_executable(test_re2 tests/test_re2.cc)

target_link_libraries(re2-cla re2::re2 absl::log_initialize)
target_link_libraries(test_re2  re2::re2 gtest_main absl::log_initialize)
