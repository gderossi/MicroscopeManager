#pragma once

#include <string>

class SerialDevice
{
public:
	virtual void WriteData(const char buf[], unsigned long long writeSize) = 0;
	virtual std::string ReadData(unsigned long long readSize) = 0;
};