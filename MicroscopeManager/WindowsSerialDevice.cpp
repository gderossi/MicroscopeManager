/*
* SerialDevice.cpp: This is the source file for the SerialDevice class,
* which is used to connect to and interact with serial devices over
* Windows COM ports.
*
* Programmer: Grayson Derossi
* gderossi@wustl.edu
*/

#include "WindowsSerialDevice.h"
#include <iostream>

WindowsSerialDevice::WindowsSerialDevice(HANDLE port, int baudrate, std::vector<std::string> exitCommands) :
	bytesWritten_(0),
	bytesRead_(0)
{
	SetExitCommands(exitCommands);

	COMMTIMEOUTS timeouts = { 0 };

	port_ = port;
	dcb_.BaudRate = baudrate;
	dcb_.ByteSize = 8;
	dcb_.StopBits = ONESTOPBIT;
	dcb_.Parity = NOPARITY;

	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	SetCommState(port_, &dcb_);
	SetCommMask(port_, EV_RXCHAR);
	SetCommTimeouts(port_, &timeouts);
}

WindowsSerialDevice::~WindowsSerialDevice()
{
	if (port_ != INVALID_HANDLE_VALUE && port_ != NULL)
	{
		for (std::string command : GetExitCommands())
		{
			WriteData(command.c_str(), command.size());
		}

		CloseHandle(port_);
	}
}

void WindowsSerialDevice::WriteData(const char data[], unsigned long long writeSize)
{
	if (!WriteFile(port_, data, writeSize, &bytesWritten_, NULL))
	{
		std::cout << "Write error: " << GetLastError();
	}
}

std::string WindowsSerialDevice::ReadData(unsigned long long readSize)
{
	DWORD commEvent = 0;

	if (WaitCommEvent(port_, &commEvent, NULL))
	{
		char* buf = new char[readSize];

		if (!ReadFile(port_, buf, readSize, &bytesRead_, NULL))
		{
			std::cout << "Read error: " << GetLastError();
		}

		std::string output(buf, buf + bytesRead_);
		delete[] buf;

		return output;
	}

	return std::string("");
}
