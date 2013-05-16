#ifndef _TIMER_H_
#define _TIMER_H_

class Timer
{
	private:
		long elapsedTime;
		long duration;

	public:
		Timer(long duration);
		void start();
		void tick();
		void setDuration(long duration);
		long getElapsedTime();
		float completionRate();
		bool isDone();
};

#endif

