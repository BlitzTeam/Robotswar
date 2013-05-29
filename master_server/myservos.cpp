#include <servos.h>
#include "myservos.h"

void servos_register_all()
{
	servos_register(5, "BR1");
	servos_calibrate(0, 4320, 7050, 7050, true);
	servos_register(8, "BR2");
	servos_calibrate(1, 2640, 6100, 7245, true);
	servos_register(11, "BL1");
	servos_calibrate(2, 1920, 2300, 5130, false);
	servos_register(3, "BL2");
	servos_calibrate(3, 1560, 2500, 6150, false);
	servos_register(4, "FM1");
	servos_calibrate(4, 2190, 3978, 6772, false);
	servos_register(27, "FR0");
	servos_calibrate(5, 2010, 4500, 6039, false);
	servos_register(26, "FR1");
	servos_calibrate(6, 1920, 2920, 6960, true);
	servos_register(25, "FR2");
	servos_calibrate(7, 2010, 5060, 6908, false);
	servos_register(15, "FR3");
	servos_calibrate(8, 1920, 7377, 7377, false);
	servos_register(9, "FL0");
	servos_calibrate(9, 2280, 4500, 7038, false);
	servos_register(10, "FL1");
	servos_calibrate(10, 1920, 6200, 7200, false);
	servos_register(16, "FL2");
	servos_calibrate(11, 2280, 5129, 7038, true);
}
