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
cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

# 빌드 config 및 기타등등 옵션
set(CMAKE_BUILD_TYPE DEBUG)

# 프로젝트 이름 및 버전
project(MyMain VERSION 1.0.1)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

# 빌드대상 바이너리 파일명 및 소스파일 목록
set(
  SOURCE_FILES
  src/sample_fibonacci.cpp
  src/sample_main.cpp
)
set(LIBRARIES MyLib)

# current working directory in a absolute path
set(
  CWD
  ${CMAKE_SOURCE_DIR}
)

# Debug 한정 컴파일 옵션, 링크 옵션
if(${CMAKE_BUILD_TYPE} STREQUAL DEBUG)
  set(CMAKE_C_FLAGS_DEBUG "-DDEBUG -DC_FLAGS")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-DDEBUG -DLINKER_FLAGS")
elseif(${CMAKE_BUILD_TYPE} STREQUAL RELEASE)
  # Release 한정 컴파일 옵션, 링크 옵션
  set(CMAKE_C_FLAGS_RELEASE "-DRELEASE -DC_FLAGS")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-DRELEASE -DLINIKER_FLAGS")
endif()

# 공통 컴파일 옵션, 링크 옵션
add_compile_options(-Wall)

include_directories(/usr/include)

add_subdirectory(lib)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBRARIES})