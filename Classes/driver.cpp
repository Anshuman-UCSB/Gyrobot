#include <iostream>
#include <wiringPi.h>
#include <thread>

using namespace std;

class Driver{
	public:
	int step[2], dir[2];
	int delay;
	bool done;
	Driver(int stepA, int stepB, int dirA, int dirB){
		// microstep
		digitalWrite(23,1);
		digitalWrite(22,1);
		speed = 0;
		delay = 9999;
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
		cout<<"Async driver started."<<endl;
		while(!done){
			delay = int(70./speed);
			if(speed<0)
				for(int i = 0;i<2;i++)
					digitalWrite(dir[i],0);
			else
				for(int i = 0;i<2;i++)
					digitalWrite(dir[i],1);
			if(abs(delay) < 100)
				for(int i = 0;i<2;i++){
					digitalWrite(step[i], !digitalRead(step[i]));
					this_thread::sleep_for(chrono::milliseconds(1));
					digitalWrite(step[i], !digitalRead(step[i]));
				}
			cout<<"Delay is "<<delay<<endl;
			if(abs(delay)<100)
				this_thread::sleep_for(chrono::milliseconds(abs(delay)));
		}
	}

	void kill(){
		done = true;
	}
};

