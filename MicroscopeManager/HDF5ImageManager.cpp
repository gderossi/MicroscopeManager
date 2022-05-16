#include "HDF5ImageManager.h"

HDF5ImageManager::HDF5ImageManager(std::string filename, unsigned long width, unsigned long height) :
	filename_(filename)
{
	dimsf_[0] = width;
	dimsf_[2] = height;
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
	H5Dwrite(dataset_, H5T_NATIVE_CHAR, memspace_, dataspace_, H5P_DEFAULT, buf);
}

void HDF5ImageManager::ReadFile(unsigned char* buf, unsigned long long readSize)
{}

void HDF5ImageManager::SetFilename(std::string filename)
{
	filename_ = filename;
}