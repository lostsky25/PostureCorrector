#include "Accelerometer.h"

Accelerometer::Accelerometer() {

}

/// <summary>
/// The constructor needs to get the address of the device and its 
/// sensitivity, there are four sensitivity modes.
/// ACC_FULL_SCALE_2_G 
/// ACC_FULL_SCALE_4_G
/// ACC_FULL_SCALE_8_G
/// ACC_FULL_SCALE_16_G
/// 1) Initializes the Wire library and connects the Arduino to 
///    the I2C bus as a master or slave device. 
///    Typically, this function is called only once.
/// 
/// 2) Set accelerometers low pass filter at 5Hz.
/// 
/// 3) Configure accelerometers range.
/// 
/// 4) Setting a fixed angle to compare against.
/// </summary>
/// <param name="address"></param>
/// <param name="range"></param>
Accelerometer::Accelerometer(uint8_t address, uint8_t range)
{
    this->address = address;
    this->range = range;

    Wire.begin();                                       //Initializes the Wire library.
    accWriteByte(this->address, 29, 0x06);              // Set accelerometers low pass filter at 5Hz.
    accWriteByte(this->address, 28, this->range);       // Configure accelerometers range.

    angles = getAccAngles();
    mainAxis = getAccActiveAxis();                      

    switch (mainAxis)
    {
        case I2C::ACC_AXIS::AX:
            fixedAngle = angles.getRoll();              // Fixed Angle AX Setting
        break;

        case I2C::ACC_AXIS::AY:
            fixedAngle = angles.getPitch();             // Fixed Angle AY Setting
        break;

        case I2C::ACC_AXIS::AZ:
            fixedAngle = angles.getYaw();               // Fixed Angle AZ Setting
        break;
    default:
        break;
    }
}

/// <summary>
/// The method looks for the maximum of three values, 
/// after that it returns an index that points to a specific axis.
/// </summary>
/// <param name="x">Accelerometer x value.</param>
/// <param name="y">Accelerometer y value.</param>
/// <param name="z">Accelerometer z value.</param>
/// <returns>Index specific axis.</returns>
I2C::ACC_AXIS Accelerometer::_max(int16_t x, int16_t y, int16_t z) {
    I2C::ACC_AXIS temp;
    if (abs(x) > abs(y)) {
        temp = I2C::AX;
    }
    else {
        temp = I2C::AY;
    }

    switch (temp)
    {
    case I2C::AX:
        if (abs(x) > abs(z))
        {
            temp = I2C::AX;
        }
        else if (abs(z) > abs(x)) {
            temp = I2C::AZ;
        }
        break;
    case I2C::AY:
        if (abs(y) > abs(z))
        {
            temp = I2C::AY;
        }
        else if (abs(z) > abs(y)) {
            temp = I2C::AZ;
        }
        break;
    default:
        break;
    }
    return temp;
}

/// <summary>
/// Returns the main axis from which calculations will be 
/// performed. The return value must be remembered.
/// </summary>
/// <seealso cref="Accelerometer::_max"/>
/// <returns>Index main axis.</returns>
I2C::_ACC_AXIS Accelerometer::getAccActiveAxis()
{
    return _max(data.getX(), data.getY(), data.getZ());
}

/// <summary>
/// the data goes into a static array of size 6. 
/// It is also necessary to perform a bitwise 
/// shift by 8 bits of the 0, 2 and 4th element.
/// </summary>
/// <seealso cref="Accelerometer::accRead"/>
/// <returns>Data structure that contains values along three axes.</returns>
I2C::_AXIS_Data Accelerometer::getAccData() {
    uint8_t Buf[14];
    accRead(address, 0x3B, 14, Buf);

    data.setX(-(Buf[0] << 8 | Buf[1]));
    data.setY(-(Buf[2] << 8 | Buf[3]));
    data.setZ((Buf[4] << 8 | Buf[5]));

    return data;
}

