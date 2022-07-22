cmake_minimum_required(VERSION 3.16)

# 빌드대상 바이너리 파일명 및 소스파일 목록
set(
  SOURCE_FILES
  sample_fibonacci.cpp
  sample_main.cpp
)

if(${CMAKE_BUILD_TYPE} STREQUAL DEBUG)
  # Debug 한정 컴파일 옵션, 링크 옵션
  set(CMAKE_C_FLAGS_DEBUG "-DDEBUG -DC_FLAGS")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-DDEBUG -DLINKER_FLAGS")
elseif(${CMAKE_BUILD_TYPE} STREQUAL RELEASE)
  # Release 한정 컴파일 옵션, 링크 옵션
  set(CMAKE_C_FLAGS_RELEASE "-DRELEASE -DC_FLAGS")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-DRELEASE -DLINIKER_FLAGS")
endif()

add_executable(
  ${SRC_TARGET}
  ${SOURCE_FILES}
)
