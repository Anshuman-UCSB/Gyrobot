#include <iostream>
#include <wiringPiI2C.h>
using namespace std;

int main(){
    int fd = wiringPiI2Csetup(0x68);
    if(fd==-1){
        cout<<"Error: Cannot open device."<<endl;
        exit(-1);
    }
    int reg = wiringPiI2CReadReg8(fd,0x1A);
    printf("%06X", reg);
    cout<<hex<<reg<<endl;
}