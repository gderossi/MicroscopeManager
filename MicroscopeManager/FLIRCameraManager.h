#pragma once
#include "CameraManager.h"
#include "Spinnaker.h"
#include "SpinGenApi//SpinnakerGenApi.h"

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;

class FLIRCameraManager :
    public CameraManager
{
public:
	FLIRCameraManager();
	~FLIRCameraManager();
	double GetFloatParameter(int module, std::string name);
	void SetFloatParameter(int module, std::string name, double value);
	long long GetIntParameter(int module, std::string name);
	void SetIntParameter(int module, std::string name, long long value);
	std::string GetStringParameter(int module, std::string name);
	void SetStringParameter(int module, std::string name, std::string value);
	void SetBufferCount(unsigned long long bufferCount);
	void SnapImage();
	void StartAcquisition(uint64_t bufferCount = 0xFFFFFFFFFFFFFFFF);
	void StopAcquisition();
	void GetImage();

private:
	SystemPtr system_;
	CameraList camList_;
	CameraPtr camera_;
};

