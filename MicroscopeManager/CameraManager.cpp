#include "CameraManager.h"

CameraManager::~CameraManager()
{

}

unsigned char* CameraManager::GetImageBuffer()
{
	return imgBuffer_.pixels;
}

unsigned long long CameraManager::GetImageBufferSize()
{
	return imgBuffer_.GetSize();
}

unsigned long long CameraManager::GetBufferCount()
{
	return bufferCount_;
}