#ifndef GY86_DRIVER_HPP
#define GY86_DRIVER_HPP
 #include <stdint.h>
 
namespace GY_86
{
    //2- Clock Source ENUM
    enum class PM_CLKSEL_ENUM
    {
    	Internal_8MHz 	= 0x00,
    	X_Axis_Ref			= 0x01,
    	Y_Axis_Ref			= 0x02,
    	Z_Axis_Ref			= 0x03,
    	Ext_32_768KHz		= 0x04,
    	Ext_19_2MHz			= 0x05,
    	TIM_GENT_INREST	= 0x07
    };
    //3- Gyro Full Scale Range ENUM (deg/sec)
    enum class gyro_FullScale_ENUM
    {
    	FS_SEL_250 	= 0x00,
    	FS_SEL_500 	= 0x01,
    	FS_SEL_1000 = 0x02,
    	FS_SEL_2000	= 0x03
    };
    //4- Accelerometer Full Scale Range ENUM (1g = 9.81m/s2)
    enum class accel_FullScale_ENUM
    {
    	AFS_SEL_2g	= 0x00,
    	AFS_SEL_4g,
    	AFS_SEL_8g,
    	AFS_SEL_16g
    };
    //5- Digital Low Pass Filter ENUM
    enum class DLPF_CFG_ENUM
    {
    	DLPF_260A_256G_Hz = 0x00,
    	DLPF_184A_188G_Hz = 0x01,
    	DLPF_94A_98G_Hz 	= 0x02,
    	DLPF_44A_42G_Hz 	= 0x03,
    	DLPF_21A_20G_Hz 	= 0x04,
    	DLPF_10_Hz 				= 0x05,
    	DLPF_5_Hz 				= 0x06
    };
    //6- e external Frame Synchronization ENUM
    enum class EXT_SYNC_SET_ENUM
    {
    	input_Disable = 0x00,
    	TEMP_OUT_L		= 0x01,
    	GYRO_XOUT_L		= 0x02,
    	GYRO_YOUT_L		= 0x03,
    	GYRO_ZOUT_L		= 0x04,
    	ACCEL_XOUT_L	= 0x05,
    	ACCEL_YOUT_L	= 0x06,
    	ACCEL_ZOUT_L	= 0x07
    };

    typedef struct
    {
        PM_CLKSEL_ENUM          ClockSource;
        gyro_FullScale_ENUM     Gyro_Full_Scale;
        accel_FullScale_ENUM    Accel_Full_Scale;
        DLPF_CFG_ENUM           CONFIG_DLPF;
        bool 	                Sleep_Mode_Bit; 
        bool	                INTA_ENABLED;
        uint8_t                 Sample_Rate_Devider;
    }MPU_ConfigTypeDef;

    class MPU6050
    {
        private:
            int i2c_id;
            void MPU6050_Set_SMPRT_DIV(uint8_t);
            float accelScalingFactor;
            float gyroScalingFactor;
        public: 
            MPU6050(int);
            void config(MPU_ConfigTypeDef &config);
    };


}


#endif