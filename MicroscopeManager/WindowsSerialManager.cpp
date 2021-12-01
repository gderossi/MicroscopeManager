/*
* WindowsSerialManager.cpp: This is the source file for the 
* WindowsSerialManager class, which creates and acts as an
* interface for WindowsSerialDevice objects and also provides
* COM port information.
*
* Programmer: Grayson Derossi
* gderossi@wustl.edu
*/

#include "WindowsSerialManager.h"
#include "windows.h"

std::vector<std::string> WindowsSerialManager::GetSerialPorts()
{
	HKEY hKey;
	LPCSTR subKey = "HARDWARE\\DEVICEMAP\\SERIALCOMM";
	DWORD cValues;
	DWORD maxValueLen;

	std::vector<std::string> portList;

	RegOpenKeyExA(HKEY_LOCAL_MACHINE, subKey, 0, KEY_READ, &hKey);

	RegQueryInfoKey(hKey,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		&cValues,
		&maxValueLen,
		NULL,
		NULL,
		NULL);

	for (DWORD i = 0; i < cValues; i++)
	{
		char valueName[64];
		DWORD valueNameLen = 64;
		DWORD dataType = 0;
		BYTE data[1024];
		DWORD dataSize = 1024;

		RegEnumValueA(hKey,
			i,
			valueName,
			&valueNameLen,
			NULL,
			&dataType,
			data,
			&dataSize);


		std::string o(data, data + dataSize);

		portList.push_back(std::string(o));
	}

	return portList;
}
