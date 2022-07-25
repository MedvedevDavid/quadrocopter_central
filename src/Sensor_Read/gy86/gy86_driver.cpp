#include "gy86_driver.hpp"
#include "i2c_adapter.hpp"


namespace GY_86
{

    GY86_User::GY86_User(int i2c_id)
    {
		I2C_Port = new I2C_driver(i2c_id);

    }

}