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
	while(1){
        printf("\033c");
        cout<<int(g.getGyro().x)<<"\n";
        cout<<int(g.getGyro().y)<<"\n";
        cout<<int(g.getGyro().z)<<endl;
	}
}

