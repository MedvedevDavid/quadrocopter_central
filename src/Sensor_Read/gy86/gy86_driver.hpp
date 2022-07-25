#ifndef GY86_DRIVER_HPP
#define GY86_DRIVER_HPP
#include <stdint.h>
#include "i2c_adapter.hpp"
#include "gy86_parameters.hpp"

namespace GY_86
{
    // Clock Source ENUM
    enum class PM_CLKSEL_ENUM
    {
        Internal_8MHz = 0x00,
        X_Axis_Ref = 0x01,
        Y_Axis_Ref = 0x02,
        Z_Axis_Ref = 0x03,
        Ext_32_768KHz = 0x04,
        Ext_19_2MHz = 0x05,
        TIM_GENT_INREST = 0x07
    };
    // Gyro Full Scale Range ENUM (deg/sec)
    enum class gyro_FullScale_ENUM
    {
        FS_SEL_250 = 0x00,
        FS_SEL_500 = 0x01,
        FS_SEL_1000 = 0x02,
        FS_SEL_2000 = 0x03
    };
    // Accelerometer Full Scale Range ENUM (1g = 9.81m/s2)
    enum class accel_FullScale_ENUM
    {
        AFS_SEL_2g = 0x00,
        AFS_SEL_4g,
        AFS_SEL_8g,
        AFS_SEL_16g
    };
    // Digital Low Pass Filter ENUM
    enum class DLPF_CFG_ENUM
    {
        DLPF_260A_256G_Hz = 0x00,
        DLPF_184A_188G_Hz = 0x01,
        DLPF_94A_98G_Hz = 0x02,
        DLPF_44A_42G_Hz = 0x03,
        DLPF_21A_20G_Hz = 0x04,
        DLPF_10_Hz = 0x05,
        DLPF_5_Hz = 0x06
    };
    // External Frame Synchronization ENUM
    enum class EXT_SYNC_SET_ENUM
    {
        input_Disable = 0x00,
        TEMP_OUT_L = 0x01,
        GYRO_XOUT_L = 0x02,
        GYRO_YOUT_L = 0x03,
        GYRO_ZOUT_L = 0x04,
        ACCEL_XOUT_L = 0x05,
        ACCEL_YOUT_L = 0x06,
        ACCEL_ZOUT_L = 0x07
    };

    typedef struct
    {
        PM_CLKSEL_ENUM ClockSource;
        gyro_FullScale_ENUM Gyro_Full_Scale;
        accel_FullScale_ENUM Accel_Full_Scale;
        DLPF_CFG_ENUM CONFIG_DLPF;
        bool Sleep_Mode_Bit;
        bool INTA_ENABLED;
        uint8_t Sample_Rate_Devider;
    } MPU_ConfigTypeDef;


    // Raw data typedef
    typedef struct
    {
    	int16_t x;
    	int16_t y;
    	int16_t z;
    }RawData_Def;

    //Scaled data typedef
    typedef struct
    {
    	float x;
    	float y;
    	float z;
    }ScaledData_Def;

    struct raw_angle{
        float x_angle, y_angle;
    };

    struct magnet_ret{
        float x, y, z;
    };

    class GY86_User
    {
        protected:
            int i2c_id;
            I2C_driver *I2C_Port;
        public:
            GY86_User(int);
    };

    class MPU6050_User:GY86_User
    {
        private:
            void MPU6050_Set_SMPRT_DIV(uint8_t);
            float accelScalingFactor;
            float gyroScalingFactor;
            void MPU6050_Get_Accel_RawData(RawData_Def *rawDef);
            void MPU6050_Get_Gyro_RawData(RawData_Def *rawDef);
            void MPU6050_Get_Accel_Scale(ScaledData_Def *scaledDef);

        public:
            MPU6050_User():GY86_User(MPU_6050_ADDR){};
            void config(MPU_ConfigTypeDef &config);
            raw_angle get_xy_accel_angles(void);
            void MPU6050_Get_Gyro_Scale(ScaledData_Def *scaledDef);
    };
    class HMC5883L_User:GY86_User
    {
        private:
            void HMC5883L_setGain(uint8_t gain);
            void HMC5883L_setMode(uint8_t newMode);
            uint8_t buffer[6];
            uint8_t mode;

        public:
            HMC5883L_User():GY86_User(HMC5883L_ADDR){};
            magnet_ret get_magnet_xyz(void);
            void HMC5883L_initialize(void);
            bool HMC5883L_getReadyStatus();
    };

}

#endif