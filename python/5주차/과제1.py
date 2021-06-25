import sys

criteria = range(2, 10)

prompt = int(input("2에서 9 까지의 정수를 입력하세요"))
if not(prompt in criteria):
    print("입력값이 잘못되었습니다. 2<=x<=9");
    sys.exit()

i = 1
while i < 10:
    print("{0:>5} * {1:>5} = {2:>5}".format(prompt, i, prompt * i))
    i = i+1

print()

for i in range(1,10):
    print("{0:>5} * {1:>5} = {2:>5}".format(prompt, i, prompt * i))
