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

#endif