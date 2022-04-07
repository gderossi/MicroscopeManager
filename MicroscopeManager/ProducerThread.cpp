#include "ProducerThread.h"
#include "WriterThread.h"

ProducerThread::ProducerThread(int bufsize, MicroscopeManager* mm) :
	currentID(0),
	buf(new unsigned char[bufsize]),
	bufSize_(bufsize),
	bufCopied(false),
	mm_(mm)
{
	
}

ProducerThread::~ProducerThread()
{
	delete buf;
	for (WriterThread* writer : writerThreads_)
	{
		delete writer;
	}
	writerThreads_.clear();
}

void ProducerThread::StartThread()
{
	thd_ = std::thread(&ProducerThread::ProducerLoop, this);
}

void ProducerThread::WaitForThread()
{
	thd_.join();
}

void ProducerThread::AddWriterThread(WriterThread* writer)
{
	writerThreads_.push_back(writer);
}

void ProducerThread::ProducerLoop()
{
	while (active)
	{
		std::unique_lock<std::mutex> ul(pMutex);
		currentID++;
		if (currentID == writerThreads_.size())
		{
			currentID = 0;
		}
		bufCopied = false;
		masked = false;
		mm_->GetImage();
		mm_->ApplyCameraMask();
		masked = true;
		memcpy(buf, mm_->GetImageBuffer(), bufSize_);
		ul.unlock();
		pCV.notify_all();
		ul.lock();
		pCV.wait(ul, [this]() {return bufCopied; });
	}

}
