#pragma once
#include "SerialManager.h"

class WindowsSerialManager :
    public SerialManager
{
public:
	std::vector<std::string> GetSerialPorts();
	void CreateSerialDevice(std::string deviceName, std::string portName, int baudrate);
	void DeleteSerialDevice(std::string deviceName);
};

