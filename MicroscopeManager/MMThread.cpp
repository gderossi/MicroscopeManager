#include "MMThread.h"

MMThread::MMThread() :
	active(true)
{}

void MMThread::StopThread()
{
	active = false;
}
