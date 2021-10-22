#include "FLIRCameraManager.h"

FLIRCameraManager::FLIRCameraManager()
{
	system_ = System::GetInstance();
	camList_ = system_->GetCameras();

	if (camList_.GetSize() == 0)
	{
		camera_ = NULL;
		return;
	}

	camera_ = camList_.GetByIndex(0);
	camera_->Init();

	INodeMap& nodeMap = camera_->GetNodeMap();

	CIntegerPtr width = nodeMap.GetNode("Width");
	CIntegerPtr height = nodeMap.GetNode("Height");
	//CIntegerPtr depth = nodeMap.GetNode("Pixel Size");
	
	uint64_t w = width->GetValue();
	uint64_t h = height->GetValue();
	uint64_t d = 1;

	imgBuffer_.SetSize(w, h);
	imgBuffer_.SetPixelDepth(d);
}

FLIRCameraManager::~FLIRCameraManager()
{
	camera_->DeInit();
	camList_.Clear();
	system_->ReleaseInstance();
}

double FLIRCameraManager::GetFloatParameter(int module, std::string name)
{
	INodeMap& nodeMap = camera_->GetNodeMap();
	CFloatPtr param = nodeMap.GetNode(name.c_str());
	if (param)
	{
		return param->GetValue();
	}
	return 0;
}

void FLIRCameraManager::SetFloatParameter(int module, std::string name, double value)
{
	INodeMap& nodeMap = camera_->GetNodeMap();
	CFloatPtr param = nodeMap.GetNode(name.c_str());
	if (param)
	{
		param->SetValue(value);
	}
}

long long FLIRCameraManager::GetIntParameter(int module, std::string name)
{
	INodeMap& nodeMap = camera_->GetNodeMap();
	CIntegerPtr param = nodeMap.GetNode(name.c_str());
	if (param)
	{
		return param->GetValue();
	}
	return 0;
}

void FLIRCameraManager::SetIntParameter(int module, std::string name, long long value)
{
	INodeMap& nodeMap = camera_->GetNodeMap();
	CIntegerPtr param = nodeMap.GetNode(name.c_str());
	if (param)
	{
		param->SetValue(value);
	}
}

std::string FLIRCameraManager::GetStringParameter(int module, std::string name)
{
	return "";
}

void FLIRCameraManager::SetStringParameter(int module, std::string name, std::string value)
{
	return;
}

void FLIRCameraManager::SetBufferCount(unsigned long long bufferCount)
{
	INodeMap& nodeMap = camera_->GetNodeMap();
	CIntegerPtr ptrBufferCount = nodeMap.GetNode("StreamBufferCountManual");
	ptrBufferCount->SetValue(bufferCount);
	bufferCount_ = bufferCount;
}

void FLIRCameraManager::SnapImage()
{
	camera_->BeginAcquisition();
	GetImage();
	camera_->EndAcquisition();
}

void FLIRCameraManager::StartAcquisition(uint64_t bufferCount)
{
	camera_->BeginAcquisition();
}

void FLIRCameraManager::StopAcquisition()
{
	camera_->EndAcquisition();
}

void FLIRCameraManager::GetImage()
{
	ImagePtr img = camera_->GetNextImage();
	memcpy(imgBuffer_.pixels, img->GetData(), img->GetBufferSize());
	img->Release();
}


