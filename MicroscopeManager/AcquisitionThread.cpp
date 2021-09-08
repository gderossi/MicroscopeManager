#include "AcquisitionThread.h"

AcquisitionThread::AcquisitionThread(unsigned long long bufferCount, MicroscopeManager* mm) :
	bufferCount_(bufferCount),
	mm_(mm),
	thd_(&AcquisitionThread::Acquire, this)
{}

void AcquisitionThread::Acquire()
{
	while (active)
	{
		mm_->GetImage();
		mm_->WriteFile(mm_->GetImageBuffer(), mm_->GetImageBufferSize());

		if (--bufferCount_ == 0)
		{
			active = false;
		}
	}
}

void AcquisitionThread::WaitForThread()
{
	thd_.join();
}