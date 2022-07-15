#include "gy86_driver.hpp"
#include <iostream>
#include "parameters.hpp"
#include <iostream>
#include <unistd.h>
#include <wiringPi.h>

using namespace GY_86;

void MPUDataInterrupt();	// Function prototype

MPU6050_User *mpu6050;
int main()
{
    if(wiringPiSetup()<0)
    {
        std::cout << "Init Failed" << std::endl;
    }
    pinMode(24, INPUT);

    MPU_ConfigTypeDef mpu_configuration;

    //Configure accelerometer and GYRO parameters
    mpu_configuration.Accel_Full_Scale = accel_FullScale_ENUM::AFS_SEL_4g;
    mpu_configuration.ClockSource = PM_CLKSEL_ENUM::Internal_8MHz;
    mpu_configuration.CONFIG_DLPF = DLPF_CFG_ENUM::DLPF_184A_188G_Hz;
    mpu_configuration.Gyro_Full_Scale = gyro_FullScale_ENUM::FS_SEL_500;
    mpu_configuration.Sleep_Mode_Bit = 0;
    mpu_configuration.INTA_ENABLED = 1;
    mpu_configuration.Sample_Rate_Devider = 4;

    mpu6050 = new MPU6050_User();
    mpu6050->config(mpu_configuration);

    // Cause an interrupt when data recieved
     
    if(wiringPiISR (24, INT_EDGE_RISING, &MPUDataInterrupt)<0)
    {
        std::cout << "ISR Failed" << std::endl;
    }

    while(1)
    {
        	

        sleep(0.5);
    }
}

// Our interrupt routine
void MPUDataInterrupt()
{
    ScaledData_Def scaledDef;
    mpu6050->MPU6050_Get_Accel_Scale(&scaledDef);
    std::cout << scaledDef.x << std::endl;
    std::cout << scaledDef.y << std::endl;
    std::cout << scaledDef.z << std::endl;

    mpu6050->MPU6050_Get_Gyro_Scale(&scaledDef);
    std::cout << scaledDef.x << std::endl;
    std::cout << scaledDef.y << std::endl;
    std::cout << scaledDef.z << std::endl;
}