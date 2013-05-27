#define SERVO_BR1 0
#define SERVO_BR2 2
#define SERVO_BL1 3
#define SERVO_BL2 4
#define SERVO_FM1 5
#define SERVO_FR1 6
#define SERVO_FR2 7
#define SERVO_FR3 8
#define SERVO_FR4 9
#define SERVO_FL1 10
#define SERVO_FL2 11
#define SERVO_FL3 12
servos_register(5, "BR1");
servos_calibrate(0, 3630, 4407, 7251, false);
servos_register(0, "8");
servos_calibrate(1, 0, 3000, 60000, false);
servos_register(8, "BR2");
servos_calibrate(2, 2100, 4375, 6919, false);
servos_register(11, "BL1");
servos_calibrate(3, 2100, 4859, 5813, false);
servos_register(3, "BL2");
servos_calibrate(4, 2010, 4124, 6908, false);
servos_register(4, "FM1");
servos_calibrate(5, 2190, 3978, 6772, false);
servos_register(27, "FR1");
servos_calibrate(6, 2010, 4699, 6039, false);
servos_register(26, "FR2");
servos_calibrate(7, 1920, 4385, 6960, false);
servos_register(25, "FR3");
servos_calibrate(8, 2010, 5060, 6908, false);
servos_register(15, "FR4");
servos_calibrate(9, 2010, 6908, 6908, false);
servos_register(9, "FL1");
servos_calibrate(10, 2280, 4255, 7038, false);
servos_register(10, "FL2");
servos_calibrate(11, 1920, 4730, 7200, false);
servos_register(16, "FL3");
servos_calibrate(12, 2280, 5129, 7038, false);

