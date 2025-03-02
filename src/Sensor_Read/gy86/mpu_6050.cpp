#include "mpu_6050.hpp"
#include "i2c_adapter.hpp"
#include <chrono>
#include <thread>
#include <cmath>
#include <iostream>

namespace GY_86
{
    using namespace std::this_thread;     // sleep_for, sleep_until
    using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
    using std::chrono::system_clock;

    void MPU6050_User::config(MPU_ConfigTypeDef &config)
    {
       	I2C_Port->I2C_Write8(PWR_MAGT_1_REG, 0x80);
        sleep_for(100ms);
        uint8_t Buffer = (int)config.ClockSource & 0x07; //change the 7th bits of register
        Buffer |= ((int)config.Sleep_Mode_Bit << 6) &0x40; // change only the 7th bit in the register
        I2C_Port->I2C_Write8(PWR_MAGT_1_REG, Buffer);
        sleep_for(100ms); // should wait 10ms after changeing the clock setting.

        //Set the Digital Low Pass Filter
        Buffer = 0;
        Buffer = (int) config.CONFIG_DLPF & 0x07;
        I2C_Port->I2C_Write8(CONFIG_REG, Buffer);

        //Select the Gyroscope Full Scale Range
	    Buffer = 0;
	    Buffer = ((int)config.Gyro_Full_Scale << 3) & 0x18;
	    I2C_Port->I2C_Write8(GYRO_CONFIG_REG, Buffer);

        //Select the Accelerometer Full Scale Range 
	    Buffer = 0; 
	    Buffer = ((int)config.Accel_Full_Scale << 3) & 0x18;
	    I2C_Port->I2C_Write8(ACCEL_CONFIG_REG, Buffer);

        MPU6050_Set_SMPRT_DIV(config.Sample_Rate_Devider);

	if (config.INTA_ENABLED)
	{
		I2C_Port->I2C_Write8(INT_ENABLE_REG, 0x1);
	}
	


	//Accelerometer Scaling Factor, Set the Accelerometer and Gyroscope Scaling Factor
	switch (config.Accel_Full_Scale)
	{
		case accel_FullScale_ENUM::AFS_SEL_2g:
			accelScalingFactor = (2000.0f/32768.0f);
			break;
		
		case accel_FullScale_ENUM::AFS_SEL_4g:
			accelScalingFactor = (4000.0f/32768.0f);
				break;
		
		case accel_FullScale_ENUM::AFS_SEL_8g:
			accelScalingFactor = (8000.0f/32768.0f);
			break;
		
		case accel_FullScale_ENUM::AFS_SEL_16g:
			accelScalingFactor = (16000.0f/32768.0f);
			break;
		
		default:
			break;
	}
	//Gyroscope Scaling Factor 
	    switch (config.Gyro_Full_Scale)
	    {
	    	case gyro_FullScale_ENUM::FS_SEL_250:
	    		gyroScalingFactor = 250.0f/32768.0f;
	    		break;
    
	    	case gyro_FullScale_ENUM::FS_SEL_500:
	    			gyroScalingFactor = 500.0f/32768.0f;
	    			break;
    
	    	case gyro_FullScale_ENUM::FS_SEL_1000:
	    		gyroScalingFactor = 1000.0f/32768.0f;
	    		break;
    
	    	case gyro_FullScale_ENUM::FS_SEL_2000:
	    		gyroScalingFactor = 2000.0f/32768.0f;
	    		break;
    
	    	default:
	    		break;
	    }

    }
    //6- Set Sample Rate Divider
    void MPU6050_User::MPU6050_Set_SMPRT_DIV(uint8_t SMPRTvalue)
    {
    	I2C_Port->I2C_Write8(SMPLRT_DIV_REG, SMPRTvalue);
    }

