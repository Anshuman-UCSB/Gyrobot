#include <iostream>
#include <wiringPiI2C.h>
using namespace std;

int main(){
    int fd = wiringPiI2Csetup(0x68);
    if(fd==-1){
        cout<<"Error: Cannot open device."<<endl;
        exit(-1);
    }
    cout<<wiringPiI2CRead(0x1A)<<endl;
}