cmake_minimum_required(VERSION 3.16)
project(bptree VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_EXECUTABLE_SUFFIX .out)

set(PROJECT_TARGET
  ${CMAKE_PROJECT_NAME}.${CMAKE_PROJECT_VERSION}
)
set(LIB_TARGET
  libbptree
)
set(TEST_TARGET
  test_bptree
)

add_compile_options(-Wall)

include_directories(/usr/include include)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(test)