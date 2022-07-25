#ifndef GY_86_PARAMETER_HPP
#define GY_86_PARAMETER_HPP

//MPU6050 parameters
constexpr int PWR_MAGT_1_REG    = 0x6B;
constexpr int MPU_6050_ADDR     = 0x68;
constexpr int CONFIG_REG        = 0x1A;
constexpr int GYRO_CONFIG_REG   = 0x1B;
constexpr int ACCEL_CONFIG_REG  = 0x1C;
constexpr int SMPLRT_DIV_REG    = 0x19;
constexpr int INT_ENABLE_REG    = 0x38;
constexpr int INT_STATUS_REG    = 0x3A;
constexpr int ACCEL_XOUT_H_REG	= 0x3B;
constexpr int GYRO_XOUT_H_REG   = 0x43;

//HMC5883L parameters 
constexpr int HMC5883L_ADDR  = 0x1E;

constexpr int HMC5883L_RA_CONFIG_A        = 0x00;
constexpr int HMC5883L_RA_CONFIG_B        = 0x01;
constexpr int HMC5883L_RA_MODE            = 0x02;
constexpr int HMC5883L_RA_DATAX_H         = 0x03;
constexpr int HMC5883L_RA_DATAX_L         = 0x04;
constexpr int HMC5883L_RA_DATAZ_H         = 0x05;
constexpr int HMC5883L_RA_DATAZ_L         = 0x06;
constexpr int HMC5883L_RA_DATAY_H         = 0x07;
constexpr int HMC5883L_RA_DATAY_L         = 0x08;
constexpr int HMC5883L_RA_STATUS          = 0x09;
constexpr int HMC5883L_RA_ID_A            = 0x0A;
constexpr int HMC5883L_RA_ID_B            = 0x0B;
constexpr int HMC5883L_RA_ID_C            = 0x0C;

constexpr int HMC5883L_CRA_AVERAGE_BIT    = 6;
constexpr int HMC5883L_CRA_AVERAGE_LENGTH = 2;
constexpr int HMC5883L_CRA_RATE_BIT       = 4;
constexpr int HMC5883L_CRA_RATE_LENGTH    = 3;
constexpr int HMC5883L_CRA_BIAS_BIT       = 1;
constexpr int HMC5883L_CRA_BIAS_LENGTH    = 2;

constexpr int HMC5883L_AVERAGING_1        = 0x00;
constexpr int HMC5883L_AVERAGING_2        = 0x01;
constexpr int HMC5883L_AVERAGING_4        = 0x02;
constexpr int HMC5883L_AVERAGING_8        = 0x03;

constexpr int HMC5883L_RATE_0P75          = 0x00;
constexpr int HMC5883L_RATE_1P5           = 0x01;
constexpr int HMC5883L_RATE_3             = 0x02;
constexpr int HMC5883L_RATE_7P5           = 0x03;
constexpr int HMC5883L_RATE_15            = 0x04;
constexpr int HMC5883L_RATE_30            = 0x05;
constexpr int HMC5883L_RATE_75            = 0x06;

constexpr int HMC5883L_BIAS_NORMAL        = 0x00;
constexpr int HMC5883L_BIAS_POSITIVE      = 0x01;
constexpr int HMC5883L_BIAS_NEGATIVE      = 0x02;

constexpr int HMC5883L_CRB_GAIN_BIT       = 7;
constexpr int HMC5883L_CRB_GAIN_LENGTH    = 3;

constexpr int HMC5883L_GAIN_1370          = 0x00;
constexpr int HMC5883L_GAIN_1090          = 0x01;
constexpr int HMC5883L_GAIN_820           = 0x02;
constexpr int HMC5883L_GAIN_660           = 0x03;
constexpr int HMC5883L_GAIN_440           = 0x04;
constexpr int HMC5883L_GAIN_390           = 0x05;
constexpr int HMC5883L_GAIN_330           = 0x06;
constexpr int HMC5883L_GAIN_220           = 0x07;

constexpr int HMC5883L_MODEREG_BIT        = 1;
constexpr int HMC5883L_MODEREG_LENGTH     = 2;

constexpr int HMC5883L_MODE_CONTINUOUS    = 0x00;
constexpr int HMC5883L_MODE_SINGLE        = 0x01;
constexpr int HMC5883L_MODE_IDLE          = 0x02;

constexpr int HMC5883L_STATUS_LOCK_BIT    = 1;
constexpr int HMC5883L_STATUS_READY_BIT   = 0;


constexpr double PI = 3.14159;




#endif