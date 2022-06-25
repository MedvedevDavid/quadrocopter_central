#include "gy86_driver.hpp"
#include "i2c_adapter.hpp"
#include "parameters.hpp"
#include <chrono>
#include <thread>

namespace GY_86
{
    using namespace std::this_thread;     // sleep_for, sleep_until
    using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
    using std::chrono::system_clock;
    
    void MPU6050::config(MPU_ConfigTypeDef &config)
    {
        I2C_Write8(this->i2c_id, PWR_MAGT_1_REG, 0x80);
        sleep_for(100ms);
        uint8_t Buffer = (int)config.ClockSource & 0x07; //change the 7th bits of register
        Buffer |= ((int)config.Sleep_Mode_Bit << 6) &0x40; // change only the 7th bit in the register
        I2C_Write8(this->i2c_id, PWR_MAGT_1_REG, Buffer);
        sleep_for(100ms); // should wait 10ms after changeing the clock setting.

        //Set the Digital Low Pass Filter
        Buffer = 0;
        Buffer = (int) config.CONFIG_DLPF & 0x07;
        I2C_Write8(this->i2c_id, CONFIG_REG, Buffer);
    }

    MPU6050::MPU6050(int i2c_id)
    {
        this->i2c_id = wiringPiI2CSetup(i2c_id);
    }


}