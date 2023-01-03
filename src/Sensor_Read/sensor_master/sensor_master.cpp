#include "sensor_master.hpp"
#include <iostream>
#include <chrono>
#include <cmath>

using namespace GY_86;
using namespace std::chrono;

namespace sensormaster{

Sensor_Data::Sensor_Data()
{
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
    previous_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    hmc5883l = new HMC5883L_User(); 
    hmc5883l->HMC5883L_initialize();
}

void Sensor_Data::MPU_get_data()
{
    ScaledData_Def scaledGyro;
    ScaledData_Def scaled_raw_Accel;

    mpu6050->Get_Accel_Scale(&scaled_raw_Accel);
    raw_angle scaledAccel = mpu6050->get_xy_accel_angles();

    mpu6050->Get_Gyro_Scale(&scaledGyro);
    
    uint64_t corrent_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    float dt_in_sec = (float)(corrent_time-previous_time)/1000;
    previous_time = corrent_time;

    float filtered_anggle_x = kalman_x.getAngle(scaledAccel.x_angle,scaledGyro.x,dt_in_sec);
    float filtered_anggle_y = kalman_y.getAngle(scaledAccel.y_angle,scaledGyro.y,dt_in_sec);
    std::cout << scaledAccel.x_angle << "   " << scaledGyro.x << "   "<< dt_in_sec << "   " << filtered_anggle_x << std::endl;
    std::cout << filtered_anggle_y << std::endl;

}


void Sensor_Data::magnetometer_sensor_data_processing()
{
    magnet_ret magnetometer_data;

    if (hmc5883l->HMC5883L_getReadyStatus())
    {
       magnetometer_data = hmc5883l->get_magnet_xyz();
    }

    auto myangle = mpu6050->get_xy_accel_angles();

    float y_angle = myangle.y_angle * PI / 180.0;
    float x_angle = myangle.x_angle * PI / 180.0;

    float Mx = magnetometer_data.x * cos(y_angle) + magnetometer_data.z * sin(y_angle);
    float My = magnetometer_data.x * sin(x_angle) * sin(y_angle) + magnetometer_data.y * cos(x_angle) - magnetometer_data.z * sin(x_angle) * cos(y_angle);
    magneto_yaw = atan2(-My,Mx)*RAD_TO_DEG;
    //magneto_yaw = atan2(y,x)*RAD_TO_DEG;
    //std::cout << "Magneto: " << magneto_yaw << std::endl;
}
}