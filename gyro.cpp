#include <iostream>
#include <vector>
#include <wiringPi.h>
#include "libSensor.h"
using namespace std;

struct Coord{
    float x, y, z;
    Coord():x(0), y(0), z(0){}
    Coord(float a, float b, float c):x(a), y(b), z(c){}
    Coord(const Coord& c){
        x = c.x;
        y = c.y;
        z = c.z;
    }


    Coord operator+(const Coord& c){
        Coord out;
        out.x = x+c.x;
        out.y = y+c.y;
        out.z = z+c.z;
        return out;
    }

    void operator+=(const Coord& c){
        x = x+c.x;
        y = y+c.y;
        z = z+c.z;
    }

    Coord operator/(int num){
        Coord c(x,y,z);
        c.x/=num;
        c.y/=num;
        c.z/=num;
        return c;
    }

    
};

ostream& operator<<(ostream& os, const Coord& c)
{
    os<<"("<<c.x<<", "<<c.y<<", "<<c.z<<")";
    return os;
}

Coord getAvg(vector<Coord>& v){
    Coord t;
    for(auto& c: v){
        t+=c;
    }
    return t/10;
}

int main(){
	if(wiringPiSetupGpio() == -1)
		return -1;
	Sensor gyro;
	printf("Init gyro\n");
    vector<Coord> v(10);
    int ind = 0;
	
	while(1){
		v[ind++]=Coord(gyro.getAngleX(),gyro.getAngleY(),gyro.getAngleZ());
        ind%=10;
		printf("\033c");
        auto c = getAvg(v);
        cout<<c.x<<"\n"<<c.y<<"\n"<<c.z<<endl;

		delay(1);
			
	}


}

