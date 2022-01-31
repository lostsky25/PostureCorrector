#include "I2C_MPU9250.h"

MPU9250::MPU9250(int16_t address) : Accelerometer(address, ACC_FULL_SCALE_4_G) {

}