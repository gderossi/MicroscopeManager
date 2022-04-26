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
		if (imgBuffer_.GetSize() == cameraMask_.GetSize())
		{
			unsigned char pixelMask;

			for (int i = 0; i < imgBuffer_.GetSize(); i++)
			{
				pixelMask = cameraMask_.pixels[i];
				if (imgBuffer_.pixels[i] > pixelMask)
				{
					imgBuffer_.pixels[i] -= pixelMask;
				}
				else
				{
					imgBuffer_.pixels[i] = 0;
				}
			}
		}
	}
}