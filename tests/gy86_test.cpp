#include "gtest/gtest.h"
#include "gy86_driver.hpp"
#include "i2c_adapter.hpp"
#include "gmock/gmock.h"
#include "gy86_parameters.hpp"
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

    MPU6050_User mpu6050();
    mpu6050.config(mpu_configuration);
    ASSERT_THAT(i2c_buffer, testing::ElementsAre(MPU_6050_ADDR, PWR_MAGT_1_REG, 0x80, 
    MPU_6050_ADDR, PWR_MAGT_1_REG, 0x00, 
    MPU_6050_ADDR, CONFIG_REG, 0x01, 
    MPU_6050_ADDR, GYRO_CONFIG_REG, 0x08, 
    MPU_6050_ADDR, ACCEL_CONFIG_REG, 0x08,
    MPU_6050_ADDR, SMPLRT_DIV_REG, 0x04,
    MPU_6050_ADDR, INT_ENABLE_REG, 0x01));

    RawData_Def rawDef;
    mpu6050.MPU6050_Get_Accel_RawData(&rawDef);
    ASSERT_THAT(rawDef.x, 1);
    ASSERT_THAT(rawDef.y, 2);
    ASSERT_THAT(rawDef.z, 3);

    ScaledData_Def scaledDef;
    mpu6050.MPU6050_Get_Accel_Scale(&scaledDef);
    ASSERT_THAT(scaledDef.x, 1*(4000.0f/32768.0f));
    ASSERT_THAT(scaledDef.y, 2*(4000.0f/32768.0f));
    ASSERT_THAT(scaledDef.z, 3*(4000.0f/32768.0f));


    RawData_Def myGyroRaw;
	mpu6050.MPU6050_Get_Gyro_RawData(&myGyroRaw);
    ASSERT_THAT(myGyroRaw.x, 4);
    ASSERT_THAT(myGyroRaw.y, 5);
    ASSERT_THAT(myGyroRaw.z, 6);


    mpu6050.MPU6050_Get_Gyro_Scale(&scaledDef);
    ASSERT_THAT(scaledDef.x, 4*500.0f/32768.0f);
    ASSERT_THAT(scaledDef.y, 5*500.0f/32768.0f);
    ASSERT_THAT(scaledDef.z, 6*500.0f/32768.0f);


};