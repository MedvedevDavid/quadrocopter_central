#include "hmc_5883l.hpp"
#include <chrono>
#include <thread>
#include <cmath>
#include "i2c_adapter.hpp"

namespace GY_86
{
    // MAGNETOMETER
	magnet_ret HMC5883L_User::get_magnet_xyz()
	{
			magnet_ret ret_Val;
		    I2C_Port->I2C_Read(HMC5883L_RA_DATAX_H, buffer, 6);
    		if (mode == HMC5883L_MODE_SINGLE) I2C_Port->I2C_Write8(HMC5883L_RA_MODE, HMC5883L_MODE_SINGLE << (HMC5883L_MODEREG_BIT - HMC5883L_MODEREG_LENGTH + 1));
    		ret_Val.x = (((int16_t)buffer[0]) << 8) | buffer[1];
    		ret_Val.y = (((int16_t)buffer[4]) << 8) | buffer[5];
    		ret_Val.z = (((int16_t)buffer[2]) << 8) | buffer[3];
			return(ret_Val);
	}
    void HMC5883L_User::HMC5883L_initialize()
	{
		I2C_Port->I2C_Write8(HMC5883L_RA_CONFIG_A, 
        (HMC5883L_AVERAGING_8 << (HMC5883L_CRA_AVERAGE_BIT - HMC5883L_CRA_AVERAGE_LENGTH + 1)) |
        (HMC5883L_RATE_15     << (HMC5883L_CRA_RATE_BIT - HMC5883L_CRA_RATE_LENGTH + 1)) |
        (HMC5883L_BIAS_NORMAL << (HMC5883L_CRA_BIAS_BIT - HMC5883L_CRA_BIAS_LENGTH + 1)));
		
		// write CONFIG_B register
   		HMC5883L_setGain(HMC5883L_GAIN_1090);

   		// write MODE register
   		HMC5883L_setMode(HMC5883L_MODE_SINGLE);
	}

	/** Set magnetic field gain value.
	 * @param gain New magnetic field gain value
	 * @see getGain()
	 * @see HMC5883L_RA_CONFIG_B
	 * @see HMC5883L_CRB_GAIN_BIT
	 * @see HMC5883L_CRB_GAIN_LENGTH
	 */
	void HMC5883L_User::HMC5883L_setGain(uint8_t gain) {
	    // use this method to guarantee that bits 4-0 are set to zero, which is a
	    // requirement specified in the datasheet; it's actually more efficient than
	    // using the I2Cdev.writeBits method
	    I2C_Port->I2C_Write8(HMC5883L_RA_CONFIG_B, gain << (HMC5883L_CRB_GAIN_BIT - HMC5883L_CRB_GAIN_LENGTH + 1));
	}

	/** Set measurement mode.
	 * @param newMode New measurement mode
	 * @see getMode()
	 * @see HMC5883L_MODE_CONTINUOUS
	 * @see HMC5883L_MODE_SINGLE
	 * @see HMC5883L_MODE_IDLE
	 * @see HMC5883L_RA_MODE
	 * @see HMC5883L_MODEREG_BIT
	 * @see HMC5883L_MODEREG_LENGTH
	 */
	void HMC5883L_User::HMC5883L_setMode(uint8_t newMode) {
	    // use this method to guarantee that bits 7-2 are set to zero, which is a
	    // requirement specified in the datasheet; it's actually more efficient than
	    // using the I2Cdev.writeBits method
	    I2C_Port->I2C_Write8(HMC5883L_RA_MODE, newMode << (HMC5883L_MODEREG_BIT - HMC5883L_MODEREG_LENGTH + 1));
	    mode = newMode; // track to tell if we have to clear bit 7 after a read
	}

	/** Get data ready status.
	 * This bit is set when data is written to all six data registers, and cleared
	 * when the device initiates a write to the data output registers and after one
	 * or more of the data output registers are written to. When RDY bit is clear it
	 * shall remain cleared for 250 us. DRDY pin can be used as an alternative to
	 * the status register for monitoring the device for measurement data.
	 * @return Data ready status
	 * @see HMC5883L_RA_STATUS
	 * @see HMC5883L_STATUS_READY_BIT
	 */
	bool HMC5883L_User::HMC5883L_getReadyStatus() {
	    I2C_Port->I2C_Read( HMC5883L_RA_STATUS, buffer, HMC5883L_STATUS_READY_BIT);
	    return buffer[0];
	}
}