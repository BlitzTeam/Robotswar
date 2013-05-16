#include "Robot.h"

Robot::Robot() : currentMode(NONE)
{
}

Robot::moveForward()
{
	currentMove = FORWARD;
}

Robot::update()
{
	switch(currentMode)
	{
		case FORWARD:
							
	}
}
