#include "gtest/gtest.h"
#include "gy86_driver.hpp"
#include "i2c_adapter.hpp"
#include "gmock/gmock.h"
#include "parameters.hpp"
using namespace GY_86;


TEST(TC_I2C_Driver, testcases)
{
    MPU_ConfigTypeDef mpu_configuration;

    //Configure accelerometer and GYRO parameters
    mpu_configuration.Accel_Full_Scale = accel_FullScale_ENUM::AFS_SEL_4g;
    mpu_configuration.ClockSource = PM_CLKSEL_ENUM::Internal_8MHz;
    mpu_configuration.CONFIG_DLPF = DLPF_CFG_ENUM::DLPF_184A_188G_Hz;
    mpu_configuration.Gyro_Full_Scale = gyro_FullScale_ENUM::FS_SEL_500;
    mpu_configuration.Sleep_Mode_Bit = 0;
    mpu_configuration.INTA_ENABLED = 1;
    mpu_configuration.Sample_Rate_Devider = 4;

    MPU6050_User mpu6050(MPU_6050_ADDR);
    mpu6050.config(mpu_configuration);
    ASSERT_THAT(i2c_buffer, testing::ElementsAre(MPU_6050_ADDR, PWR_MAGT_1_REG, 0x80, 
    MPU_6050_ADDR, PWR_MAGT_1_REG, 0x00, 
    MPU_6050_ADDR, CONFIG_REG, 0x01, 
    MPU_6050_ADDR, GYRO_CONFIG_REG, 0x08, 
    MPU_6050_ADDR, ACCEL_CONFIG_REG, 0x08,
    MPU_6050_ADDR, SMPLRT_DIV_REG, 0x04,
    MPU_6050_ADDR, INT_ENABLE_REG, 0x01));

};