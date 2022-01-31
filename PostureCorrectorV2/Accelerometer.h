#pragma once

#include "I2C_Device.h"

#define ACC_FULL_SCALE_2_G 0x00 
#define ACC_FULL_SCALE_4_G 0x08
#define ACC_FULL_SCALE_8_G 0x10
#define ACC_FULL_SCALE_16_G 0x18

class Accelerometer : public __I2C_Device
{
private:
    uint8_t address = 0;
    uint8_t range = 0;

    I2C::ACC_AXIS mainAxis;
    I2C::_AXIS_Data data;
    I2C::AXIS_Angles angles;

    I2C::ACC_AXIS _max(int16_t x, int16_t y, int16_t z);

    double fixedAngle = 0.0;
    double diff = 0.0;
    
public:
    Accelerometer();
	Accelerometer(uint8_t address, uint8_t range);

	void accRead(uint8_t address, uint8_t _register, uint8_t Nbytes, uint8_t* data) override;
	void accWriteByte(uint8_t address, uint8_t _register, uint8_t data) override;

    I2C::_ACC_AXIS getAccActiveAxis();
    I2C::_AXIS_Data getAccData();
    I2C::_AXIS_Angles getAccAngles();
    
    double getDiff();
    double getFixedAngle();

    bool diffAccAngle(int8_t sensetive);
};

