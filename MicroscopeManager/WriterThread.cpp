#include "WriterThread.h"

WriterThread::WriterThread(std::string filename, unsigned int bufsize, int id, ProducerThread* producer, ImageManager* img) :
	filename_(filename),
	buf_(new unsigned char(bufsize)),
	bufsize_(bufsize),
	id_(id),
	img_(img),
	producer_(producer)
{
	thd_= std::thread(&WriterThread::WriteLoop, this);
}

WriterThread::~WriterThread()
{
	delete buf_;

	if (img_)
	{
		delete img_;
	}
}

void WriterThread::WaitForThread()
{
	thd_.join();
}

void WriterThread::WriteLoop()
{
	if (img_)
	{
		while (active)
		{
			std::unique_lock<std::mutex> ul(producer_->pMutex);
			producer_->pCV.wait(ul, [this]() {return (producer_->currentID == id_); });
			memcpy(buf_, producer_->buf, bufsize_);
			producer_->bufCopied = true;
			ul.unlock();
			producer_->pCV.notify_all();

			//write to file
			img_->WriteFile(buf_, bufsize_);
		}
	}
}