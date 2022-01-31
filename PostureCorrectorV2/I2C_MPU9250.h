#pragma once

#include "Accelerometer.h"

#define MPU9250_ADDRESS 0x68

class MPU9250 : public Accelerometer
{
public:
	MPU9250(int16_t address);

};

