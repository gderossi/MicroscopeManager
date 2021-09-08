#pragma once
class ImageBuffer
{
public:
	ImageBuffer(unsigned long long width, unsigned long long height, unsigned long long depth);
	ImageBuffer();
	~ImageBuffer();
	void SetSize(unsigned long long width, unsigned long long height);
	void SetPixelDepth(unsigned long long depth);
	unsigned long long GetSize();

	unsigned char* pixels;

private:
	unsigned long long width_;
	unsigned long long height_;
	unsigned long long depth_;
	unsigned long long size_;
};

