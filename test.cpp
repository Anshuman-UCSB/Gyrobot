#include <iostream>
#include <wiringPi.h>
using namespace std;

int main(){
	wiringPiSetupGpio();
	int step[2] = {15,2};
	int dir[2] = {14,17};
	for(int i = 0;i<2;i++){
		pinMode(step[i], OUTPUT);
		pinMode(dir[i], OUTPUT);
		digitalWrite(dir[i], 1);
	}
	/*pinMode(15, OUTPUT);
	pinMode(drive, OUTPUT);
	pinMode(dir, OUTPUT);
	pinMode(14, OUTPUT);
	digitalWrite(dir, 1);
	digitalWrite(14, 0);*/

	for(int i = 0;i<5000;i++){
		for(int i = 0;i<2;i++){
			digitalWrite(step[i], !digitalRead(step[i]));
		}
		if(i == 2500){
			for(int i = 0;i<2;i++){
				digitalWrite(dir[i], 0);
			}
		}
		delay(1);
	}
}
