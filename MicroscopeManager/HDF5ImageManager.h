#pragma once
#include "ImageManager.h"
#include "H5Cpp.h"

class HDF5ImageManager :
    public ImageManager
{
public:
	HDF5ImageManager(std::string filename, unsigned long width = 1920, unsigned long height = 1080);
	~HDF5ImageManager();
	void ProcessData();
	void CompressData();
	void CreateFile();
	void OpenFile();
	void CloseFile();
	void WriteFile(unsigned char* buf, unsigned long long writeSize, bool newImage = false);
	void ReadFile(unsigned char* buf, unsigned long long readSize);
	void SetFilename(std::string filename);

private:
	H5::DSetCreatPropList pList_;
	H5::H5File file_;
	H5::DataSet dataset_;
	//hid_t datatype_;
	H5::DataSpace dataspace_;
	H5::DataSpace memspace_;
	hsize_t dims_[3];
	hsize_t maxDims_[3];
	hsize_t chunkDims_[3];
	hsize_t offset_[3];
	unsigned char fillVal_;
	//unsigned long long stride_[3];
	//unsigned long long block_[3];
	//herr_t status_;
	std::string filename_;
};

