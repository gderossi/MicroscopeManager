#include "RawImageManager.h"

RawImageManager::RawImageManager(std::string filename) :
	filename_(filename),
	file_(0),
	open_(false)
{

}

RawImageManager::~RawImageManager()
{
	if (file_)
	{
		CloseFile();
	}
}

void RawImageManager::ProcessData()
{
	//TODO
}

void RawImageManager::CompressData()
{
	//TODO
}

void RawImageManager::CreateFile()
{
	if (!file_)
	{
		file_ = CreateFileA(filename_.c_str(),
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			CREATE_NEW,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | FILE_FLAG_WRITE_THROUGH,
			NULL);

		open_ = true;
	}
}

void RawImageManager::OpenFile()
{
	if (!file_)
	{
		file_ = CreateFileA(filename_.c_str(),
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | FILE_FLAG_WRITE_THROUGH,
			NULL);

		open_ = true;
	}
}

void RawImageManager::CloseFile()
{
	if (open_)
	{
		CloseHandle(file_);
		file_ = 0;
		open_ = false;
	}
}

void RawImageManager::WriteFile(unsigned char* buf, unsigned long long writeSize)
{
	if (open_)
	{
		DWORD bytesWritten;

		::WriteFile(file_, buf, writeSize, &bytesWritten, NULL);
		DWORD testCount = bytesWritten;
	}
}

void RawImageManager::ReadFile(unsigned char* buf, unsigned long long readSize)
{
	if (open_)
	{
		DWORD bytesRead;

		bool result = ::ReadFile(file_, buf, readSize, &bytesRead, NULL);
	}
}

void RawImageManager::SetFilename(std::string filename)
{
	filename_ = filename;
}