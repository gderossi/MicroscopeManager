#include "MMThread.h"

MMThread::~MMThread()
{

}

MMThread::MMThread() :
	active(true)
{}

void MMThread::StopThread()
{
	active = false;
}
