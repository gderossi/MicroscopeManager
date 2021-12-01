#pragma once
#include "SerialManager.h"

class WindowsSerialManager :
    public SerialManager
{
public:
	std::vector<std::string> GetSerialPorts();
};

