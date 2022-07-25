#ifndef __SENSOR_MASTER_HPP
#define __SENSOR_MASTER_HPP
#include "gy86_driver.hpp"
#include "mpu_6050.hpp"
#include "hmc_5883l.hpp"
#include "Kalman.h"

namespace sensormaster{

class Sensor_Data
{
    private:
        GY_86::MPU6050_User *mpu6050;
        GY_86::HMC5883L_User *hmc5883l;
        uint64_t previous_time;
        Kalman kalman_x, kalman_y;
        float magneto_yaw;
    public:
        Sensor_Data();
        void MPU_get_data();
        void magnetometer_sensor_data_processing();
};


}




#endif