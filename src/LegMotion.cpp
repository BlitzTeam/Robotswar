#include "LegMotion.h"

LegMotion::LegMotion(...)
{
	// TODO
}

float* LegMotion::getCurrentPosition()
{
	float* res = new float[3];
	for (int i = 0; i < 3; i++)
		res[i] = LegMotion::interpolate(start[i], end[i], timer.completionRate());
}

void LegMotion::start()
{
	timer.start();
}

bool LegMotion::isDone()
{
	return timer.isDone();
}

float interpolate(float start, float end, float completionRate)
{
	return start + (end - start) * completionRate;
}
