#ifndef UART_READ_HPP
#define UART_READ_HPP
#include <stdint.h>
void UART_run();

struct UART_data
{
    uint8_t *rx_buffer;
    uint8_t data_length;
};

class UART_receiver
{
    private:
        int uart0_filestream;
        uint8_t rx_buffer[33];
    public:
        UART_receiver();
        ~UART_receiver();
        UART_data get_data();

};

#endif //UART_READ_HPP