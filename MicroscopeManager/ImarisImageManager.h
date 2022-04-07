#pragma once
#include "ImageManager.h"
#include "bpConverterTypes.h"
#include "bpImageConverter.h"

using namespace bpConverterTypes;

class ImarisImageManager :
    public ImageManager
{
public:
    ImarisImageManager(tSize5D imageSize,
        tDimensionSequence5D blockDimensionSequence,
        tSize5D blockSize5D,
        tSize5D sample,
        bpSize blockSize,
        bpString outputFile,
        cOptions options,
        cImageExtent imageExtent);

    ~ImarisImageManager();

    void ProcessData();
    void CompressData();
    void CreateFile();
    void OpenFile();
    void CloseFile();
    void WriteFile(unsigned char* buf, unsigned long long writeSize, bool newImage=false);
    void ReadFile(unsigned char* buf, unsigned long long readSize);
    void SetFilename(std::string filename);

private:
    tSize5D imageSize_;
    tDimensionSequence5D blockDimensionSequence_;
    tSize5D blockSize5D_;
    tSize5D sample_;
    bpSize blockSize_;
    bpString outputFile_;
    cOptions options_;
    cImageExtent imageExtent_;
    bool open_;
    unsigned long long blockIndex_[5];

    bpImageConverter<bpUInt8>* imageConverter;
};

