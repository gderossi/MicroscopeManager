/*
* EGrabberCameraManager.cpp: This is the source file for the
* EGrabberCameraManager class, which interfaces with a Euresys
* frame grabber and associated camera to manage camera setup and capture.
*
* Programmer: Grayson Derossi
* gderossi@wustl.edu
*/

#include "EGrabberCameraManager.h"
#include <iostream>

EGrabberCameraManager::EGrabberCameraManager() :
	grabber(genTL)
{
	bufferCount_ = DEFAULT_BUFFER_COUNT;

	uint64_t w = grabber.getInteger<StreamModule>("Width");
	uint64_t h = grabber.getInteger<StreamModule>("Height");
	uint64_t d = grabber.getInteger<StreamModule>("PixelSize") / 8;

	imgBuffer_.SetSize(w, h);
	imgBuffer_.SetPixelDepth(d);
	cameraMask_.SetSize(w, h);
	cameraMask_.SetPixelDepth(d);
}

double EGrabberCameraManager::GetFloatParameter(int module, std::string name)
{
	switch (module)
	{
	case SYSTEM_MODULE:
		return grabber.getFloat<SystemModule>(name);
		break;

	case INTERFACE_MODULE:
		return grabber.getFloat<InterfaceModule>(name);
		break;

	case DEVICE_MODULE:
		return grabber.getFloat<DeviceModule>(name);
		break;

	case REMOTE_MODULE:
		return grabber.getFloat<RemoteModule>(name);
		break;

	case STREAM_MODULE:
		return grabber.getFloat<StreamModule>(name);
		break;
	}

	return 0;
}

void EGrabberCameraManager::SetFloatParameter(int module, std::string name, double value)
{
	switch (module)
	{
	case SYSTEM_MODULE:
		grabber.setFloat<SystemModule>(name, value);
		break;

	case INTERFACE_MODULE:
		grabber.setFloat<InterfaceModule>(name, value);
		break;

	case DEVICE_MODULE:
		grabber.setFloat<DeviceModule>(name, value);
		break;

	case REMOTE_MODULE:
		grabber.setFloat<RemoteModule>(name, value);
		break;

	case STREAM_MODULE:
		grabber.setFloat<StreamModule>(name, value);
		break;
	}
}

long long EGrabberCameraManager::GetIntParameter(int module, std::string name)
{
	switch (module)
	{
	case SYSTEM_MODULE:
		return grabber.getInteger<SystemModule>(name);
		break;

	case INTERFACE_MODULE:
		return grabber.getInteger<InterfaceModule>(name);
		break;

	case DEVICE_MODULE:
		return grabber.getInteger<DeviceModule>(name);
		break;

	case REMOTE_MODULE:
		return grabber.getInteger<RemoteModule>(name);
		break;

	case STREAM_MODULE:
		return grabber.getInteger<StreamModule>(name);
		break;
	}

	return 0;
}

void EGrabberCameraManager::SetIntParameter(int module, std::string name, long long value)
{
	switch (module)
	{
	case SYSTEM_MODULE:
		grabber.setInteger<SystemModule>(name, value);
		break;

	case INTERFACE_MODULE:
		grabber.setInteger<InterfaceModule>(name, value);
		break;

	case DEVICE_MODULE:
		grabber.setInteger<DeviceModule>(name, value);
		break;

	case REMOTE_MODULE:
		grabber.setInteger<RemoteModule>(name, value);
		break;

	case STREAM_MODULE:
		grabber.setInteger<StreamModule>(name, value);
		break;
	}
}

std::string EGrabberCameraManager::GetStringParameter(int module, std::string name)
{
	switch (module)
	{
	case SYSTEM_MODULE:
		return grabber.getString<SystemModule>(name);
		break;

	case INTERFACE_MODULE:
		return grabber.getString<InterfaceModule>(name);
		break;

	case DEVICE_MODULE:
		return grabber.getString<DeviceModule>(name);
		break;

	case REMOTE_MODULE:
		return grabber.getString<RemoteModule>(name);
		break;

	case STREAM_MODULE:
		return grabber.getString<StreamModule>(name);
		break;
	}
	return "";
}

void EGrabberCameraManager::SetStringParameter(int module, std::string name, std::string value)
{
	switch (module)
	{
	case SYSTEM_MODULE:
		grabber.setString<SystemModule>(name, value);
		break;

	case INTERFACE_MODULE:
		grabber.setString<InterfaceModule>(name, value);
		break;

	case DEVICE_MODULE:
		grabber.setString<DeviceModule>(name, value);
		break;

	case REMOTE_MODULE:
		grabber.setString<RemoteModule>(name, value);
		break;

	case STREAM_MODULE:
		grabber.setString<StreamModule>(name, value);
		break;
	}
}

void EGrabberCameraManager::SetBufferCount(unsigned long long bufferCount)
{
	grabber.reallocBuffers(bufferCount);
	bufferCount_ = bufferCount;
}

void EGrabberCameraManager::SnapImage()
{
	grabber.reallocBuffers(1);
	grabber.start(1);
	GetImage();
	grabber.stop();
}

void EGrabberCameraManager::StartAcquisition(uint64_t bufferCount /*=GENTL_INFINITE*/)
{
	grabber.reallocBuffers(bufferCount_);
	grabber.start(bufferCount);
}

void EGrabberCameraManager::StopAcquisition()
{
	grabber.stop();
}

void EGrabberCameraManager::GetImage()
{
	ScopedBuffer buffer(grabber);
	uint8_t* img = buffer.getInfo<uint8_t*>(gc::BUFFER_INFO_BASE);
	memcpy(imgBuffer_.pixels, img, imgBuffer_.GetSize());
}
