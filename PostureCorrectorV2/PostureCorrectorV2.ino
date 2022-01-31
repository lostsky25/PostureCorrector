
#include <Wire.h>
#include "I2C_MPU9250.h"

#define BUZZER_PIN 3
#define FREQUENCY 100
#define DURATION 500
#define PC_SENSETIVE 5

#define DEBUG
#define VISUALIZE

bool stateLoop;
bool incorectAngle;
unsigned long sec_time, last_time;
double* accelData = 0;
MPU9250* mpu9250;
I2C::ACC_AXIS currentAxis;

void setup() {
    Serial.begin(115200);
    mpu9250 = new MPU9250(MPU9250_ADDRESS);
    pinMode(BUZZER_PIN, OUTPUT);
    I2C::_AXIS_Data data = mpu9250->getAccData();
    currentAxis = mpu9250->getAccActiveAxis();
}

void loop() {
#ifdef VISUALIZE
    I2C::_AXIS_Data data = mpu9250->getAccData();
    double x = mpu9250->getAccAngles().getRoll();
    double y = mpu9250->getAccAngles().getPitch();
    double z = mpu9250->getAccAngles().getYaw();
#endif // VISUALIZE

#ifdef DEBUG
    Serial.print("diff: ");
    Serial.print(mpu9250->getDiff());
    Serial.print(" fixed: ");
    Serial.println(mpu9250->getFixedAngle());
#endif // DEBUG

    if (mpu9250->diffAccAngle(PC_SENSETIVE)) {
        tone(BUZZER_PIN, FREQUENCY, DURATION);
    }

    delay(200);
}
