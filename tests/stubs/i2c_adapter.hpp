#ifndef I2C_ADAPTER_HPP
#define I2C_ADAPTER_HPP
#include <vector>

extern std::vector<int> i2c_buffer;

void I2C_Write8(int, int, int);
int wiringPiI2CSetup(int);


#endif
