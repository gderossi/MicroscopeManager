/*
* MicroscopeManager.cpp: This is the source file for the
* MicroscopeManager class, which integrates the different
* manager classes into a single place for easy control.
*
* Programmer: Grayson Derossi
* gderossi@wustl.edu
*/

#include "MicroscopeManager.h"

MicroscopeManager::MicroscopeManager(std::string filename) :
	filename_(filename),
	imageManager(0),
	cameraManager(0),
	serialManager(0)
{
	imageManagerTypes.push_back("Raw");
	imageManagerTypes.push_back("Imaris");
	imageManagerTypes.push_back("TIFF");
	imageManagerTypes.push_back("HDF5");

	cameraManagerTypes.push_back("EGrabber");
	cameraManagerTypes.push_back("FLIR");
	cameraManagerTypes.push_back("Test");

	serialManagerTypes.push_back("Windows");
}

MicroscopeManager::~MicroscopeManager()
{
	StopAcquisition();

	if(imageManager)
	{
		delete imageManager;
	}
	if (cameraManager)
	{
		delete cameraManager;
	}
	if (serialManager)
	{
		delete serialManager;
	}
	
}

///////////////////////////////////////////////////////////////////////////////
// Setup functions
///////////////////////////////////////////////////////////////////////////////

void MicroscopeManager::SetFilename(std::string filename)
{
	filename_ = filename;

	if (imageManager)
	{
		imageManager->SetFilename(filename);
	}
}

void MicroscopeManager::CreateImageManager(std::string imageManagerType, char* parameters)
{
	

	if (imageManagerType == "Raw")
	{
		imageManager = new RawImageManager(filename_);
	}
	else if (imageManagerType == "Imaris")
	{

		//imageManager = new ImarisImageManager();
	}
	else if (imageManagerType == "TIFF")
	{
		imageManager = new TIFFImageManager(filename_);
	}
	else if (imageManagerType == "HDF5")
	{
		imageManager = new HDF5ImageManager(filename_);
	}
}

void MicroscopeManager::CreateCameraManager(std::string cameraManagerType, char* parameters)
{
	if (cameraManager)
	{
		delete cameraManager;
	}

	if(cameraManagerType == "EGrabber")
	{
		cameraManager = new EGrabberCameraManager();
	}

	if (cameraManagerType == "FLIR")
	{
		cameraManager = new FLIRCameraManager();
	}

	if (cameraManagerType == "Test")
	{
		cameraManager = new TestCameraManager();
	}
}

void MicroscopeManager::CreateSerialManager(std::string serialManagerType, char* parameters)
{
	if (serialManager)
	{
		delete serialManager;
	}

	if(serialManagerType == "Windows")
	{
		serialManager = new WindowsSerialManager();
	}
}

///////////////////////////////////////////////////////////////////////////////
// SerialManager functions
///////////////////////////////////////////////////////////////////////////////

std::vector<std::string> MicroscopeManager::GetSerialPorts()
{
	if (serialManager)
	{
		return serialManager->GetSerialPorts();
	}

	return std::vector<std::string>();
}

void MicroscopeManager::ConnectSerialDevice(std::string deviceName, std::string portName, int baudrate, std::vector<std::string> exitCommands)
{
	if (serialManager)
	{
		serialManager->CreateSerialDevice(deviceName, portName, baudrate, exitCommands);
	}
}

void MicroscopeManager::DisconnectSerialDevice(std::string deviceName)
{
	if (serialManager)
	{
		serialManager->DeleteSerialDevice(deviceName);
	}
}

std::vector<std::string> MicroscopeManager::ListConnectedSerialDevices()
{
	if (serialManager)
	{
		return serialManager->GetSerialDeviceNames();
	}

	return std::vector<std::string>();
}

SerialDevice* MicroscopeManager::GetSerialDevice(std::string deviceName)
{
	return serialManager->GetSerialDevice(deviceName);
}

