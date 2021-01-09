#include <iostream>
#include <wiringPiI2C.h>
#include <wiringPi.h>
using namespace std;

int main(){
    int reg;
    uint8_t regH, regL;
    int fd = wiringPiI2CSetup(0x68);
    if(fd==-1){
        cout<<"Error: Cannot open device."<<endl;
        exit(-1);
    }
    reg = wiringPiI2CReadReg8(fd,0x1A);
    printf("%06X", reg);
    
    wiringPiI2CWriteReg8(fd,107, 0b10000000);                   // PWR_MGMT_1[7=DEVICE_RESET]
    delay(100);
    wiringPiI2CWriteReg8(fd,104, 0b00000111);                   // RESETTING DATAPATH
    delay(100);


    reg = wiringPiI2CReadReg8(fd,26);
    wiringPiI2CWriteReg8(fd,26, (reg&0b11111000)|0b00000110);   //Set low pass filter to 6
    regH = wiringPiI2CReadReg8(fd,67);
    regL = wiringPiI2CReadReg8(fd,68);
    reg = (regH<<8) + regL;
    if(reg>65535){
        reg=reg-65535;
    }
    printf("Gyro X: %04X", reg);
}