#include <iostream>
#include <wiringPi.h>
#include "../Classes/libSensor.h"

using namespace std;

int main(){
	if(wiringPiSetupGpio() == -1)
		return -1;
	Sensor gyro;
	printf("Init gyro\n");

	float xyz[3];
	
	while(1){
		xyz[0]=gyro.getAngleX();
		xyz[1]=gyro.getAngleY();
		xyz[2]=gyro.getAngleZ();
		printf("\033c");
		cout<<int(xyz[0])<<"\n"<<int(xyz[1])<<"\n"<<int(xyz[2])<<endl;
		

		delay(1);
			
	}


}

