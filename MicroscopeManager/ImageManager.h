#pragma once

#include <string>

class ImageManager
{
public:
	virtual void ProcessData() = 0;
	virtual void CompressData() = 0;
	virtual void CreateFile() = 0;
	virtual void OpenFile() = 0;
	virtual void CloseFile() = 0;
	virtual void WriteFile(unsigned char* buf, unsigned long long writeSize) = 0;
	virtual void ReadFile(unsigned char* buf, unsigned long long readSize) = 0;
	virtual void SetFilename(std::string filename) = 0;
};