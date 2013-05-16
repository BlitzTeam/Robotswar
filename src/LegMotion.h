#ifndef _LEGMOTION_H_
#define _LEGMOTION_H_

class LegMotion
{
	public:
		LegMotion(float startX, float startY, float startZ, float endX, float endY, float endZ, long duration);
		float* getCurrentPosition();
		void start();
		bool isDone();
	private:
		static float interpolate(float start, float end, long duration, long currentTime);
		Timer timer;
		float[3] start;
		float[3] end;
};

#endif
