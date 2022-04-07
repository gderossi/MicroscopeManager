#include "RawImageManager.h"

RawImageManager::RawImageManager(std::string filename) :
	filename_(filename),
	file_(0),
	open_(false)
{
	fileHeader_[0] = 82;
	fileHeader_[1] = 512;
	fileHeader_[2] = 1920;
	fileHeader_[3] = 1080;
	fileHeader_[4] = 0;
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

		SetFilePointer(file_, 512, NULL, FILE_BEGIN);

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
		DWORD bytesWritten;
		SetFilePointer(file_, 0, NULL, FILE_BEGIN);
		::WriteFile(file_, fileHeader_, 512, &bytesWritten, NULL);


		CloseHandle(file_);
		file_ = 0;
		open_ = false;
	}
}

void RawImageManager::WriteFile(unsigned char* buf, unsigned long long writeSize, bool newImage /*=false*/)
{
	if (open_)
	{
		DWORD bytesWritten;

		::WriteFile(file_, buf, writeSize, &bytesWritten, NULL);
		
		if (newImage)
		{
			fileHeader_[4]++;
		}
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