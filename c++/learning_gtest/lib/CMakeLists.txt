cmake_minimum_required(VERSION 3.16)

# 여기에는 라이브러리를 만드는 코드만 생성할 것임.
set(
  LIB_SOURCES
  lib_arithmetic.cpp
)

# 라이브러리 만들기 https://matgomes.com/add-library-cmake-create-libraries/
add_library(${MY_LIB_TARGET} SHARED ${LIB_SOURCES})