import math

#
# 1
#

regular_diameter = 8 #inch
large_diameter = 12 #inch

regular_radius = regular_diameter / 2
large_radius = large_diameter / 2

large_area = (large_radius**2) * math.pi
regular_area = (regular_radius**2) * math.pi

lar_per_reg = large_area / regular_area
print("라지 사이즈 피자가 레귤러 사이즈 피자보다 ", lar_per_reg, " 배 더 큽니다.")


#
# 2
#

x = 50_000
interest = 0.06
year = 10
answer = x * ((1+interest) ** year)
print("10년 후의 쌀 가격은 ", answer, "원 입니다.")
