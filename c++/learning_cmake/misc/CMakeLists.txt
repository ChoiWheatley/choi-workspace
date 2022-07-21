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
elseif(APPLE)
  message("You're running CMake on Apple")
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