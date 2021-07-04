import sys


child = 7
elem = 13
mid = 16
high = 19
univ = 26
thisyear = 2021

prompt = int(input("출생년도를 입력해 주세용 "))

delta_year = thisyear - prompt + 1

if delta_year < 0:
    print("나이는 음수가 될 수 없습니다!");
elif delta_year <= child:
    print("어린이 입니다.");
elif delta_year <= elem:
    print("초등학생 입니다.");
elif delta_year <= mid:
    print("중학생 입니다.");
elif delta_year <= high:
    print("고등학생 입니다.");
elif delta_year <= univ:
    print("대학생 입니다.");
else:
    print("직장인 입니다.");
