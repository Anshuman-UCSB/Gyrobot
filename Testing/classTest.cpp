#include <iostream>
#include "../Classes/gyro.cpp"
#include "../Classes/driver.cpp"
using namespace std;


int main(){
	if(wiringPiSetupGpio() == -1)
		return -1;
    Gyro g;
	Driver d(14,27,15,17);
	d.speed = 0;
	int crd[3], old[3]
	for(int i =0 ;;i++){
		auto t = g.getGyro();
		old[3] = {crd[0], crd[1], crd[2]};
		crd[3] = {t.x, t.y, t.z};
		if(old[0]!=crd[0] || old[1]!=crd[1] || old[2]!=crd[2])
			cout<<i<<": ("<<crd[0]<<", "<<crd[1]<<", "<<crd[2]<<")"<<endl;
		delay(10);
	}
}

