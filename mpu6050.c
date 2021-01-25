#include <stdio.h>
#include <stdlib.h>
#include <wiringPiI2C.h>
#include "mpu6050.h"

double gyroXcali, gyroYcali, gyroZcali;
int ret, fd, reg;
int regH, regL;

int gyroX, gyroY, gyroZ;
int gyroXold, gyroYold, gyroZold;
double angleX, angleY, angleZ;

int getReg16(int fd, int aH, int aL) {
  int regH, regL, reg;
  regH = wiringPiI2CReadReg8(fd, aH);
  regL = wiringPiI2CReadReg8(fd, aL);
  reg = (regH<<8) | (regL&0xff);
  if (reg & 0x8000) { 
    reg = -1*((~reg-1)&0XFFFF); 
    //printf ("Reg=%X %d\n",reg, reg);
  }
  return(reg);
}

void gyroCalib() {
  printf("Calibrating the Gyro...\n");
  gyroXcali=gyroYcali=gyroZcali=0;
  for (int i=0; i<5000; i++) {
    
    gyroX = getReg16(fd, GYRO_XOUT_H, GYRO_XOUT_L)>>4;
    gyroY = getReg16(fd, GYRO_YOUT_H, GYRO_YOUT_L)>>4;
    gyroZ = getReg16(fd, GYRO_ZOUT_H, GYRO_ZOUT_L)>>4;

    gyroXcali = gyroXcali + gyroX;
    gyroYcali = gyroYcali + gyroY;
    gyroZcali = gyroZcali + gyroZ;
    if(i%2) printf ("\\ \r");
    else printf ("/\r");
    fflush (stdout);
  }
  gyroXcali = gyroXcali/5000;
  gyroYcali = gyroYcali/5000;
  gyroZcali = gyroZcali/5000;
  printf("Done.. %f, %f, %f\n", gyroXcali, gyroYcali, gyroZcali);
}


int main () {
  int del = 50;

  fd = wiringPiI2CSetup(0x68);
  if (fd == -1) { 
    printf ("Error opening device \nExiting...\n");
    exit(-1);
  } else {
    printf ("Opened device handle:%d\n", fd);
  }

  ret = wiringPiI2CReadReg8(fd, PWR_MGMT_1);
  printf ("%02X\n", ret&0xff);
  wiringPiI2CWriteReg8(fd, PWR_MGMT_1, 0x80);             // Resetting PWR_MGMT_1[7] and SLEEP==0
  delay (100);
  wiringPiI2CWriteReg8(fd, PWR_MGMT_1, 0x01);             // Select clock source

  wiringPiI2CWriteReg8(fd, GYRO_CONFIG, 0x00);            // GYRO_CONFIG == 0;

  wiringPiI2CWriteReg8(fd, SIGNAL_PATH_RESET, 0x7);              // Resetting data path SIGNAL_PATH_RESET [2:0]
  ret = wiringPiI2CReadReg8(fd, SIGNAL_PATH_RESET);
  printf ("%02X\n", ret&0xff);

  ret = wiringPiI2CReadReg8(fd, CONFIG);
  printf ("%02X\n", ret&0xff);
  gyroCalib();
  gyroCalib();
  gyroCalib();

  while(1) {
    gyroX = getReg16(fd, GYRO_XOUT_H, GYRO_XOUT_L)>>4;
    gyroY = getReg16(fd, GYRO_YOUT_H, GYRO_YOUT_L)>>4;
    gyroZ = getReg16(fd, GYRO_ZOUT_H, GYRO_ZOUT_L)>>4;
    //printf ("Gyro[X::%3d, %3d, %3d]", gyroX, gyroY, gyroZ);

    gyroXold=gyroX;
    gyroYold=gyroY;
    gyroZold=gyroZ;

    angleX = angleX + (del * (gyroX + gyroXold - (2*gyroXcali)) * 0.00000382);
    angleY = angleY + (del * (gyroY + gyroYold - (2*gyroYcali)) * 0.00000382);
    angleZ = angleZ + (del * (gyroZ + gyroZold - (2*gyroZcali)) * 0.00000382);
    printf ("Angle[X:%2.02f, y:%2.02f, z:%2.02f]",angleX, angleY, angleZ);
 
    printf ("\r");
    fflush(stdout);
    delay (del);
  }
}
