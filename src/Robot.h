#ifndef _ROBOT_H_
#define _ROBOT_H_

class Robot
{
	public:
		void moveForward();
		void update();
	private:
		enum Mode
		{
			NONE,
			FORWARD,
			BACKWARD,
			ATTACK
		};
		
		Mode currentMode;
		
};

#endif
