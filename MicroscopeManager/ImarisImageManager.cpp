#include "ImarisImageManager.h"

void RecordProgress(bpFloat aProgress, bpFloat aTP) { return; }


ImarisImageManager::ImarisImageManager(tSize5D imageSize,
	tDimensionSequence5D blockDimensionSequence,
	tSize5D blockSize5D,
	tSize5D sample,
	bpSize blockSize,
	bpString outputFile,
	cOptions options,
	cImageExtent imageExtent):
	imageSize_(imageSize),
	blockDimensionSequence_(blockDimensionSequence),
	blockSize5D_(blockSize5D),
	sample_(sample),
	blockSize_(blockSize),
	outputFile_(outputFile),
	options_(options),
	imageConverter(0),
	imageExtent_(imageExtent),
	open_(false)
{
	for (int i = 0; i < 5; i++)
	{
		blockIndex_[i] = 0;
	}
}

ImarisImageManager::~ImarisImageManager()
{
	if (open_)
	{
		CloseFile();
	}
}

void ImarisImageManager::ProcessData()
{
	//TODO
}

void ImarisImageManager::CompressData()
{
	//Compression handled by ImarisWriter
}

void ImarisImageManager::CreateFile()
{
	//Create new ImageConverter, which in turn creates/opens file
	if (!imageConverter)
	{
		imageConverter = new bpImageConverter<bpUInt8>(bpUInt8Type,
			imageSize_,
			sample_,
			blockDimensionSequence_,
			blockSize5D_,
			outputFile_,
			options_,
			"ImarisImageManager",
			"1.0",
			RecordProgress);
		open_ = true;
	}
}

void ImarisImageManager::OpenFile()
{
	//ImarisWriter handles all of this, so just combine create and open
	CreateFile();
}

void ImarisImageManager::CloseFile()
{
	tColorInfoVector colorInfoPerChannel(imageSize_[C]);
	tTimeInfoVector timeInfoPerTimePoint;
	tParameters parameters;

	imageConverter->Finish(imageExtent_, parameters, timeInfoPerTimePoint, colorInfoPerChannel, false);
	delete imageConverter;
	open_ = false;
}

void ImarisImageManager::WriteFile(unsigned char* buf, unsigned long long writeSize)
{
	imageConverter->CopyBlock(buf,
		{ {blockDimensionSequence_[0], 0},
		{blockDimensionSequence_[1], 0},
		{blockDimensionSequence_[2], 0},
		{blockDimensionSequence_[3], 0},
		{blockDimensionSequence_[4], 0} });

	//Update block position values
	if (++blockIndex_[4] == (imageSize_[blockDimensionSequence_[4]] - 1) / blockSize5D_[blockDimensionSequence_[4]] + 1)
	{
		blockIndex_[4] = 0;

		if (++blockIndex_[3] == (imageSize_[blockDimensionSequence_[3]] - 1) / blockSize5D_[blockDimensionSequence_[3]] + 1)
		{
			blockIndex_[3] = 0;

			if (++blockIndex_[2] == (imageSize_[blockDimensionSequence_[2]] - 1) / blockSize5D_[blockDimensionSequence_[2]] + 1)
			{
				blockIndex_[2] = 0;

				if (++blockIndex_[1] == (imageSize_[blockDimensionSequence_[1]] - 1) / blockSize5D_[blockDimensionSequence_[1]] + 1)
				{
					blockIndex_[1] = 0;

					if (++blockIndex_[0] == (imageSize_[blockDimensionSequence_[0]] - 1) / blockSize5D_[blockDimensionSequence_[0]] + 1)
					{
						blockIndex_[0] = 0;
					}
				}
			}
		}
	}

}

void ImarisImageManager::ReadFile(unsigned char* buf, unsigned long long readSize)
{
	//Cannot read Imaris files using ImarisWriter
}

void ImarisImageManager::SetFilename(std::string filename)
{
	outputFile_ = filename;
}