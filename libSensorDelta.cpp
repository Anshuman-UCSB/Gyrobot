#include <iostream>
#include <wiringPi.h>
#include <stdio.h>
#include <cmath>
#include "libSensor.h"

using namespace std;

int main()
{
    if (wiringPiSetup() == -1)
        return -1;

    Sensor gyro;
    perror("Init gyro");

    int oX, oY, oZ;
    int x,y,z;
    oX = oY = oZ = 0;
    int tolerance = 5;
    while(1){
        x=gyro.getAccelX();
        y=gyro.getAccelY();
        z=gyro.getAccelZ();
	if(abs(x-oX)>tolerance || abs(y-oY)>tolerance || abs(z-oZ)>tolerance){
        	printf("x=%d    y=%d    z=%d      ax=%f\n", x-oX, y-oY, z-oZ, gyro.getAngleX());
		oX = x;
		oY = y;
		oZ = z;
	}
    }
}

