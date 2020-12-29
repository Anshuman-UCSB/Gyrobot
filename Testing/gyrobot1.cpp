#include <iostream>
#include "../Classes/gyro.cpp"
#include "../Classes/driver.cpp"
using namespace std;


int main(){
	if(wiringPiSetupGpio() == -1)
		return -1;
    Gyro g(100);
	Driver d(14,27,15,17);
	d.speed = 0;
	for(;;){
		float x = g.getGyro().x;
		d.speed = abs(x)>4?(x>0?80:-80):0;
		cout<<x<<endl;
		delay(10);
	}
}

