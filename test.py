from mpu6050 import mpu6050
from time import sleep, time
from gpiozero import LED
from threading import Thread

sensor = mpu6050(0x68)


def step(delay, leftPin=27, rightPin = 14, leftDirPin = 17):
    left = LED(leftPin)
    right= LED(rightPin)
    leftDir = LED(leftDirPin)
    leftDir.on() # set bias

    while True:
        start = time()
        while time()-start<delay[0]:
            pass
        left.toggle()
        right.toggle()

def changeDir(input, leftDirPin = 17,rightDirPin = 17, lForwards = 1, rForwards=0):
    "if input is >0, forwards else backwards"
    leftDir = LED(leftDirPin)
    rightDir = LED(rightDirPin)
    if(input>0):
        leftDir.value = lForwards
        rightDir.value = rForwards
    else:
        leftDir.value = (0 if lForwards == 1 else 1)
        rightDir.value = (0 if rForwards == 1 else 1)


delay = [1]
p = Thread(target = step, args=[delay])
p.daemon = True
p.start()

# sleep(2)
# print("changing speed")

mx = 0
while True:
    data= sensor.get_gyro_data()
    dy = data['y']
    print('\033c',dy)
    mx = max(mx, abs(dy))
    changeDir(dy)
    delay[0] = .0001
