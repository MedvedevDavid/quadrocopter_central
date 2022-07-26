#include <iostream>
#include "parameters.hpp"
#include <unistd.h>
#include <wiringPi.h>
#include "sensor_master.hpp"
#include "UART_read.hpp"
#include "controll_master.hpp"

using namespace sensormaster;
void MPUDataInterrupt();	// Function prototype
Sensor_Data *GyData;
int main()
{
    if(wiringPiSetup()<0)
    {
        std::cout << "Init Failed" << std::endl;
    }
    pinMode(24, INPUT);

   GyData = new Sensor_Data();

    // Cause an interrupt when data recieved
     
    if(wiringPiISR (24, INT_EDGE_RISING, &MPUDataInterrupt)<0)
    {
        std::cout << "ISR Failed" << std::endl;
    }

    UART_receiver UART_controll_master;
    ControllMessageManeger UART_data_decoder;
    while(1)
    {

        UART_data raw_control_data =  UART_controll_master.get_data();
        ControllSignal_data_type processed_control_data =  UART_data_decoder.decode_new_message(raw_control_data.rx_buffer, raw_control_data.data_length);
        std::cout << "acceleration" << processed_control_data.acceleration << std::endl;
        std::cout << "angle_yaw" << processed_control_data.angle_yaw << std::endl;
        std::cout << "angle_roll" << processed_control_data.angle_roll << std::endl;
        std::cout << "angle_pitch" << processed_control_data.angle_pitch << std::endl;
        //std::cout << "state" << processed_control_data.state << std::endl;

        sleep(0.5);
    }
}

// Our interrupt routine
void MPUDataInterrupt()
{
    //GyData->MPU_get_data();
    //GyData->magnetometer_sensor_data_processing();
}