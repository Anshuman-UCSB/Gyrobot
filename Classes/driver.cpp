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
		// microstep
		// digitalWrite(23,1);
		// digitalWrite(22,1);
		speed = 0;
		minDelay = 1;
		maxDelay = 100;
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
		int delay;
		while(!done){
			delay = int(70./speed);
			if(speed<0)
				for(int i = 0;i<2;i++)
					digitalWrite(dir[i],0);
			else
				for(int i = 0;i<2;i++)
					digitalWrite(dir[i],1);
			if(delay<100)
				for(int i = 0;i<2;i++)
					digitalWrite(step[i], !digitalRead(step[i]));
			// delay((1-abs(speed))*(maxDelay-minDelay));
			cout<<"Delay is "<<delay<<endl;
			if(delay<100)
				this_thread::sleep_for(chrono::milliseconds(abs(delay)));

			// delay(1000);
		}
	}

	void kill(){
		done = true;
	}
};

