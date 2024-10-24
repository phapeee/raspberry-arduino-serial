#include <rasp_ard_serial.h>
#include <mecanum_ik/vector4_msg.h>
#include <PWM_16kHz.h>
using namespace PWM;

// PWM1A = pin 9
// PWM1B = pin 10
// PWM2A = pin 11
// PWM2B = pin 3

// Initialize raspberry-arduino serial communication.
// The class subscribes to "wheel_ang_vels" topic.
rasp_ard_serial::Mecanum4Wheels mecanum_Wheels; 

void setup() {
  Serial.begin(57600);    // set baurate for ROS communication
  init_16kHz_PWM();       // initialize 16kHz PWM at pin 3, 9, 10, and 11
}

void loop() {
  mecanum_Wheels.Loop();  // run ROS.

  mecanum_ik::vector4_msg wheel_ang_vels = mecanum_Wheels.getWheelAngVels();  // Get all motors's speed as 4D vector;
  setDuty(PWM1A, mapLED(wheel_ang_vels.x)); // Top left motor
  setDuty(PWM1B, mapLED(wheel_ang_vels.w)); // Bottom left motor
  setDuty(PWM2A, mapLED(wheel_ang_vels.z)); // Bottom Right motor
  setDuty(PWM2B, mapLED(wheel_ang_vels.y)); // Top right motor

  // This is another way to set the wheel's angular velocities.
  // setDuty(PWM1A, mapLED(mecanum_Wheels.getTopLeftWheel()));
  // setDuty(PWM1B, mapLED(mecanum_Wheels.getBottomLeftWheel()));
  // setDuty(PWM2A, mapLED(mecanum_Wheels.getBottomRightWheel()));
  // setDuty(PWM2B, mapLED(mecanum_Wheels.getTopRightWheel()));


  // ********** Testing PWM signal **********
  // static float i = 0;
  // static char dir = 1;

  // i += (float) 1 * dir;

  // setDuty(PWM1A, i);
  // setDuty(PWM1B, i);
  // setDuty(PWM2A, i);
  // setDuty(PWM2B, i);

  // if (i >= 100) dir = -1;
  // if (i <= 0) dir = 1;

  // delay(100);
  // ****************************************
}

// Mapping velocity to % duty between 0 and 100
// This function is for testing only.
int mapLED(float vel){
  return (int) -exp(log(100)-10*pow(vel, 2)) + 100;
}
