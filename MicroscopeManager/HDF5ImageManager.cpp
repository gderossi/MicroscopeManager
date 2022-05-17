#include "HDF5ImageManager.h"

HDF5ImageManager::HDF5ImageManager(std::string filename, unsigned long width, unsigned long height) :
	filename_(filename)
{
	dimsf_[0] = height;
	dimsf_[1] = width;
	dimsf_[2] = 1;

	count_[0] = height;
	count_[1] = width;
	count_[2] = 1;

	offset_[0] = 0;
	offset_[1] = 0;
	offset_[2] = 0;

	stride_[0] = 1;
	stride_[1] = 1;
	stride_[2] = 1;

	block_[0] = 1;
	block_[1] = 1;
	block_[2] = 1;
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
	pList_ = H5Pcreate(H5P_FILE_ACCESS);
	file_ = H5Fcreate(filename_.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, pList_);
	H5Pclose(pList_);

	dataspace_ = H5Screate_simple(3, dimsf_, NULL);
	datatype_ = H5Tcopy(H5T_NATIVE_UCHAR);
	dataset_ = H5Dcreate2(file_, "Images", datatype_, dataspace_, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	H5Sclose(dataspace_);
	memspace_ = H5Screate_simple(3, count_, NULL);
	dataspace_ = H5Dget_space(dataset_);
}

void HDF5ImageManager::OpenFile()
{
	pList_ = H5Pcreate(H5P_FILE_ACCESS);
	file_ = H5Fcreate(filename_.c_str(), H5F_ACC_RDWR, H5P_DEFAULT, pList_);
	H5Pclose(pList_);
}

void HDF5ImageManager::CloseFile()
{
	H5Sclose(dataspace_);
	H5Tclose(datatype_);
	H5Dclose(dataset_);
	H5Fclose(file_);
}

void HDF5ImageManager::WriteFile(unsigned char* buf, unsigned long long writeSize, bool newImage)
{
	H5Sselect_hyperslab(dataspace_, H5S_SELECT_SET, offset_, stride_, count_, block_);
	H5Dwrite(dataset_, H5T_NATIVE_CHAR, memspace_, dataspace_, H5P_DEFAULT, buf);
	++offset_[2];
	++dimsf_[2];
}

void HDF5ImageManager::ReadFile(unsigned char* buf, unsigned long long readSize)
{}

void HDF5ImageManager::SetFilename(std::string filename)
{
	filename_ = filename;
}