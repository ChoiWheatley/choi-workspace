# Messing around with real cpp files
# https://github.com/methylDragon/coding-notes/blob/master/CMake/01%20CMake%20-%20Basics%20and%20Scripting.md#2.2
# https://www.tuwlab.com/ece/27270
# https://cgold.readthedocs.io/en/latest/tutorials.html
cmake_minimum_required(VERSION 3.16) # 요구 CMake 최소 버전
project(LEARN_GTEST VERSION 1.0.1) # 프로젝트 이름 및 버전

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG) # 빌드 config 및 기타등등 옵션
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_EXECUTABLE_SUFFIX .out)

# 타겟 이름은 내가 정의한다. 밖에서 온 타겟을 빼곤.
set(SRC_TARGET
  ${CMAKE_PROJECT_NAME}.${CMAKE_PROJECT_VERSION}
)
set(MY_LIB_TARGET
  MY_LIB
)
set(MY_TEST_TARGET
  MY_TEST
)

# 공통 컴파일 옵션, 링크 옵션
add_compile_options(-Wall)

# current directory 변경하기 전에 공통적으로 include할 디렉토리를 지정할 수 있다.
# target_include_directories는 항상 루트 디렉토리 기준으로 검색한다는 점과는 다르다.
include_directories(/usr/include include)

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

# 재귀적으로 하위 단위를 빌드
add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(test)

# 원하는 타겟의 최종 위치를 정할 수도 있다.
set_target_properties(${SRC_TARGET}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
set_target_properties(${MY_LIB_TARGET}
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
set_target_properties(${MY_TEST_TARGET}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# 타겟이 필요한 라이브러리를 정의.
target_link_libraries(${SRC_TARGET} # ./src/CMakeLists.txt::project name
  PUBLIC ${MY_LIB_TARGET} # ./lib/CMakeLists.txt::project name
)
target_link_libraries(${MY_TEST_TARGET}
  PUBLIC ${MY_LIB_TARGET}
)