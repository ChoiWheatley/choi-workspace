import sys

#
# 2: 양의 정수 A, B를 입력받아 A 부터 B까지 모두 더하시오.
# 만약 A > B 라면 프로그램을 종료한다.
#
a = int(input("A를 입력하세요: "))
b = int(input("B를 입력하세요: "))
if (a > b or a < 0 or b < 0):
    print("잘못된 입력입니다.")
    sys.exit()

ret = 0
while a <= b:
    ret += a
    a += 1
else:
    print("A부터 B까지 더한 수는 {} 입니다.".format(ret))

#
# 3: for문을 사용하여 100부터 150까지의 정수 중에서 7의 배수들의 
# 합계를 구하는 프로그램을 작성하시오.
#
ret = 0
for i in range(100, 151, 1):
    if i % 7 == 0:
        ret += i
else:
    print("100부터 150까지의 정수 중 7의 배수의 합은 {} 입니다.".format(ret))
