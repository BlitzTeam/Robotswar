#include "Leg.h"
#include <cmath>

Leg::Leg(LegType type, uint8_t* servos) : type(type)
{
	servo_count = type == FRONT ? 3 : 2;
}

Leg::~Leg()
{
	delete servos;
}

void Leg::scheduleMotions()
{
	// TODO
}

void Leg::update()
{
	timer.tick();
	
	if (motions[currentMotion].isDone())
	{
		currentMotion = (currentMotion + 1) % LEG_MOTION_COUNT;
		motions[currentMotion].start();
	}
	float* positions = motions[currentMotion].getCurrentPosition();
	float* angles = positionToAngle(positions[0],positions[1],positions[2]);
	
	for (int i = 0; i < servo_count; i++)
		servos_command(servos[i], angles[i]);
	
	delete angles;
	delete positions;
}

float* Leg::positionToAngle(float x, float y, float z)
{
	switch(type)
	{
		case FRONT:
			float* res = new float[3];
			float p = cmath::sqrt(x * x + y * y);
			float alpha = cmath::atan2(y / x);
			float l = cmath::sqrt(z*z + p*p);
			float gamma = cmath::acos((a * a + b * b - l * l) / (2 * a * b));
			float beta = cmath::acos((a * a + l * l - b * b) / (2 * a * l));
			res[0] = alpha;
			res[1] = beta;
			res[2] = gamma;
			return res;
		case BACK:
			float* res = new float[2];
			float p = x;
			float l = cmath::sqrt(z*z + p*p);
			float gamma = cmath::acos((a * a + b * b - l * l) / (2 * a * b));
			float beta = cmath::acos((a * a + l * l - b * b) / (2 * a * l));
			res[0] = beta;
			res[1] = gamma;
			return res;
	}	
}

