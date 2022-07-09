#include "i2c_adapter.hpp"

std::vector<int> i2c_buffer;

void I2C_Write8(int id, int message)
{
    i2c_buffer.push_back(address); 
    i2c_buffer.push_back(id); 
    i2c_buffer.push_back(message);

}

int i2c_sender_buffer[] = {1,0,1,0,2,0,3,0,4,0,5,0,6,1,0,1,0,2,0,3,0,4,0,5,0,6}; 
int data_sent_count = 0;
void I2C_Read(uint8_t ADDR, uint8_t *i2cBif, uint8_t NofData)
{
        for(int i=0;i<NofData; i++)
        {
            i2cBif[i] =i2c_sender_buffer[data_sent_count];
            data_sent_count ++;
        }
}