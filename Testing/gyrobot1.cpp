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
		auto t = g.getGyro().x;
        cout<<t<<endl;
		delay(10);
	}
}

