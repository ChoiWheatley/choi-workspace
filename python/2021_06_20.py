import random
print(random.randrange(1, 100))

a = """
Lorem ipsum dolor sit amet,
consectetur adipiscing elit,
sed do eiusmod tempor incididunt
ut labore et dolore magna aliqua
"""

# for (int i = 0; i < a.length; i++) 를 이렇게 표현하네
for i in range(len(a)):
    # Strings are array
    print(a[i])
print(a)

# Check String
# To check if a certain phrase or character is present in a string,
# we can use the keyword `in`
txt = "The best things in life are free!"
if "free" in txt:
    print("the string \"free\" is in this text!")
if "expensive" not in txt:
    print("the string \"expensive\" insn't in this text!")

# Slicing
# You can return a range of characters by using the slice syntax
# Specify the start index and the end index, separated by a colon, 
# to return a part of the string
b = "Hello, World!"
print(b[2:5] + '\n')
# slice from the start
print(b[:5] + '\n')
# slice to the end
print(b[2:] + '\n')
# negative indexing
for i in range(-1, -len(b)-1, -1):
    print(b[i])
print('\n' + b[-5:-2] + '\n')

# Upper case
print(b.upper())
# lower case
print(b.lower())
# replace string
print(b.replace('H', 'J'))
# split string
print(b.split(', '))

# string format
# "My age is" + 25 
# 이런 식으로 형이 다른 두 값을 동시에 취급할 수는 없다.
# The `format()` method takes the passed arguments, formats them,
# and places them in the string where the placeholders `{}` are
age = 25
greetings = ["Nice", "to", "meet", "you!"]
txt = "My name is Choi Wheatley, I am {} years old. {}"
print(txt.format(age, greetings[0:len(greetings)-1]))

print(txt.count('a'))
print(len(txt))
