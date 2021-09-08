#pragma once

#include "MMThread.h"
#include "MicroscopeManager.h"

class AcquisitionThread :
	public MMThread
{
public:
	AcquisitionThread(unsigned long long bufferCount, MicroscopeManager* mm);
	void WaitForThread();

private:
	void Acquire();

	unsigned long long bufferCount_;
	std::thread thd_;
	MicroscopeManager* mm_;
};

