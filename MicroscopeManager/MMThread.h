#pragma once

#include <thread>
#include <atomic>
#include <chrono>
#include <string>

struct MICROSCOPE_METADATA
{
	long long timestamp;
	char currentOdor;
	int planeCount;
	float volumeRange;
	char currentLaser;
	float laserPower;
	int cameraMode;
	char sampleInfo[478];
};

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

