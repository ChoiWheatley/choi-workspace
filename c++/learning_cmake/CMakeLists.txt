# https://preshing.com/20170522/learn-cmakes-scripting-language-in-15-minutes/
message("Hello, world!, ${NAME}")

# variables
set(JOHN_NAME "John Smith")
set(JOHN_ADDRESS "123 Fake St")
set(PERSON "JOHN")
message("${${PERSON}_NAME} lives at ${${PERSON}_ADDRESS}.")

# math expressions
set(EXPRESSION "1 + 1")
math(EXPR MY_SUM ${EXPRESSION})
message("The sum of ${EXPRESSION} is ${MY_SUM}")
math(EXPR DOUBLE_SUM "${MY_SUM} * 2")
message("Double that is ${DOUBLE_SUM}")

# if statements
if(WIN32)
  message("You're running CMake on Windows")
elseif(UNIX)
  message("You're running CMake on Unix-based")
endif()

# loops
set(A "1")
set(B "2")

while(A LESS "1000000")
  message("${A}")
  math(EXPR T "${A} + ${B}")
  set(A "${B}")
  set(B "${T}")
endwhile()

# lists
set(ARGS "EXPR;T;1+1")
math(${ARGS}) # math(EXPR T "1+1")
set(MY_LIST These are separate arguments)
list(REMOVE_ITEM MY_LIST "separate")
message("${MY_LIST}")

foreach(ARG ${MY_LIST})
  message("${ARG}")
endforeach(ARG)

# functions
function(doubleIt OUT IN)
  math(EXPR RESULT "${IN} * 2")
  set(${OUT} "${RESULT}" PARENT_SCOPE) # 짜가 리턴
endfunction(doubleIt)

doubleIt(RESULT "100")
message("${RESULT}")

# functions with ARGN keywords
function(doubleEach OUT)
  set(RET "")

  foreach(ARG ${ARGN})
    math(EXPR N "${ARG} * 2")
    list(APPEND RET "${N}")
    message("inside of function <doubleEach>: RET = ${RET}")
  endforeach()

  set(${OUT} "${RET}" PARENT_SCOPE)
endfunction(doubleEach)

doubleEach(RET 5 6 7 8)
message("functions with ARGN keywords: ${RET}")

# Messing around with real cpp files
# https://github.com/methylDragon/coding-notes/blob/master/CMake/01%20CMake%20-%20Basics%20and%20Scripting.md#2.2
# https://www.tuwlab.com/ece/27270
# 요구 CMake 최소 버전
cmake_minimum_required(VERSION 2.6)

# 프로젝트 이름 및 버전
project("sample_example")
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)

# 빌드 config 및 기타등등 옵션
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_VERBOSE_MAKEFILE true)

# 빌드대상 바이너리 파일명 및 소스파일 목록
set(
  OUTPUT_EXEC
  "${CMAKE_PROJECT_NAME}.${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.out"
)
set(
  SOURCE_FILES
  src/sample.cpp
  src/sample_fibonacci.cpp
)

# 공통 헤더파일 디렉토리
include_directories(include)

# 공통 컴파일 옵션, 링크 옵션
add_compile_options(-g -Wall)
set(CMAKE_EXE_LINKER_FLAGS "-static -Wl,--gc-sections")

# 공통 링크 라이브러리 디렉토리
link_directories(/usr/lib)

# Debug 한정 컴파일 옵션, 링크 옵션
set(CMAKE_C_FLAGS_DEBUG "-DDEBUG -DC_FLAGS")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-DDEBUG -DLINKER_FLAGS")

# Release 한정 컴파일 옵션, 링크 옵션
set(CMAKE_C_FLAGS_RELEASE "-DRELEASE -DC_FLAGS")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-DRELEASE -DLINIKER_FLAGS")

# 출력 디렉토리
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BUILD_TYPE}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BUILD_TYPE}/lib)

add_executable(${OUTPUT_EXEC} ${SOURCE_FILES}) # Create a target named MyApp