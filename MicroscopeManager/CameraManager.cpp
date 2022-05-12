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

void CameraManager::CreateCameraMask(int imageCount)
{
	if (imgBuffer_.pixels && cameraMask_.pixels && imageCount > 0)
	{
		unsigned long long bufferLength = imgBuffer_.GetSize();
		int* maskSumBuffer = new int[bufferLength];

		for (unsigned long long i = 0; i < bufferLength; i++)
		{
			maskSumBuffer[i] = 0;
		}

		for (int i = 0; i < imageCount; i++)
		{
			SnapImage();

			for (unsigned long long i = 0; i < bufferLength; i++)
			{
				maskSumBuffer[i] += imgBuffer_.pixels[i];
			}
		}

		for (unsigned long long i = 0; i < bufferLength; i++)
		{
			cameraMask_.pixels[i] = (char)(maskSumBuffer[i] / imageCount);
		}

		delete[] maskSumBuffer;
	}
}

void CameraManager::ApplyCameraMask()
{
	if (imgBuffer_.pixels && cameraMask_.pixels)
	{
		unsigned long long bufferSize = imgBuffer_.GetSize();

		if (bufferSize == cameraMask_.GetSize())
		{
			unsigned char* pixelMask = cameraMask_.pixels;
			unsigned char* pixel = imgBuffer_.pixels;

			for (unsigned long long i = 0; i < bufferSize; ++i)
			{
				if (*pixel > *pixelMask)
				{
					*pixel -= *pixelMask;
				}
				else
				{
					*pixel = 0;
				}

				++pixel;
				++pixelMask;
			}
		}
	}
}