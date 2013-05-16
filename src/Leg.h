#ifndef _LEG_H_
#define _LEG_H_

class Leg
{
	public:
		void scheduleMove();
		void update();
	private:
		float* positionToAngle(float x, float y, float z);
		float a;
		float b;
		
};

#endif
