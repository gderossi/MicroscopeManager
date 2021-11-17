#pragma once

#include <string>
#include <vector>

class SerialDevice
{
public:
	virtual ~SerialDevice();
	virtual void WriteData(const char buf[], unsigned long long writeSize) = 0;
	virtual std::string ReadData(unsigned long long readSize) = 0;
	void SetExitCommands(std::vector<std::string> exitCommands);
	std::vector<std::string> GetExitCommands();
private:
	std::vector<std::string> exitCommands_;
};