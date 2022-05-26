#include "HDF5ImageManager.h"

HDF5ImageManager::HDF5ImageManager(std::string filename, unsigned long width, unsigned long height) :
	filename_(filename),
	fillVal_(0)
{
	dims_[0] = height;
	dims_[1] = width;
	dims_[2] = 1;

	maxDims_[0] = H5S_UNLIMITED;
	maxDims_[1] = H5S_UNLIMITED;
	maxDims_[2] = H5S_UNLIMITED;

	memspace_ = H5::DataSpace(3, dims_, maxDims_);

	chunkDims_[0] = height;
	chunkDims_[1] = width;
	chunkDims_[2] = 1;

	offset_[0] = 0;
	offset_[1] = 0;
	offset_[2] = 0;
}

HDF5ImageManager::~HDF5ImageManager()
{
	CloseFile();
}

void HDF5ImageManager::ProcessData()
{}

void HDF5ImageManager::CompressData()
{}

void HDF5ImageManager::CreateFile()
{
	if (filename_.find(".h5") == std::string::npos)
	{
		filename_ += ".h5";
	}

	file_ = H5::H5File(filename_, H5F_ACC_TRUNC);
	pList_.setChunk(3, chunkDims_);
	pList_.setFillValue(H5::PredType::NATIVE_UCHAR, &fillVal_);
	dataset_ = file_.createDataSet("Images", H5::PredType::NATIVE_UCHAR, memspace_, pList_);
	dataset_.extend(dims_);
}

void HDF5ImageManager::OpenFile()
{}

void HDF5ImageManager::CloseFile()
{}

void HDF5ImageManager::WriteFile(unsigned char* buf, unsigned long long writeSize, bool newImage)
{
	dataset_.extend(dims_);
	dataspace_ = dataset_.getSpace();
	dataspace_.selectHyperslab(H5S_SELECT_SET, chunkDims_, offset_);
	dataset_.write(buf, H5::PredType::NATIVE_UCHAR, memspace_, dataspace_);
	++dims_[2];
	++offset_[2];
}

void HDF5ImageManager::ReadFile(unsigned char* buf, unsigned long long readSize)
{}

void HDF5ImageManager::SetFilename(std::string filename)
{
	filename_ = filename;
}