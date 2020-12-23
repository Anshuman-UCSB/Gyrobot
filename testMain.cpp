#include <iostream>
#include <wiringPi.h>
#include "libSensor.h"

using namespace std;

int main(){
	if(wiringPiSetupGpio() == -1)
		return -1;
	Sensor gyro;
	printf("Init gyro");

	float xyz[3];
	
	int step[2] = {15,17};
	int dir[2] = {14,27};

	for(int i = 0;i<2;i++){
		pinMode(step[i],OUTPUT);
		pinMode(dir[i],OUTPUT);
		digitalWrite(dir[i],1);
	}

	for(int i = 0;i<5000;i++){
		for(int i = 0;i<2;i++){
			digitalWrite(step[i], !digitalRead(step[i]));
		}
		if(i == 2500){
			for(int i = 0;i<2;i++){
				digitalWrite(dir[i], 0);
			}
		}
		xyz[0]=gyro.getAngleX();
		xyz[1]=gyro.getAngleY();
		xyz[2]=gyro.getAngleZ();

		cout<<"("<<xyz[0]<<", "<<xyz[1]<<", "<<xyz[2]<<")"<<endl;
		

		delay(1);
			
	}


}
