#include "ImageBuffer.h"
#include "windows.h"

ImageBuffer::ImageBuffer(unsigned long long width, unsigned long long height, unsigned long long depth) :
	width_(width),
	height_(height),
	depth_(depth)
{
	size_ = width_ * height_ * depth_;
	pixels = (unsigned char*)VirtualAlloc(NULL, size_, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

ImageBuffer::ImageBuffer() :
	width_(0),
	height_(0),
	depth_(0),
	size_(0),
	pixels(0)
{}

ImageBuffer::~ImageBuffer()
{
	VirtualFree(pixels, 0, MEM_RELEASE);
}

void ImageBuffer::SetSize(unsigned long long width, unsigned long long height)
{
	width_ = width;
	height_ = height;
	size_ = width_ * height_ * depth_;
	VirtualFree(pixels, 0, MEM_RELEASE);
	pixels = (unsigned char*)VirtualAlloc(NULL, size_, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

void ImageBuffer::SetPixelDepth(unsigned long long depth)
{
	depth_ = depth;
	size_ = width_ * height_ * depth_;
	VirtualFree(pixels, 0, MEM_RELEASE);
	pixels = (unsigned char*)VirtualAlloc(NULL, size_, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

unsigned long long ImageBuffer::GetSize()
{
	return size_;
}