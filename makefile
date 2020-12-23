Delta:
	g++ libSensorDelta.cpp libSensor.cpp -o test -l wiringPi

testMain: FORCE
	g++ testMain.cpp libSensor.cpp -o testMain -l wiringPi

.PHONY: FORCE

FORCE:
