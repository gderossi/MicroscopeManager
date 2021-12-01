

#include <iostream>
#include "SerialManager.h"

SerialManager::~SerialManager()
{
	std::map<std::string, SerialDevice*>::iterator i;

	for (i = devices.begin(); i != devices.end(); i++)
	{
		delete i->second;
	}
}

void SerialManager::CreateSerialDevice(std::string deviceName, std::string portName, int baudrate, std::vector<std::string> exitCommands)
{
	devices.emplace(deviceName, new SerialDevice(portName, baudrate, exitCommands));
}

void SerialManager::DeleteSerialDevice(std::string deviceName)
{
	SerialDevice* device = devices.find(deviceName)->second;
	devices.erase(deviceName);
	delete device;
}

SerialDevice* SerialManager::GetSerialDevice(std::string deviceName)
{
	if (devices.find(deviceName) == devices.end())
	{
		return NULL;
	}
	return devices.find(deviceName)->second;
}

std::vector<std::string> SerialManager::GetSerialDeviceNames()
{
	std::map<std::string, SerialDevice*>::iterator i;
	std::vector<std::string> deviceList;

	for (i = devices.begin(); i != devices.end(); ++i)
	{
		deviceList.push_back(i->first);
	}

	return deviceList;
}