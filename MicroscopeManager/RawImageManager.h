#pragma once

#include "ImageManager.h"
#include "windows.h"
#include <string>

#undef CreateFile

class RawImageManager :
    public ImageManager
{
public:
    RawImageManager(std::string filename);
    ~RawImageManager();

    void ProcessData();
    void CompressData();
    void CreateFile();
    void OpenFile();
    void CloseFile();
    void WriteFile(unsigned char* buf, unsigned long long writeSize, bool newImage=false);
    void ReadFile(unsigned char* buf, unsigned long long readSize);
    void SetFilename(std::string filename);

private:
    std::string filename_;
    HANDLE file_;
    bool open_;
    uint32_t fileHeader_[5];
};

