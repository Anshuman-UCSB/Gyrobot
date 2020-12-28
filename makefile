Delta: FORCE
	g++ Testing/libSensorDelta.cpp Classes/libSensor.cpp -o Binaries/test -l wiringPi
	./Binaries/test

testMain: FORCE
	g++ Testing/testMain.cpp Classes/libSensor.cpp -o Binaries/testMain -l wiringPi
	./Binaries/testMain

printGyro: FORCE
	g++ Testing/printGyroAngle.cpp Classes/libSensor.cpp -o Binaries/printGyro -l wiringPi
	./Binaries/printGyro

gyro: FORCE
	g++ Testing/gyro.cpp Classes/libSensor.cpp -o Binaries/gyro -l wiringPi -pthread
	./Binaries/gyro

driver: FORCE
	g++ Testing/driver.cpp -o Binaries/driver -l wiringPi -pthread
	./Binaries/driver

classTest: FORCE
	g++ Testing/classTest.cpp -o Binaries/classTest -l wiringPi -pthread
	./Binaries/classTest

clean: FORCE
	rm Binaries/*
	echo Cleaned!

.PHONY: FORCE

FORCE:
