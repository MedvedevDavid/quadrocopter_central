#include "UART_read.hpp"

#include <iostream>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART

UART_receiver::UART_receiver()
{
	uart0_filestream = -1;

	uart0_filestream = open("/dev/ttyS0", O_RDONLY | O_NOCTTY);
	if (uart0_filestream == -1)
	{
		//ERROR - CAN'T OPEN SERIAL PORT
		std::cout << "Error - Unable to open UART.  Ensure it is not in use by another application\n";
	}
	
	struct termios options;
	tcgetattr(uart0_filestream, &options);
	//options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	//options.c_cflag &= ~CSIZE;
	//options.c_cflag &= ~PARENB;
	//options.c_cflag |= CSTOPB;
	//options.c_cflag &= ~CRTSCTS;
	//options.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	//options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	//options.c_oflag &= ~OPOST;
    //options.c_cc[VMIN] = 1;
	//tcsetattr(uart0_filestream, TCSANOW, &options);


	options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(uart0_filestream, TCIFLUSH);
	tcsetattr(uart0_filestream, TCSANOW, &options);

}
UART_data UART_receiver::get_data()
{
	uint8_t rx_sample;
	UART_data ret_val;
	if (uart0_filestream != -1)
	{
		int cycle_count;
		for( cycle_count = 0; cycle_count<32; )
		{
			if (read(uart0_filestream, (void*)&rx_sample, 1) == 1)
			{
				if (cycle_count == 0 || cycle_count == 1)
				{
					if (cycle_count == 0 && (int)rx_sample == 0x20)
					{
						rx_buffer[cycle_count] = rx_sample;
						cycle_count++;
					}
					else if (cycle_count == 1 && (int)rx_sample == 0x40)
					{
						rx_buffer[cycle_count] = rx_sample;
						cycle_count++;
					}

				}
				else
				{
					rx_buffer[cycle_count] = rx_sample;
					cycle_count++;
				}
			}
			else
			{
				break;
				//Failure
			}

			
		}
		ret_val.rx_buffer = rx_buffer;
		ret_val.data_length = cycle_count;
	}
	else
	{
		std::cout << "Error - Unable to open UART.\n";
	}
	return (ret_val);
}
UART_receiver::~UART_receiver()
{
	close(uart0_filestream);
}