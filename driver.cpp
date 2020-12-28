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
		while(!done){
			if(speed<0)
				for(int i = 0;i<2;i++)
					digitalWrite(dir[i],0);
			else
				for(int i = 0;i<2;i++)
					digitalWrite(dir[i],0);
			if(speed !=0)
				for(int i = 0;i<2;i++)
					digitalWrite(step[i], !digitalRead(step[i]));
			// delay((1-abs(speed))*(maxDelay-minDelay));
			delay(11-abs(speed)/10);
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
	cout<<"Reached"<<endl;
	while(1){
		string temp;
		cout<<"Enter a speed: ";
		cin>>temp;
		d.speed = stoi(temp);
		cout<<"New speed: "<<d.speed<<endl;
	}
}

