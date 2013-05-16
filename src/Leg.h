#ifndef _LEG_H_
#define _LEG_H_

#define LEG_MOTION_COUNT 3

class Leg
{
	public:
		Leg(LegType type, uint8_t* servos);
		~Leg();
		void scheduleMove();
		void update();
		
	private:
		float* positionToAngle(float x, float y, float z);
		float a;
		float b;
		uint8_t[] servos;
		int servo_count;
		LegMotion[LEG_MOTION_COUNT] motions;
		int currentMotion;
};

#endif
