
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include "i2c_adapter.hpp"
#include <iostream>


I2C_driver::I2C_driver(int i2c_addr)
{
    addr = i2c_addr;
	//----- OPEN THE I2C BUS -----
	char *filename = (char*)"/dev/i2c-1";
	if ((file_i2c = open(filename, O_RDWR)) < 0)
	{
		//ERROR HANDLING: you can check errno to see what went wrong
		std::cout << "Failed to open the i2c bus\n";
		return;
	}
	
	if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
	{
		std::cout <<"Failed to acquire bus access and/or talk to slave.\n";
		//ERROR HANDLING; you can check errno to see what went wrong
		return;
	}
    std::cout <<"I2C succesfully opened\n";
}

void I2C_driver::I2C_Write8(int id, int message)
{

	//----- WRITE BYTES -----
	buffer[0] = id;
	buffer[1] = message;
	length = 2;			//<<< Number of bytes to write

	if (write(file_i2c, buffer, length) != length)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		/* ERROR HANDLING: i2c transaction failed */
		std::cout <<"Failed to write to the i2c bus.\n";
	}
}

void I2C_driver::I2C_Read(uint8_t ADDR, uint8_t *i2c_read_buff, uint8_t NofData)
{

	uint8_t i2cBuf[2];
	i2cBuf[0] = ADDR;
	length = 2;			//<<< Number of bytes to write
	//----- WRITE COMMAND -----
	if (write(file_i2c, i2cBuf, length) != length)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		/* ERROR HANDLING: i2c transaction failed */
		std::cout << "Failed to write to the i2c bus.\n";
	}
    //----- READ BYTES -----
	length = NofData;			//<<< Number of bytes to read
	if (read(file_i2c, i2c_read_buff, length) != length)		//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		//ERROR HANDLING: i2c transaction failed
		std::cout <<"Failed to read from the i2c bus.\n";
	}

}
