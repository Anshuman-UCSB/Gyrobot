from mpu6050 import mpu6050
from time import sleep, time
from gpiozero import LED
from threading import Thread

sensor = mpu6050(0x68)

used = [14,15,17,27]
pins = {}
for pin in used:
    pins[pin] = LED(pin)



def step(delay, leftPin=27, rightPin = 14, leftDirPin = 17):
    left = pins[leftPin]
    right= pins[rightPin]
    leftDir = pins[leftDirPin]
    leftDir.on() # set bias

    while True:
        start = time()
        while time()-start<delay[0]:
            pass
        left.toggle()
        right.toggle()

def changeDir(input, leftDirPin = 17,rightDirPin = 15, lForwards = 0, rForwards=0):
    "if input is >0, forwards else backwards"
    leftDir = pins[leftDirPin]
    rightDir = pins[rightDirPin]
    if(input>0):
        leftDir.value = lForwards
        rightDir.value = rForwards
    else:
        leftDir.value = (0 if lForwards == 1 else 1)
        rightDir.value = (0 if rForwards == 1 else 1)


def avg(lst): 
    return sum(lst) / len(lst) 

delay = [1]
p = Thread(target = step, args=[delay])
p.daemon = True
p.start()

# sleep(2)
# print("changing speed")

rollingFilter = []

while True:
    data= sensor.get_gyro_data()
    dy = data['y']
    rollingFilter.append(dy)
    if(len(rollingFilter)>=100):
        rollingFilter.pop(0)
    dyAvg = avg(rollingFilter[-10:])-avg(rollingFilter)
    print('\033c',dyAvg)
    changeDir(dyAvg)
    if abs(dyAvg)>4:
        delay[0] = .01/abs(dyAvg)
        sleep(.02)
    else:
        delay[0] = 999
    # sleep(1)
