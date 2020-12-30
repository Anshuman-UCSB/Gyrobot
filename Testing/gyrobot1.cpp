#include <iostream>
#include "../Classes/gyro.cpp"
#include "../Classes/driver.cpp"
using namespace std;


int main(){
	if(wiringPiSetupGpio() == -1)
		return -1;
    Gyro g(50);
	Driver d(14,27,15,17);
	d.speed = 0;
	for(;;){
		float x = g.getGyro().x;
		d.speed = x;
		cout<<"\r\r"<<x;
		delay(10);
	}
}

