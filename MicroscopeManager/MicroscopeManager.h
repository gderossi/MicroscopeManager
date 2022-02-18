#pragma once

#include "ImageManagers.h"
#include "CameraManagers.h"
#include "SerialManagers.h"

enum IMAGE_MANAGERS {RAW, IMARIS};
enum CAMERA_MANAGERS {EGRABBER, FLIR};
enum SERIAL_MANAGERS {WINDOWS};

#undef CreateFile

class MicroscopeManager
{
public:
	MicroscopeManager(std::string filename);
	~MicroscopeManager();

	void SetFilename(std::string filename);
	void CreateImageManager(std::string imageManagerType, char* parameters);
	void CreateCameraManager(std::string cameraManagerType, char* parameters);
	void CreateSerialManager(std::string serialManagerType, char* parameters);

	std::vector<std::string> GetSerialPorts();
	void ConnectSerialDevice(std::string deviceName, std::string portName, int baudrate, std::vector<std::string> exitCommands);
	void DisconnectSerialDevice(std::string deviceName);
	std::vector<std::string> ListConnectedSerialDevices();
	SerialDevice* GetSerialDevice(std::string deviceName);
	void SerialWrite(std::string deviceName, const char* data, unsigned long long writeSize);
	std::string SerialRead(std::string deviceName, unsigned long long readSize);

	double GetCameraFloatParameter(int module, std::string name);
	void SetCameraFloatParameter(int module, std::string name, double value);
	long long GetCameraIntParameter(int module, std::string name);
	void SetCameraIntParameter(int module, std::string name, long long value);
	std::string GetCameraStringParameter(int module, std::string name);
	void SetCameraStringParameter(int module, std::string name, std::string value);
	void SnapImage();
	void StartAcquisition(unsigned long long bufferCount);
	void StopAcquisition();
	void GetImage();
	unsigned char* GetImageBuffer();
	unsigned long long GetImageBufferSize();
	void CreateCameraMask(int imageCount);
	void ApplyCameraMask();

	void CreateFile();
	void OpenFile();
	void CloseFile();
	void WriteFile(unsigned char* buf, unsigned long long writeSize, bool process=false, bool compress=false);
	void ReadFile(unsigned char* buf, unsigned long long readSize);

	std::vector<std::string> imageManagerTypes;
	std::vector<std::string> cameraManagerTypes;
	std::vector<std::string> serialManagerTypes;

private:
	ImageManager* imageManager;
	CameraManager* cameraManager;
	SerialManager* serialManager;

	std::string filename_;
};
