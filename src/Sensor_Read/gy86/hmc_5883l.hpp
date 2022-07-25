#ifndef HMC_5883L_HPP
#define HMC_5883L_HPP
#include "gy86_parameters.hpp"
#include "gy86_driver.hpp"

namespace GY_86
{
    struct magnet_ret{
        float x, y, z;
    };
    class HMC5883L_User:GY86_User
    {
        private:
            void HMC5883L_setGain(uint8_t gain);
            void HMC5883L_setMode(uint8_t newMode);
            uint8_t buffer[6];
            uint8_t mode;

        public:
            HMC5883L_User():GY86_User(HMC5883L_ADDR){};
            magnet_ret get_magnet_xyz(void);
            void HMC5883L_initialize(void);
            bool HMC5883L_getReadyStatus();
    };
}
#endif // HMC_5883L_HPP