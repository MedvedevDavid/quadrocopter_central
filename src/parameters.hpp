#ifndef PARAMETER_HPP
#define PARAMETER_GPP
//PID parameters
constexpr float YAW_P = 2;
constexpr float YAW_I = 0;
constexpr float YAW_D = 0;

constexpr float YAW_SCALING_FACTOR = 0.00001;
constexpr int16_t MOTOR_IDDLE_TICK              = 1000;

constexpr float ROLL_P = 0.5;
constexpr float ROLL_I = 0;
constexpr float ROLL_D = 0.4;

constexpr float PITCH_P = 0.5;
constexpr float PITCH_I = 0;
constexpr float PITCH_D = 0.4;
constexpr float MAXIMUM_ACCELERATION            = 130;
constexpr float PID_INTEGRATION_START = MAXIMUM_ACCELERATION/2;

constexpr float MAX_INTEGRATOR_BUFFER           = 200;

#endif