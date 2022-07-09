#include "gy86_driver.hpp"
#include "i2c_adapter.hpp"
#include "parameters.hpp"
#include <chrono>
#include <thread>

namespace GY_86
{
    using namespace std::this_thread;     // sleep_for, sleep_until
    using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
    using std::chrono::system_clock;


    void MPU6050_User::config(MPU_ConfigTypeDef &config)
    {
        I2C_Write8(this->i2c_id, PWR_MAGT_1_REG, 0x80);
        sleep_for(100ms);
        uint8_t Buffer = (int)config.ClockSource & 0x07; //change the 7th bits of register
        Buffer |= ((int)config.Sleep_Mode_Bit << 6) &0x40; // change only the 7th bit in the register
        I2C_Write8(this->i2c_id, PWR_MAGT_1_REG, Buffer);
        sleep_for(100ms); // should wait 10ms after changeing the clock setting.

        //Set the Digital Low Pass Filter
        Buffer = 0;
        Buffer = (int) config.CONFIG_DLPF & 0x07;
        I2C_Write8(this->i2c_id, CONFIG_REG, Buffer);

        //Select the Gyroscope Full Scale Range
	    Buffer = 0;
	    Buffer = ((int)config.Gyro_Full_Scale << 3) & 0x18;
	    I2C_Write8(this->i2c_id, GYRO_CONFIG_REG, Buffer);

        //Select the Accelerometer Full Scale Range 
	    Buffer = 0; 
	    Buffer = ((int)config.Accel_Full_Scale << 3) & 0x18;
	    I2C_Write8(this->i2c_id, ACCEL_CONFIG_REG, Buffer);

        MPU6050_Set_SMPRT_DIV(config.Sample_Rate_Devider);

	if (config.INTA_ENABLED)
	{
		I2C_Write8(this->i2c_id, INT_ENABLE_REG, 0x1);
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
    	I2C_Write8(this->i2c_id, SMPLRT_DIV_REG, SMPRTvalue);
    }

	static int16_t GyroRW[3];
	//9- Get Accel Raw Data
	void MPU6050_User::MPU6050_Get_Accel_RawData(RawData_Def *rawDef)
	{
		uint8_t i2cBuf[2];
		uint8_t AcceArr[6], GyroArr[6];

		I2C_Read(INT_STATUS_REG, &i2cBuf[1],1);
		if((i2cBuf[1]&&0x01))
		{
			I2C_Read(ACCEL_XOUT_H_REG, AcceArr,6);

			//Accel Raw Data
			rawDef->x = ((AcceArr[0]<<8) + AcceArr[1]); // x-Axis
			rawDef->y = ((AcceArr[2]<<8) + AcceArr[3]); // y-Axis
			rawDef->z = ((AcceArr[4]<<8) + AcceArr[5]); // z-Axis
			//Gyro Raw Data
			I2C_Read(GYRO_XOUT_H_REG, GyroArr,6);
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

    GY86_User::GY86_User(int i2c_id)
    {
        this->i2c_id = wiringPiI2CSetup(i2c_id);
    }
}