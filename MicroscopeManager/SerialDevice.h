#pragma once

#include <string>
#include <vector>
#include "serial\serial.h"

class SerialDevice
{
public:
	SerialDevice(std::string port, int baudrate, std::vector<std::string> exitCommands);
	virtual ~SerialDevice();
	virtual bool Available();
	virtual void WriteData(const char buf[], unsigned long long writeSize);
	virtual std::string ReadData(unsigned long long readSize);
	void SetExitCommands(std::vector<std::string> exitCommands);
	std::vector<std::string> GetExitCommands();
private:
	serial::Serial* device_;
	std::vector<std::string> exitCommands_;
};