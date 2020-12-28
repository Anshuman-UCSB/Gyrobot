Delta: FORCE
	g++ libSensorDelta.cpp libSensor.cpp -o test -l wiringPi

testMain: FORCE
	g++ testMain.cpp libSensor.cpp -o testMain -l wiringPi

printGyro: FORCE
	g++ printGyroAngle.cpp libSensor.cpp -o printGyro -l wiringPi

gyro: FORCE
	g++ gyro.cpp libSensor.cpp -o gyro -l wiringPi -pthread



.PHONY: FORCE

FORCE:
