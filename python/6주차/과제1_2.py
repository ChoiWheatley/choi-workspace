
#
# 1. 2차 함수를 만들어보자. f(x)=3*x**2 + 5*x + 7 의 기능을 하는 함수를 정의해보자.
# 함수에 입력값 15, 20, 25를 입력하여 계산 결과를 출력해보자.
# 

def quadratic(x):
    return (3*(x**2) + 5*x + 7)

print(quadratic(15))
print(quadratic(20))
print(quadratic(25))

#
# 2. 삼각형의 밑변과 높이를 입력받아 삼각형의 넓이를 계산하여 알려주는 프로그램을
# 함수를 사용하여 만들어보자.
#

def area(base, height):
    return base * height / 2

base = float(input("삼각형의 밑변의 길이를 입력해주세요: "))
height = float(input("삼각형의 높이의 길이를 입력해주세요: "))

print("삼각형의 넓이는 {0:0.5f} 입니다.".format(area(base, height)))
