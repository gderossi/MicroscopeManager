#include "TestCameraManager.h"

TestCameraManager::TestCameraManager()
{
	bufferCount_ = DEFAULT_BUFFER_COUNT;

	imgBuffer_.SetSize(1920, 1080);
	imgBuffer_.SetPixelDepth(1);
	cameraMask_.SetSize(1920, 1080);
	cameraMask_.SetPixelDepth(1);
	CreateCameraMask(10);
}

TestCameraManager::~TestCameraManager()
{}

double TestCameraManager::GetFloatParameter(int module, std::string name)
{
	return 0;
}

void TestCameraManager::SetFloatParameter(int module, std::string name, double value)
{}

long long TestCameraManager::GetIntParameter(int module, std::string name)
{
	if (name == "Width")
	{
		return 1920;
	}
	if (name == "Height")
	{
		return 1080;
	}
	return 0;
}

void TestCameraManager::SetIntParameter(int module, std::string name, long long value)
{}

std::string TestCameraManager::GetStringParameter(int module, std::string name)
{
	return "";
}

void TestCameraManager::SetStringParameter(int module, std::string name, std::string value)
{}

void TestCameraManager::SetBufferCount(unsigned long long bufferCount)
{
	bufferCount_ = bufferCount;
}

void TestCameraManager::SnapImage()
{
	GetImage();
}

void TestCameraManager::StartAcquisition(uint64_t bufferCount)
{}

void TestCameraManager::StopAcquisition()
{}

void TestCameraManager::GetImage()
{
	char* data = new char[1920*1080];
	for (int i=0; i<1920*1080; i++)
	{
		data[i] = rand() % 256;
	}
	memcpy(imgBuffer_.pixels, data, imgBuffer_.GetSize());
	delete[] data;
}