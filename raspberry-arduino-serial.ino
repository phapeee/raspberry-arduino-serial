#include "rasp_ard_serial.h"
#include "vector4_msg.h"

#define LED1        (3)   // 
#define LED2        (5)
#define LED3        (6)
#define LED4        (9)

// Initialize raspberry-arduino serial communication.
// The class subscribes to "wheel_ang_vels" topic.
rasp_ard_serial::Mecanum4Wheels mecanum_Wheels; 

void setup() {
  Serial.begin(57600);
}

void loop() {
  mecanum_Wheels.Loop();  // run ROS.

  // mecanum_ik::vector4_msg wheel_ang_vels = mecanum_Wheels.getWheelAngVels();  // Get all motors's speed as 4D vector;
  // analogWrite(LED1, mapLED(wheel_ang_vels.x); // Top left motor
  // analogWrite(LED2, mapLED(wheel_ang_vels.w); // Bottom left motor
  // analogWrite(LED3, mapLED(wheel_ang_vels.z); // Bottom Right motor
  // analogWrite(LED4, mapLED(wheel_ang_vels.y); // Top right motor

  analogWrite(LED1, mapLED(mecanum_Wheels.getTopLeftWheel()));
  analogWrite(LED2, mapLED(mecanum_Wheels.getBottomLeftWheel()));
  analogWrite(LED3, mapLED(mecanum_Wheels.getBottomRightWheel()));
  analogWrite(LED4, mapLED(mecanum_Wheels.getTopRightWheel()));
}

int mapLED(float vel){
  return (int) -exp(log(100)-pow(vel, 2)/2000.0) + 100;
}
