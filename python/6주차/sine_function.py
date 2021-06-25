import turtle
import math

# draw_function draws any function that user given
# This function starts at leftmost side of the screen,
# where y coordinate is 0. it recieves x coordinate
# and return the required y value.
def draw_function(x, func=math.sin, amplitude=1.0, x_ratio=1.0):
    return amplitude * func(x * x_ratio)

screen = turtle.Screen()
turtle.shape('circle')
turtle.turtlesize(1,1)
turtle.speed(0)
turtle.penup()
turtle.goto(-(screen.window_width()/2),0)
turtle.pendown()
for i in range(0, screen.window_width(), 1):
    #print(draw_function(i))
    turtle.goto(i-(screen.window_width()/2), draw_function(i+1, math.log2, 30, 0.1))

screen.exitonclick()
