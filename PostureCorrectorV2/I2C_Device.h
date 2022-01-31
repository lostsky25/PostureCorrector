#pragma once

#include "Wire.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "I2C_Types.h"

class __I2C_Device
{
public:
    virtual void accRead(uint8_t address, uint8_t _register, uint8_t Nbytes, uint8_t* data) = 0;
    virtual void accWriteByte(uint8_t address, uint8_t _register, uint8_t data) = 0;
};

