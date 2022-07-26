#ifndef __REMOTCONTROLL_PAREMETERS_HPP
#define __REMOTCONTROLL_PAREMETERS_HPP

constexpr float MAXIMUM_ACCELERATION            = 130;

//IBUS Parameters
constexpr int16_t IBUS_LENGTH				        = 0x20;   // 32 bytes
constexpr int16_t IBUS_COMMAND40			        = 0x40;	// Command to set servo or motor speed is always 0x40
constexpr int16_t IBUS_MAX_CHANNLES		            = 14;

constexpr uint16_t STICK_VALUE_AT_MIDDLE	        = 0x5DC;
constexpr uint16_t STICK_VALUE_AT_MINIMUM	        = 0x3EA;
constexpr uint16_t STICK_VALUE_FROM_MIN_TO_MAX	    = 0x3DB;
constexpr uint16_t STICK_VALUE_FROM_MIN_TO_MAX_HALF	= 0x1F2;

// Controller Parameters
constexpr float MAXIMUM_CONTROLL_ANGLE              = 60;

//UART Logger parameters
constexpr uint16_t MAXIMUM_BUFFER_SIZE	            = 100;
constexpr uint16_t LOGGING_MULTIPLIER	            = 100;

#endif //__REMOTCONTROLL_PAREMETERS_HPP