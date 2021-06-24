import sys

quiz_ratio = 0.2
mid_ratio = 0.3
final_ratio = 0.5
cutline = 70

quiz = int(input("퀴즈 점수: "))
mid = int(input("중간고사 점수: "))
final = int(input("기말고사 점수: "))

if not( 0<=quiz<=100 and 0<=mid<=100 and 0<=final<=100 ):
    print("잘못된 값입니다.")
    sys.exit()

score = quiz * quiz_ratio + mid * mid_ratio + final * final_ratio

if score < 70:
    print("FAIL")
else:
    print("PASS")
