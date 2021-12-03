#include "SerialDevice.h"

SerialDevice::SerialDevice(std::string port, int baudrate, std::vector<std::string> exitCommands) :
	exitCommands_(exitCommands)
{
	device_ = new serial::Serial(port, baudrate, serial::Timeout(1000, 1000, 1, 1000, 1));
}

SerialDevice::~SerialDevice()
{
	if (device_->isOpen())
	{
		device_->flush();

		for (std::string command : GetExitCommands())
		{
			WriteData(command.c_str(), command.size());
		}

		device_->close();
	}

	delete device_;
}

bool SerialDevice::Available()
{
	return device_->available();
}

void SerialDevice::WriteData(const char buf[], unsigned long long writeSize)
{
	device_->write((const uint8_t*)buf, (size_t)writeSize);
}

std::string SerialDevice::ReadData(unsigned long long readSize)
{
	std::string output = "";
	std::string buf;
	int count = 0;
	int maxCount = std::min(readSize, device_->available());
	while (count < maxCount)
	{
		buf = device_->read(1);
		if (buf == "\n" || buf == "\r")
		{
			break;
		}
		output += buf;
		count++;
	}
	
	return output;
}

void SerialDevice::SetExitCommands(std::vector<std::string> exitCommands)
{
	exitCommands_ = exitCommands;
}

std::vector<std::string> SerialDevice::GetExitCommands()
{
	return exitCommands_;
}