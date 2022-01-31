#pragma once

namespace I2C {

    typedef enum ACC_AXIS {
        AX = 0x01,
        ROLL = AX,
        AY = 0x02,
        PITCH = AY,
        AZ = 0x03,
        YAW = AZ
    }_ACC_AXIS;

    typedef struct AXIS_Data{
    private:
        int16_t ax;
        int16_t ay;
        int16_t az;

    public:
        int16_t getX() {
            return ax;
        }

        int16_t getY() {
            return ay;
        }

        int16_t getZ() {
            return az;
        }

        void setX(int16_t ax) {
            this->ax = ax;
        }

        void setY(int16_t ay) {
            this->ay = ay;
        }

        void setZ(int16_t az) {
            this->az = az;
        }
    }_AXIS_Data;

    typedef struct AXIS_Angles {
    private:
        double roll;  //x
        double pitch; //y
        double yaw;   //z
    public:
        double getRoll() {
            return roll;
        }

        double getPitch() {
            return pitch;
        }

        double getYaw() {
            return yaw;
        }

        void setRoll(int16_t roll) {
            this->roll = roll;
        }

        void setPitch(int16_t pitch) {
            this->pitch = pitch;
        }

        void setYaw(int16_t yaw) {
            this->yaw = yaw;
        }
    }_AXIS_Angles;

}