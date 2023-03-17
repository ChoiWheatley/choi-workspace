cmake_minimum_required(VERSION 3.25) # 요구 CMake 최소 버전
project("bak") # 프로젝트 이름 및 버전

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE DEBUG) # 빌드 config 및 기타등등 옵션
set(CMAKE_EXPORT_COMPILE_COMMANDS) # SonarLint vscode extension이 이거 써달래.

set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_EXECUTABLE_SUFFIX .out)
set(CMAKE_BINARY_DIR bin)

set(SRC_TARGET ${CMAKE_PROJECT_NAME})
set(LIB_TARGET lib${CMAKE_PROJECT_NAME})
set(MY_TEST_TARGET MY_TEST)

# 공통 컴파일 옵션
add_compile_options(-Wall -fno-builtin -fno-limit-debug-info -O0 -D_GLIBCXX_DEBUG)

include_directories(useful)

# Googlt Test
# declare a dependency on GoogleTest which is downloaded from github
# FetchContent : https://cmake.org/cmake/help/latest/module/FetchContent.html
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "main.cc")
file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS "tests.cc")

# ################################################
# compile source files
# ################################################
message("@@@@SOURCE_FILES:")
message("${SOURCE_FILES}")
message("@@@@CMAKE_BINARY_DIR : ${CMAKE_BINARY_DIR}")

foreach(SOURCE_PATH ${SOURCE_FILES})
    get_filename_component(EXEC_TARGET ${SOURCE_PATH} DIRECTORY)
    get_filename_component(EXEC_TARGET ${EXEC_TARGET} NAME)
    set(EXEC_TARGET ${EXEC_TARGET}_app)
    message("@@@@EXEC_TARGET: ${EXEC_TARGET}")

    add_executable(${EXEC_TARGET} ${SOURCE_PATH})
    set_target_properties(${EXEC_TARGET}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endforeach()

# ################################################
# compile test files
# ################################################
message("@@@@ TEST_FILES: ${TEST_FILES}")

enable_testing()

foreach(TEST_PATH ${TEST_FILES})
    get_filename_component(TEST_TARGET ${TEST_PATH} DIRECTORY)
    get_filename_component(TEST_TARGET ${TEST_TARGET} NAME)

    set(TEST_TARGET ${TEST_TARGET}_tests)
    message("@@@@ TEST_TARGET : ${TEST_TARGET}")

    add_executable(${TEST_TARGET} ${TEST_PATH})
    set_target_properties(${TEST_TARGET}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )
    target_link_libraries(${TEST_TARGET} PUBLIC GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(${TEST_TARGET})
endforeach()
