#include <iostream>
#include <wiringPi.h>
#include <thread>

using namespace std;

class Driver{
	int step[2], dir[2];
	double speed;
	int minDelay(0), maxDelay(1000);
	bool done;
	Driver(int stepA, int stepB, int dirA, int dirB){
		done = false;
		step = {stepA, stepB};
		dir = {dirA, dirB};
		for(int i = 0;i<2;i++){
			pinMode(step[i],OUTPUT);
			pinMode(dir[i],OUTPUT);
			digitalWrite(dir[i],1);
		}
		thread t(&Driver::asyncDriver, this);
		t.detach();
	}

	void asyncDriver(){
		while(!done){
			if(speed<0)
				for(int i = 0;i<2;i++)
					digitalWrite(dir[i],0);
			else
				for(int i = 0;i<2;i++)
					digitalWrite(dir[i],0);
			digitalWrite(step[i], !digitalRead(step[i]));
			delay(abs(speed)*(maxDelay-minDelay));
		}
	}

	void kill(){
		done = true;
	}
}

int main(){
	if(wiringPiSetupGpio() == -1)
		return -1;
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
		delay(1);
	}
}

