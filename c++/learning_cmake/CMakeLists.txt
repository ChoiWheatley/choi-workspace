# Messing around with real cpp files
# https://github.com/methylDragon/coding-notes/blob/master/CMake/01%20CMake%20-%20Basics%20and%20Scripting.md#2.2
# https://www.tuwlab.com/ece/27270
# https://cgold.readthedocs.io/en/latest/tutorials.html
cmake_minimum_required(VERSION 3.16) # 요구 CMake 최소 버전
project(MyMain VERSION 1.0.1) # 프로젝트 이름 및 버전

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG) # 빌드 config 및 기타등등 옵션
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_EXECUTABLE_SUFFIX out)

# 타겟 이름은 내가 정의한다. 밖에서 온 타겟을 빼곤.
set(SRC_TARGET
  ${CMAKE_PROJECT_NAME}.${CMAKE_PROJECT_VERSION}.
)
set(MY_LIB_TARGET
  MY_LIB
)

# 공통 컴파일 옵션, 링크 옵션
add_compile_options(-Wall)

# 재귀적으로 하위 단위를 빌드
add_subdirectory(misc)
add_subdirectory(src)
add_subdirectory(lib)

# 원하는 타겟의 최종 위치를 정할 수도 있다.
set_target_properties(${SRC_TARGET}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# 의존성 주입 및 전파는 루트에서
target_link_libraries( # 타겟이 필요한 라이브러리를 정의.
  ${SRC_TARGET} # ./src/CMakeLists.txt::project name
  PUBLIC ${MY_LIB_TARGET} # ./lib/CMakeLists.txt::project name
)
add_dependencies(${SRC_TARGET} ${MY_LIB_TARGET}) # 얘는 단순히 빌드의 의존성만을 정의함. 즉, 빌드순서를 정의함.