	static int16_t GyroRW[3];
	//9- Get Accel Raw Data
	void MPU6050_User::MPU6050_Get_Accel_RawData(RawData_Def *rawDef)
	{
		uint8_t i2cBuf[2];
		uint8_t AcceArr[6], GyroArr[6];

		I2C_Port->I2C_Read(INT_STATUS_REG, &i2cBuf[1],1);
		if((i2cBuf[1]&&0x01))
		{
			I2C_Port->I2C_Read(ACCEL_XOUT_H_REG, AcceArr,6);

			//Accel Raw Data
			rawDef->x = ((AcceArr[0]<<8) + AcceArr[1]); // x-Axis
			rawDef->y = ((AcceArr[2]<<8) + AcceArr[3]); // y-Axis
			rawDef->z = ((AcceArr[4]<<8) + AcceArr[5]); // z-Axis
			//Gyro Raw Data
			I2C_Port->I2C_Read(GYRO_XOUT_H_REG, GyroArr,6);
			GyroRW[0] = ((GyroArr[0]<<8) + GyroArr[1]);
			GyroRW[1] = (GyroArr[2]<<8) + GyroArr[3];
			GyroRW[2] = ((GyroArr[4]<<8) + GyroArr[5]);
		}
	}
	//10- Get Accel scaled data (g unit of gravity, 1g = 9.81m/s2)
	void MPU6050_User::MPU6050_Get_Accel_Scale(ScaledData_Def *scaledDef)
	{

		RawData_Def AccelRData;
		MPU6050_Get_Accel_RawData(&AccelRData);
		//Accel Scale data 
		scaledDef->x = ((AccelRData.x+0.0f)*accelScalingFactor);
		scaledDef->y = ((AccelRData.y+0.0f)*accelScalingFactor);
		scaledDef->z = ((AccelRData.z+0.0f)*accelScalingFactor);
	}

	//12- Get Gyro Raw Data
	void MPU6050_User::MPU6050_Get_Gyro_RawData(RawData_Def *rawDef)
	{

		//Accel Raw Data
		rawDef->x = GyroRW[0];
		rawDef->y = GyroRW[1];
		rawDef->z = GyroRW[2];

	}

	//13- Get Gyro scaled data
	void MPU6050_User::MPU6050_Get_Gyro_Scale(ScaledData_Def *scaledDef)
	{
		RawData_Def myGyroRaw;
		MPU6050_Get_Gyro_RawData(&myGyroRaw);
		//Gyro Scale data 
		scaledDef->x = (myGyroRaw.x)*gyroScalingFactor; // x-Axis
		scaledDef->y = (myGyroRaw.y)*gyroScalingFactor; // y-Axis
		scaledDef->z = (myGyroRaw.z)*gyroScalingFactor; // z-Axis
	}
	void MPU6050_User::Get_Accel_Scale(ScaledData_Def *my_accel_scaled)
    {
        MPU6050_Get_Accel_Scale(my_accel_scaled);
		// check for if all the values are numbers
		if ((my_accel_scaled->x = my_accel_scaled->x) and (my_accel_scaled->y = my_accel_scaled->y) and (my_accel_scaled->z = my_accel_scaled->z))
		{
			this->my_accel_scaled = *my_accel_scaled;
		}
        
    }

	void MPU6050_User::Get_Gyro_Scale(ScaledData_Def *my_gyro_scaled)
    {
        MPU6050_Get_Gyro_Scale(my_gyro_scaled);
    }

 	raw_angle MPU6050_User::get_xy_accel_angles(void)
    {
        raw_angle ret_Val;
        // Using x y and z from accelerometer, calculate x and y angles
        float  accel_angle_x, accel_angle_y, result, x_val, y_val, z_val;
        double x2, y2, z2; 

        x_val= my_accel_scaled.x;
        y_val= my_accel_scaled.y;
        z_val= my_accel_scaled.z;
        // Work out the squares
        x2 = (double)(x_val*x_val);
        y2 = (double)(y_val*y_val);
        z2 = (double)(z_val*z_val);

        //X Axis
        result=sqrt(y2+z2);
        result=x_val/result;
        accel_angle_x = atan(result);

        //Y Axis
        result=sqrt(x2+z2);
        result=y_val/result;
        accel_angle_y = atan(result);
        ret_Val.x_angle=accel_angle_x*180/PI;
        ret_Val.y_angle=accel_angle_y*180/PI;

        return(ret_Val);
    }
}