/// <summary>
/// The method calculates pitch, roll and yaw. Values ranging from -180 to +180 degrees.
/// </summary>
/// <seealso cref="I2C::AXIS_Angles::setRoll"/>
/// <seealso cref="I2C::AXIS_Angles::setPitch"/>
/// <seealso cref="I2C::AXIS_Angles::setYaw"/>
/// <returns>Data structure that contains the current angles along the three axes.</returns>
I2C::_AXIS_Angles Accelerometer::getAccAngles()
{
    I2C::_AXIS_Angles angles;
    angles.setRoll(atan(data.getX() / sqrt(pow(data.getY(), 2) + pow(data.getZ(), 2))) * 180 / M_PI);
    angles.setPitch(atan(data.getY() / sqrt(pow(data.getX(), 2) + pow(data.getZ(), 2))) * 180 / M_PI);
    angles.setYaw(atan(sqrt(pow(data.getX(), 2) + pow(data.getY(), 2)) / data.getZ()) * 180 / M_PI);

    return angles;
}

/// <summary>
/// The method itself performs all the necessary 
/// calculations, preliminary calls to Accelerometer::getAxAngles 
/// are not needed.
/// </summary>
/// <param name="sensetive">Maximum allowable deflection angle.</param>
/// <seealso cref="Accelerometer::getAccAngles"/>
/// <returns>If the angle has exceeded the maximum allowable deflection angle, then true will be returned, otherwise false.</returns>
bool Accelerometer::diffAccAngle(int8_t sensetive)
{
    angles = getAccAngles();
    switch (mainAxis)
    {
    case I2C::ACC_AXIS::AX:
        diff = abs(abs(fixedAngle) - abs(angles.getRoll()));
        break;

    case I2C::ACC_AXIS::AY:
        diff = abs(abs(fixedAngle) - abs(angles.getPitch()));
        break;

    case I2C::ACC_AXIS::AZ:
        diff = abs(abs(fixedAngle) - abs(angles.getYaw()));
        break;
    default:
        break;
    }

    if (diff > sensetive) {
        return true;
    }
    else {
        return false;
    }

    //return diff;
}

/// <summary>
/// The method reads the required cell of the I2C device.
/// </summary>
/// <param name="address">Device I2C address in hexadecimal format.</param>
/// <param name="_register">Read cell (hex).</param>
/// <param name="Nbytes">Count of bytes.</param>
/// <param name="data">Pointer to the first array element that will contain the received data.</param>
void Accelerometer::accRead(uint8_t address, uint8_t _register, uint8_t Nbytes, uint8_t* data) {
    Wire.beginTransmission(address);   // Slave installation.
    Wire.write(_register);             // Queue bytes for transmission.
    Wire.endTransmission();            // Transmit bytes.
                                          
    Wire.requestFrom(address, Nbytes); // Read Nbytes.
    uint8_t index = 0;                    
    while (Wire.available())           // Returns the number of bytes available for retrieval with read().
    data[index++] = Wire.read();       // Reads a byte that was transmitted from a slave device to a master after a call to requestFrom().
}

/// <summary>
/// You can use it for debugging.
/// </summary>
/// <returns>diff variable.</returns>
double Accelerometer::getDiff() {
    return diff;
}

/// <summary>
/// You can use it for debugging.
/// </summary>
/// <returns>fixedAngle variable.</returns>
double Accelerometer::getFixedAngle() {
    return fixedAngle;
}

/// <summary>
/// The method writes the required cell of the I2C device.
/// </summary>
/// <param name="address">Device I2C address in hexadecimal format.</param>
/// <param name="_register">Read cell (hex).</param>
/// <param name="data">Pointer to the first array element that will contain the received data.</param>
void Accelerometer::accWriteByte(uint8_t address, uint8_t _register, uint8_t data){
    Wire.beginTransmission(address);   // Slave installation.
    Wire.write(_register);             // Queue bytes for transmission.
    Wire.write(data);                  // Write bytes.
    Wire.endTransmission();            // Transmit bytes.
}