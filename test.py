from mpu6050 import mpu6050
from time import sleep, time
from gpiozero import LED

sensor = mpu6050(0x68)

left = LED(27)
right= LED(14)
leftDir = LED(17)
leftDir.on()

def step(delay):
    while True:
        start = time()
        print(start)
        left.toggle()
        right.toggle()

step(1)

while True:
    data= sensor.get_gyro_data()
    print('\033c')
    left.toggle()
    right.toggle()
    print(data['y'])
    sleep(.1)
