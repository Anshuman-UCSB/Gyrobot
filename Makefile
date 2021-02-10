test:
	python test.py

install:
	python3 -m venv venv
	source venv/bin/activate
	pip install mpu6050-raspberrypi
	