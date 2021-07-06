import turtle as 거북이

거북이.shape("turtle")
거북이.shapesize(3)
거북이.speed(0)

각도 = 144
변의개수 = 5
변의길이 = 300

for i in range(변의개수):
    거북이.fd(변의길이)
    거북이.right(각도)
