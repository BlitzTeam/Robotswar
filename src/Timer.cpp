#include "Timer.h"

Timer::Timer(long duration) : duration(duration), elapsedTime(0)
{
}

void Timer::start()
{
	elapsedTime = 0;
}

bool Timer::isDone()
{
	return elapsedTime >= duration;
}

long Timer::getElapsedTime()
{
	return elapsedTime;
}

void Timer::setDuration(long time)
{
	duration = time;
}

void Timer::tick()
{
	elapsedTime += 50;
}

float completionRate()
{
	return elapsedTime / duration;
}
