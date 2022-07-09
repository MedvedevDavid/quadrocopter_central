#ifndef I2C_ADAPTER_HPP
#define I2C_ADAPTER_HPP
#include <vector>
#include <stdint.h>

extern std::vector<int> i2c_buffer;

void I2C_Write8(int, int);
void I2C_Read(uint8_t, uint8_t *, uint8_t );

#endif
