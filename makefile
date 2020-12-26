Delta:
	g++ libSensorDelta.cpp libSensor.cpp -o test -l wiringPi

testMain: FORCE
	g++ testMain.cpp libSensor.cpp -o testMain -l wiringPi

printGyro:
	g++ printGyroAngle.cpp libSensor.cpp -o printGyro -l wiringPi

.PHONY: FORCE

FORCE:
