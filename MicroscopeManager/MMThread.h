#pragma once

#include <thread>
#include <atomic>

class MMThread
{
public:
	MMThread();
	virtual ~MMThread();
	virtual void WaitForThread() = 0;
	virtual void StopThread();

protected:
	std::atomic_bool active;
};

