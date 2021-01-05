from mpu6050 import mpu6050
from time import sleep, time
from logger import Logger

sensor = mpu6050(0x68)
l = Logger("http://192.168.0.34:5000/")
l.delete()
while True:
    gyro_data = sensor.get_gyro_data()
    print("x: " + str(gyro_data['x']))
    l.post(time(), gyro_data['x'])
    # requests.post("http://192.168.0.34:5000/", data = f"{time()},{gyro_data['x']}")
