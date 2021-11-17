#pragma once

#include <map>
#include <string>
#include <vector>
#include "SerialDevice.h"

class SerialManager
{
public:
	virtual ~SerialManager();

	virtual std::vector<std::string> GetSerialPorts() = 0;
	virtual void CreateSerialDevice(std::string deviceName, std::string portName, int baudrate, std::vector<std::string> exitCommands) = 0;
	virtual void DeleteSerialDevice(std::string deviceName) = 0;
	SerialDevice* GetSerialDevice(std::string deviceName);
	std::vector<std::string> GetSerialDeviceNames();
protected:
	std::map<std::string, SerialDevice*> devices;
};