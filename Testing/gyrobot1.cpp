#include <iostream>
#include "../Classes/gyro.cpp"
#include "../Classes/driver.cpp"
using namespace std;


int main(){
	if(wiringPiSetupGpio() == -1)
		return -1;
    Gyro g(50);
	Driver d(14,27,15,17);
	d.delay = 0;
	float start = g.getGyro().x;
	for(;;){
		float x = g.getGyro().x-start;
		d.delay = abs(x)>.7 ? max(500./abs(x),1.):0;
		d.delay *= abs(x)/x;
		cout<<"\r\r"<<x;
		delay(10);
	}
}

