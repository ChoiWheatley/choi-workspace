import turtle as t

def goUp():
    t.setheading(90)
    t.fd(50)
def goDown():
    t.setheading(270)
    t.fd(50)
def goRight():
    t.setheading(0)
    t.fd(50)
def goLeft():
    t.setheading(180)
    t.fd(50)

t.speed(0)
t.shape('turtle')
t.shapesize(2)
screen = t.Screen()
screen.listen()
screen.onkey(goLeft, 'Left')
screen.onkey(goRight, 'Right')
screen.onkey(goUp, 'Up')
screen.onkey(goDown, 'Down')

screen.exitonclick()
