import turtle as t
import time
import random
import math
import winsound

t.shape('turtle')
t.shapesize(1)
t.speed(0)
screen = t.Screen()
print(screen.screensize(), "sample", sep="구분자", end=" ")
while True:
    angle = random.randint(-180, 180)
    t.rt( angle )
    t.fd(50)
    if abs(t.pos()[0]) > screen.screensize()[0] or \
       abs(t.pos()[1]) > screen.screensize()[1]:
        t.penup()
        t.home()
        t.pendown()
        winsound.Beep(random.randint(1,20000),500)
        


