cmake_minimum_required(VERSION 3.16)
project(programmers VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_EXECUTABLE_SUFFIX .out)

set(TEST_TARGET
  ${CMAKE_PROJECT_NAME})

add_compile_options(-Wall)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${TEST_TARGET}
  최소직사각형.cpp
  "같은 숫자는 싫어.cpp"
)

target_link_libraries(${TEST_TARGET}
  PUBLIC GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(${TEST_TARGET})
