#include "SerialDevice.h"

SerialDevice::~SerialDevice()
{

}

void SerialDevice::SetExitCommands(std::vector<std::string> exitCommands)
{
	exitCommands_ = exitCommands;
}

std::vector<std::string> SerialDevice::GetExitCommands()
{
	return exitCommands_;
}