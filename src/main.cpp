#include <iostream>
#include "parameters.hpp"
#include <unistd.h>
#include <wiringPi.h>
#include "sensor_master.hpp"

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

    while(1)
    {
        	

        sleep(0.5);
    }
}

// Our interrupt routine
void MPUDataInterrupt()
{
    GyData->MPU_get_data();
}