void MicroscopeManager::SerialWrite(std::string deviceName, const char* data, unsigned long long writeSize)
{
	if (serialManager)
	{
		SerialDevice* device = serialManager->GetSerialDevice(deviceName);
		if (device)
		{
			device->WriteData(data, writeSize);
		}
	}
}

std::string MicroscopeManager::SerialRead(std::string deviceName, unsigned long long readSize)
{
	if (serialManager)
	{
		return serialManager->GetSerialDevice(deviceName)->ReadData(readSize);
	}

	return "";
}

///////////////////////////////////////////////////////////////////////////////
// CameraManager functions
///////////////////////////////////////////////////////////////////////////////

double MicroscopeManager::GetCameraFloatParameter(int module, std::string name)
{
	if (cameraManager)
	{
		return cameraManager->GetFloatParameter(module, name);
	}

	return 0;
}

void MicroscopeManager::SetCameraFloatParameter(int module, std::string name, double value)
{
	if (cameraManager)
	{
		cameraManager->SetFloatParameter(module, name, value);
	}
}

long long MicroscopeManager::GetCameraIntParameter(int module, std::string name)
{
	if (cameraManager)
	{
		return cameraManager->GetIntParameter(module, name);
	}

	return 0;
}

void MicroscopeManager::SetCameraIntParameter(int module, std::string name, long long value)
{
	if (cameraManager)
	{
		cameraManager->SetIntParameter(module, name, value);
	}
}

std::string MicroscopeManager::GetCameraStringParameter(int module, std::string name)
{
	if (cameraManager)
	{
		return cameraManager->GetStringParameter(module, name);
	}

	return "";
}

void MicroscopeManager::SetCameraStringParameter(int module, std::string name, std::string value)
{
	if (cameraManager)
	{
		cameraManager->SetStringParameter(module, name, value);
	}
}

void MicroscopeManager::SnapImage()
{
	if (cameraManager)
	{
		cameraManager->SnapImage();
	}
}

void MicroscopeManager::StartAcquisition(unsigned long long bufferCount)
{
	if (cameraManager)
	{
		cameraManager->StartAcquisition(bufferCount);
	}
}

void MicroscopeManager::StopAcquisition()
{
	if (cameraManager)
	{
		cameraManager->StopAcquisition();
	}
}

void MicroscopeManager::GetImage()
{
	if (cameraManager)
	{
		cameraManager->GetImage();
	}
}

unsigned char* MicroscopeManager::GetImageBuffer()
{
	if (cameraManager)
	{
		return cameraManager->GetImageBuffer();
	}

	return 0;
}

unsigned long long MicroscopeManager::GetImageBufferSize()
{
	if (cameraManager)
	{
		return cameraManager->GetImageBufferSize();
	}

	return 0;
}

void MicroscopeManager::CreateCameraMask(int imageCount)
{
	if (cameraManager)
	{
		cameraManager->CreateCameraMask(imageCount);
	}
}

void MicroscopeManager::ApplyCameraMask()
{
	if (cameraManager)
	{
		cameraManager->ApplyCameraMask();
	}
}

///////////////////////////////////////////////////////////////////////////////
// ImageManager functions
///////////////////////////////////////////////////////////////////////////////

void MicroscopeManager::CreateFile()
{
	if (imageManager)
	{
		imageManager->CreateFile();
	}
}

void MicroscopeManager::OpenFile()
{
	if (imageManager)
	{
		imageManager->OpenFile();
	}
}

void MicroscopeManager::CloseFile()
{
	if (imageManager)
	{
		imageManager->CloseFile();
	}
}

void MicroscopeManager::WriteFile(unsigned char* buf, unsigned long long writeSize, bool newImage /*=false*/, bool process /*=false*/, bool compress /*=false*/)
{
	if (imageManager)
	{
		if (process)
		{
			imageManager->ProcessData();
		}
		if (compress)
		{
			imageManager->CompressData();
		}

		imageManager->WriteFile(buf, writeSize, newImage);
	}
}

void MicroscopeManager::ReadFile(unsigned char* buf, unsigned long long readSize)
{
	if (imageManager)
	{
		imageManager->ReadFile(buf, readSize);
	}
}