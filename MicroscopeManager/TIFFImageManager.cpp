#include "TIFFImageManager.h"

#define MAX_PAGE_COUNT 1024

TIFFImageManager::TIFFImageManager(std::string filename, unsigned long width, unsigned long height) :
	filename_(filename),
	width_(width),
	height_(height),
	file_(0),
	open_(false),
	writing_(false),
	multiImage_(false),
	page_(0)
{
	scanlineBuf_ = _TIFFmalloc(width);
}

TIFFImageManager::~TIFFImageManager()
{
	if (scanlineBuf_)
	{
		_TIFFfree(scanlineBuf_);
	}
	CloseFile();
}

void TIFFImageManager::ProcessData()
{}

void TIFFImageManager::CompressData()
{}

void TIFFImageManager::CreateFile()
{
	if (filename_.find(".tif") == std::string::npos)
	{
		filename_ += ".tif";
	}
	file_ = TIFFOpen(filename_.c_str(), "w8");
	open_ = true;
	multiImage_ = false;
	page_ = 0;
}

void TIFFImageManager::OpenFile()
{
	file_ = TIFFOpen(filename_.c_str(), "a8");
	open_ = true;
	multiImage_ = true;
	page_ = 0;
}

void TIFFImageManager::CloseFile()
{
	if (open_)
	{
		while (writing_) {}
		open_ = false;
		TIFFClose(file_);
	}
}

void TIFFImageManager::WriteFile(unsigned char* buf, unsigned long long writeSize, bool newImage /*=false*/)
{
	if (!open_)
	{
		file_ = TIFFOpen(filename_.c_str(), "a8");
		open_ = true;
		page_ = 0;
	}
    writing_ = true;

    //TIFFSetField(file_, TIFFTAG_PAGENUMBER, page_, page_);
    //TIFFSetField(file_, TIFFTAG_SUBFILETYPE, FILETYPE_PAGE);

    TIFFSetField(file_, TIFFTAG_IMAGEWIDTH, width_);
    TIFFSetField(file_, TIFFTAG_IMAGELENGTH, height_);
    TIFFSetField(file_, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(file_, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
    TIFFSetField(file_, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
    //TIFFSetField(file_, TIFFTAG_STRIPOFFSETS, )
    //TIFFSetField(file_, TIFFTAG_FILLORDER, FILLORDER_MSB2LSB);
    //TIFFSetField(file_, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField(file_, TIFFTAG_SAMPLESPERPIXEL, 1);
    //TIFFSetField(file_, TIFFTAG_ROWSPERSTRIP, 8);
    //TIFFSetField(file_, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    //TIFFSetField(file_, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_UINT);
    TIFFSetField(file_, TIFFTAG_XRESOLUTION, 120);
    TIFFSetField(file_, TIFFTAG_YRESOLUTION, 120);
    TIFFSetField(file_, TIFFTAG_RESOLUTIONUNIT, RESUNIT_NONE);

    for (unsigned long row = 0; row < height_; row++)
    {
        std::memcpy(scanlineBuf_, buf + row * width_, width_);
        if (TIFFWriteScanline(file_, scanlineBuf_, row, 0) == -1)
        {
            writing_ = false;
			open_ = false;
			TIFFClose(file_);
            return;
        }
    }

	//TIFFFlush(file_);
	++page_;

	if (page_ >= MAX_PAGE_COUNT)
	{
		open_ = false;
		TIFFClose(file_);
	}
	else
	{
		TIFFFlush(file_);
	}
	
	writing_ = false;
	//multiImage_ = true;
}

void TIFFImageManager::ReadFile(unsigned char* buf, unsigned long long readSize)
{}

void TIFFImageManager::SetFilename(std::string filename)
{
	filename_ = filename;
}