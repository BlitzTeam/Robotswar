#ifndef _TIMER_H_
#define _TIMER_H_

class Timer
{
	private:
		long startTime;
		long duration;

	public:
		Timer(long duration);
		long elapsedTime();
		bool isDone();
};

#endif

