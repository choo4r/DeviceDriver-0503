#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int firstData, data;
    for (int readTry = 0; readTry < 5; readTry++) {
        if (readTry == 0) {
            firstData = (int)(m_hardware->read(address));
            continue;
        }

        if (firstData == (data = (int)(m_hardware->read(address)))) continue;

        throw ReadFailException("ReadFailException");
    }
    return firstData;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}