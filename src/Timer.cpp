#include "Timer.h"
#include <ctime>

Timer::Timer(long duration) : duration(duration)
{
	this->startTime = ctime::time(NULL);
}