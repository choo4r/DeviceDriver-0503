#include "device_driver.h"
#include <set>

using std::set;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    set<int> data;
    for (int readTry = 0; readTry < 5; readTry++) 
        data.insert((int)(m_hardware->read(address)));

    if (data.size() != 1)
        throw ReadFailException();

    return *(data.begin());
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    if (m_hardware->read(address) != 0xFF)
        throw WriteFailException();

    m_hardware->write(address, (unsigned char)data);
}