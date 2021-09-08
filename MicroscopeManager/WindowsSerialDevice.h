#pragma once

#include "SerialDevice.h"
#include <windows.h>

class WindowsSerialDevice :
    public SerialDevice
{
public:
    WindowsSerialDevice(HANDLE port, int baudrate);
    ~WindowsSerialDevice();

    void WriteData(const char buf[], unsigned long long writeSize);
    std::string ReadData(unsigned long long readSize);

private:
    HANDLE port_;
    DCB dcb_;
    DWORD bytesWritten_;
    DWORD bytesRead_;
};

