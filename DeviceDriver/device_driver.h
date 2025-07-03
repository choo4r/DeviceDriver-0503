#pragma once
#include "flash_memory_device.h"
#include <stdexcept>

class ReadFailException : public std::exception
{
public:
    ReadFailException(char const* _Mesage) : exception(_Mesage) {}
};

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};