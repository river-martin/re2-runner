cmake_minimum_required(VERSION 3.16)

project(re2-runner)

set(CMAKE_CXX_STANDARD 17)

# Import Abseil's CMake targets
find_package(absl REQUIRED)
find_package(re2 REQUIRED)

add_executable(re2_runner src/re2_runner.cc)

target_link_libraries(re2_runner re2::re2 absl::log_initialize)
