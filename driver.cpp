#include <iostream>
#include <wiringPi.h>
#include <thread>

using namespace std;

class Driver{
	public:
	int step[2], dir[2];
	double speed;
	int minDelay, maxDelay;
	bool done;
	Driver(int stepA, int stepB, int dirA, int dirB){
		minDelay = 0;
		maxDelay = 1000;
		done = false;
		step[0] = stepA;
		step[1] = stepB;
		dir[0] = dirA;
		dir[1] = dirB;
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
			for(int i = 0;i<2;i++)
				digitalWrite(step[i], !digitalRead(step[i]));
			delay(abs(speed)*(maxDelay-minDelay));
		}
	}

	void kill(){
		done = true;
	}
};

int main(){
	if(wiringPiSetupGpio() == -1)
		return -1;
	Driver d(14,27,15,17);
	d.speed = .1;
}

