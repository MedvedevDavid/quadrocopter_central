#include <iostream>
#include "parameters.hpp"
#include <unistd.h>
#include <wiringPi.h>
#include "sensor_master.hpp"
#include "UART_read.hpp"
#include "controll_master.hpp"
#include <thread>
#include "PID.hpp"
#include "motor_controller.hpp"
//PWM
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>



using namespace sensormaster;
void MPUDataInterrupt();
void RemoteControllerRead();
void PIDController();
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
    std::thread thread_object(RemoteControllerRead);


    while(1)
    {
    }
}

// Our interrupt routine
void MPUDataInterrupt()
{
    GyData->MPU_get_data();
    //TODO: Magnetometer filedescriptor is not correct
    //GyData->magnetometer_sensor_data_processing();
}

void RemoteControllerRead()
{
    UART_receiver UART_controll_master;
    ControllMessageManeger UART_data_decoder;
    while(1)
    {
        UART_data raw_control_data =  UART_controll_master.get_data();
        ControllSignal_data_type processed_control_data =  UART_data_decoder.decode_new_message(raw_control_data.rx_buffer, raw_control_data.data_length);
    }

    //std::cout << "acceleration" << processed_control_data.acceleration << std::endl;
    //std::cout << "angle_yaw" << processed_control_data.angle_yaw << std::endl;
    //std::cout << "angle_roll" << processed_control_data.angle_roll << std::endl;
    //std::cout << "angle_pitch" << processed_control_data.angle_pitch << std::endl;
    //std::cout << "state" << processed_control_data.state << std::endl;
}

void PIDController()
{
    struct timeval time_val;
    gettimeofday(&time_val, NULL);
    ControllSignal_data_type decoded_UART_message_from_queue;
    PID_controller PID_pitch(PITCH_P,PITCH_I,PITCH_D, ((float) time_val.tv_usec)/1000);
    PID_controller PID_roll(ROLL_P,ROLL_I,ROLL_D, ((float) time_val.tv_usec)/1000);
    PID_controller_yaw PID_yaw(YAW_P,YAW_I,YAW_D, ((float) time_val.tv_usec)/1000);
    float sampple_time_buffer;
    sensor_data_type servo_angle_from_queue;
    controll_data_type controll_Data_for_queue;
    /* Infinite loop */
    while (1)
    {


      if (sampple_time_buffer != servo_angle_from_queue.sampple_time)
      {

        controll_Data_for_queue.angle_pitch   = PID_pitch.get_PID_controll_signal(decoded_UART_message_from_queue.angle_pitch, servo_angle_from_queue.angle_pitch, servo_angle_from_queue.sampple_time, decoded_UART_message_from_queue.state, decoded_UART_message_from_queue.acceleration);
        controll_Data_for_queue.angle_roll    = PID_roll.get_PID_controll_signal(decoded_UART_message_from_queue.angle_roll, servo_angle_from_queue.angle_roll, servo_angle_from_queue.sampple_time, decoded_UART_message_from_queue.state, decoded_UART_message_from_queue.acceleration);
        controll_Data_for_queue.angle_yaw     = PID_yaw.get_PID_controll_signal(decoded_UART_message_from_queue.angle_yaw, servo_angle_from_queue.angle_yaw, servo_angle_from_queue.sampple_time, decoded_UART_message_from_queue.state, decoded_UART_message_from_queue.acceleration);
      }
      sampple_time_buffer = servo_angle_from_queue.sampple_time;
      controll_Data_for_queue.acceleration = decoded_UART_message_from_queue.acceleration;


    }
}

void signal_callback_handler(int signum);
FILE *fp;

void MotorController()
{
    fp = fopen("/dev/pi-blaster", "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(0);
     }
    signal(SIGINT, signal_callback_handler);

    fprintf(fp, "%i=%f\n", 4,0);
    fflush(fp);
    fprintf(fp, "%i=%f\n", 17,0);
    fflush(fp); 
    fprintf(fp, "%i=%f\n", 18,0);
    fflush(fp); 
    fprintf(fp, "%i=%f\n", 22,0);
    fflush(fp); 

    motor_controller::Motor_controller motor_calculation_master;

    while (1)
    {
        controll_data_type controll_Date_from_queue;

        bldc_driver_data_type bldc_driver = motor_calculation_master.update_motor_driver(controll_Date_from_queue);

        fprintf(fp, "%i=%f\n", 4,MOTOR_IDDLE_TICK + bldc_driver.motor_1);
        fflush(fp);
        fprintf(fp, "%i=%f\n", 17,MOTOR_IDDLE_TICK + bldc_driver.motor_2);
        fflush(fp); 
        fprintf(fp, "%i=%f\n", 18,MOTOR_IDDLE_TICK + bldc_driver.motor_3);
        fflush(fp); 
        fprintf(fp, "%i=%f\n", 22,MOTOR_IDDLE_TICK + bldc_driver.motor_4);
        fflush(fp); 
    }


}

//https://github.com/sarfata/pi-blaster
//https://ozzmaker.com/software-pwm-on-a-raspberry-pi/
void signal_callback_handler(int signum) {
    fprintf(fp, "%i=%f\n", 4,0.0);
    fflush(fp);
    fprintf(fp, "%i=%f\n", 17,0.0);
    fflush(fp); 
    fprintf(fp, "%i=%f\n", 18,0.0);
    fflush(fp); 
    fprintf(fp, "%i=%f\n", 22,0.0);
    fflush(fp); 
    std::cout << "Session cloosed" << std::endl;
   // Terminate program
   exit(0);
}