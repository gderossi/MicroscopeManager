#pragma once
#include "ImageManager.h"
#include "hdf5.h"

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
	hid_t pList_;
	hid_t file_;
	hid_t dataset_;
	hid_t datatype_;
	hid_t dataspace_;
	hid_t memspace_;
	unsigned long long dimsf_[3];
	unsigned long long count_[3];
	unsigned long long offset_[3];
	unsigned long long stride_[3];
	unsigned long long block_[3];
	herr_t status_;
	std::string filename_;
};

