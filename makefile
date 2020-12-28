Delta: FORCE
	g++ Testing/libSensorDelta.cpp Classes/libSensor.cpp -o Binaries/test -l wiringPi

testMain: FORCE
	g++ Testing/testMain.cpp Classes/libSensor.cpp -o Binaries/testMain -l wiringPi

printGyro: FORCE
	g++ Testing/printGyroAngle.cpp Classes/libSensor.cpp -o Binaries/printGyro -l wiringPi

gyro: FORCE
	g++ Testing/gyro.cpp Classes/libSensor.cpp -o Binaries/gyro -l wiringPi -pthread

driver: FORCE
	g++ Testing/driver.cpp -o Binaries/driver -l wiringPi -pthread

.PHONY: FORCE

FORCE:
