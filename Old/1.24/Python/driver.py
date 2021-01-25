from time import time, sleep
from gpiozero import LED
LED(23).on()
LED(22).on()

def step(left, right):
    left.toggle()
    right.toggle()
    sleep(0.001)
    left.toggle()
    right.toggle()


def setDir(left, right, val): #if val > 0, forwards
    if(val>0):
        left.on();
        right.off();
    else:
        left.on();
        right.off();


left = LED(14)
right = LED(27)
setDir(left, right, 1)

for i in range(10000):
    step(left, right)
    sleep(.0001)
