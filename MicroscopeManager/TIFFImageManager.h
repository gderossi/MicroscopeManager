#pragma once
#include "ImageManager.h"
#include "tiffiop.h"

#undef CreateFile

class TIFFImageManager :
    public ImageManager
{
public:
	TIFFImageManager(std::string filename, unsigned long width=1920, unsigned long height=1080);
	~TIFFImageManager();
	void ProcessData();
	void CompressData();
	void CreateFile();
	void OpenFile();
	void CloseFile();
	void WriteFile(unsigned char* buf, unsigned long long writeSize, bool newImage = false);
	void ReadFile(unsigned char* buf, unsigned long long readSize);
	void SetFilename(std::string filename);

private:
	std::string filename_;
	TIFF* file_;
	bool open_;
	unsigned long height_;
	unsigned long width_;
	unsigned char* scanlineBuf_;
	bool writing_;
	bool multiImage_;
};

