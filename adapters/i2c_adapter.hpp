#include <stdint.h>


void I2C_Write8(int, int, int);
int wiringPiI2CSetup(int);
void I2C_Read(uint8_t, uint8_t *, uint8_t );