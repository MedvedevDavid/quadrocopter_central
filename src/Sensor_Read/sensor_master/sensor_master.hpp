#ifndef __SENSOR_MASTER_HPP
#define __SENSOR_MASTER_HPP
#include "gy86_driver.hpp"
#include "Kalman.h"

namespace sensormaster{

class Sensor_Data
{
    private:
        GY_86::MPU6050_User *mpu6050;
        uint64_t previous_time;
        Kalman kalman_x, kalman_y;
    public:
        Sensor_Data();
        void MPU_get_data();
};


}




#endif