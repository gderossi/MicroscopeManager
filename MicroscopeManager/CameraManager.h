#pragma once

#include "ImageBuffer.h"
#include <string>

#define DEFAULT_BUFFER_COUNT 256

class CameraManager
{
public:
	virtual double GetFloatParameter(int module, std::string name) = 0;
	virtual void SetFloatParameter(int module, std::string name, double value) = 0;
	virtual long long GetIntParameter(int module, std::string name) = 0;
	virtual void SetIntParameter(int module, std::string name, long long value) = 0;
	virtual std::string GetStringParameter(int module, std::string name) = 0;
	virtual void SetStringParameter(int module, std::string name, std::string value) = 0;
	virtual unsigned long long GetBufferCount();
	virtual void SetBufferCount(unsigned long long bufferCount) = 0;
	virtual void SnapImage() = 0;
	virtual void StartAcquisition(unsigned long long bufferCount) = 0;
	virtual void StopAcquisition() = 0;
	virtual void GetImage() = 0;
	virtual unsigned char* GetImageBuffer();
	virtual unsigned long long GetImageBufferSize();

protected:
	ImageBuffer imgBuffer_;
	unsigned long long bufferCount_;
};