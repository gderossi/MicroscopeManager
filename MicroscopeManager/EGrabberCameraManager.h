#pragma once

#include "CameraManager.h"
#include <EGrabber.h>

using namespace Euresys;

enum GENAPI_MODULE {SYSTEM_MODULE, INTERFACE_MODULE, DEVICE_MODULE, REMOTE_MODULE, STREAM_MODULE};

class EGrabberCameraManager :
    public CameraManager
{
public:
	EGrabberCameraManager();
	~EGrabberCameraManager();
	double GetFloatParameter(int module, std::string name);
	void SetFloatParameter(int module, std::string name, double value);
	long long GetIntParameter(int module, std::string name);
	void SetIntParameter(int module, std::string name, long long value);
	std::string GetStringParameter(int module, std::string name);
	void SetStringParameter(int module, std::string name, std::string value);
	void SetBufferCount(unsigned long long bufferCount);
	void SnapImage();
	void StartAcquisition(uint64_t bufferCount = GENTL_INFINITE);
	void StopAcquisition();
	void GetImage();

private:
	EGenTL genTL;
	EGrabber<CallbackOnDemand> grabber;
};

