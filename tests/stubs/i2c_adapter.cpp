#include "i2c_adapter.hpp"

std::vector<int> i2c_buffer;
int wiringPiI2CSetup(int i2c_id)
{
    return i2c_id;
}
void I2C_Write8(int address, int id, int message)
{
    i2c_buffer.push_back(address); 
    i2c_buffer.push_back(id); 
    i2c_buffer.push_back(message);

}