cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)

# 여기에는 라이브러리를 만드는 코드만 생성할 것임.
project(MyLib VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE) # project() 명령은 이 변수를 항상 FALSE로 초기화하기에...

set(
  LIB_SOURCES
  sample_lib1.cpp
  sample_lib2.cpp
)

# 라이브러리 만들기 https://matgomes.com/add-library-cmake-create-libraries/
add_library(${PROJECT_NAME} SHARED ${LIB_SOURCES})