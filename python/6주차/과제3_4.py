import sys
#
# 3 p.178 체질량지수 계산하여 건강을 진단하는 예제를 함수를 이용하여 작성해보자.
#   - 키는 cm 단위로 입력받고, 몸무게는 kg 단위로 입력받는다.
#   - BMI 수치는 계산한 후 소수점 둘째자리까지 표현한다.
#   - BMI는 몸무게(kg)을 키(m)의 제곱으로 나누어 계산한다.
#
def bmi(height_cm, weight_kg):
    height_m = height_cm / 100
    return ( weight_kg / (height_m**2) )

def classify(bmi_val):
    if bmi_val <= 0:
        print("bmi 지수는 0 또는 음수가 될 수 없습니다.")
        sys.exit()
    elif bmi_val < 20:
        return("저체중 입니다.")
    elif 20 <= bmi_val < 25:
        return("정상체중 입니다.")
    elif 25 <= bmi_val < 30:
        return("경도비만 입니다.")
    elif 30 <= bmi_val < 40:
        return("비만 입니다.")
    else:
        return("고도비만 입니다.")

height_cm = float(input("키를 입력해 주세요 (cm)"))
weight_kg = float(input("몸무게를 입력해 주세요(kg)"))
print("당신은 {}".format(classify(bmi(height_cm, weight_kg))))


#
# 4 p.202 8번 문제 요구사항에 따라 함수를 정의하고 호출하여 풀 것
# 짝수인지 홀수인지 판별해주는 함수를 만들어보자. 사용자로부터 정수를 입력받아
# 그 정수가 짝수인지, 홀수인지 판별하여 출력해보자.
#
def even_odd(x):
    if x <= 0:
        return "음수는 판별할 수 없습니다"
    if x%2 == 0:
        return "짝수입니다."
    else:
        return "홀수입니다."

x = int(input("자연수를 입력해 주세요!"))
print(even_odd(x))

