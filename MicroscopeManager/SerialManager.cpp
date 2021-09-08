

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