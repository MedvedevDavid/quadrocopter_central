#ifndef I2C_ADAPTER_HPP
#define I2C_ADAPTER_HPP
#include <stdint.h>

class I2C_driver{
    private:
        int file_i2c;
        int adapter_nr = 2;
        char filename[20];
        int addr = 0x5a;          //<<<<<The I2C address of the slave
        uint8_t buffer[60];
        int length;

    public:
        I2C_driver(int);
        void I2C_Write8(int, int);
        void I2C_Read(uint8_t, uint8_t *, uint8_t );
};
#endif