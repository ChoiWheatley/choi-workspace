#
# 1
#

달러당원화 = 1175

print("환전 계산 프로그램입니다.")
한국돈 = int(input("한국 돈 입력: "))
answer = 한국돈 / 달러당원화

print(한국돈, "원을 환전하면", int(answer), "달러 입니다.")

#
# 2
#

kilo_per_mile = 1.60934

print("=== 킬로미터-마일 거리변환 프로그램 ===")
입력 = float(input("Km 거리 입력 -> "))
answer = 입력 / kilo_per_mile
print("입력한 킬로미터거리: %.2f km" % (입력))
print("변환된 마일거리: %.2f miles" % (answer))
