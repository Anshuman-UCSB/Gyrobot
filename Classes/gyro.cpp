#include <iostream>
#include <vector>
#include <wiringPi.h>
#include <thread>
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
    return t/1;
}

class Gyro{
    public:
    Sensor gyro;
    vector<Coord> v;
    int ind, wait, buffer;
    bool done;
    Gyro(int buff = 10){
        //Assume wiringPiSetupGpio already done
        done = false;
        buffer = buff;
        v = vector<Coord>(buffer);
        ind = 0;    
        wait  = 1;
        thread t(&Gyro::update, this);
        t.detach();
    }

    void update(){
        while(!done){
            v[ind++] = getGyroInstant();
            ind%=buffer;
            delay(wait);
        }
    }

    Coord getGyro(){
        return getAvg(v);
    }

    Coord getGyroInstant(){
        return Coord(gyro.getAngleX(),gyro.getAngleY(),gyro.getAngleZ());
    }
    
    void kill(){
        done = true;
    }
};
