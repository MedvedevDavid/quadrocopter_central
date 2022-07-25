#ifndef GY86_DRIVER_HPP
#define GY86_DRIVER_HPP
#include <stdint.h>
#include "i2c_adapter.hpp"

namespace GY_86
{
    
    class GY86_User
    {
        protected:
            int i2c_id;
            I2C_driver *I2C_Port;
        public:
            GY86_User(int);
    };

}

#endif