#include "ProducerThread.h"
#include "WriterThread.h"

ProducerThread::ProducerThread(int bufsize, MicroscopeManager* mm) :
	producerIndex(0),
	bufSize(bufsize),
	mm_(mm),
	lastWriterID(0)
{}

ProducerThread::~ProducerThread()
{
	{
		std::unique_lock<std::mutex> ul(pMutex);
		for (int i = 0; i < writerThreads_.size(); i++)
		{
			writerThreads_[i]->StopThread();
			bufReadys[i] = true;
		}
	}
	pCV.notify_all();
	
	for (WriterThread* writer : writerThreads_)
	{
		writer->WaitForThread();
		delete writer;
	}
	writerThreads_.clear();

	for (unsigned char* buf : imgBuffers)
	{
		VirtualFree(buf, 0, MEM_RELEASE);
	}
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
	imgBuffers.push_back((unsigned char*)VirtualAlloc(NULL, bufSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
	bufReadys.push_back(false);
}

void ProducerThread::ProducerLoop()
{
	while (active)
	{
		{
			std::unique_lock<std::mutex> ul(pMutex);
			
			if (bufReadys[producerIndex])
			{
				pCV.wait(ul, [this]() {return !bufReadys[producerIndex]; });
			}

			//masked = false;
			mm_->GetImage();
			//mm_->ApplyCameraMask();
			//masked = true;

			memcpy(imgBuffers[producerIndex], mm_->GetImageBuffer(), bufSize);
			bufReadys[producerIndex] = true;

			producerIndex++;
			if (producerIndex == writerThreads_.size())
			{
				producerIndex = 0;
			}
		}
		pCV.notify_all();
	}
}
