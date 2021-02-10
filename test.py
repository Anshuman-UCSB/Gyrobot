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

delay = [1]
p = Thread(target = step, args=[delay])
p.daemon = True
p.start()

sleep(2)
print("changing speed")
delay[0] = .001
sleep(5)
print("DONE")
exit(1)

while True:
    data= sensor.get_gyro_data()
    print('\033c')
    left.toggle()
    right.toggle()
    print(data['y'])
    sleep(.1)
