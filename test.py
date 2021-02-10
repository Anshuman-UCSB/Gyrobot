from mpu6050 import mpu6050
from time import sleep
from gpiozero import LED

sensor = mpu6050(0x68)

left = LED(27)
right= LED(14)
leftDir = LED(17)
leftDir.on()

def step():
    while True:
        # sleep(0.01)
        left.toggle()
        right.toggle()

step()

while True:
    data= sensor.get_gyro_data()
    print('\033c')
    left.toggle()
    right.toggle()
    print(data['y'])
    sleep(.1)
