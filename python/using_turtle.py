import turtle as t
import time
import math

'''
t.shape('turtle')
t.color('blue')
t.shapesize(5)
t.setheading(90)

t.forward(300)
t.right(90)

time.sleep(1)
t.forward(200)
t.shapesize(10)
'''

screen = t.getscreen()

t.speed(0)
t.shape('turtle')
t.shapesize(1)

#print("=== 사각형을 그리는 거북이 ===")
temp = t.textinput("polygon", "몇 각형을 그릴까요 : ")
vertex = int(temp)

rad = math.radians( 360 / vertex / 2 )
radius = screen.window_height() / 2
side = radius * math.tan(rad)

t.penup()
t.setpos(-radius / 2,0)
t.pendown()
t.left(90)

for i in range(vertex):
    t.fd(side)
    t.right(360/vertex)
