#include "rasp_ard_serial.h"
#include <ros.h>
#include "vector4_msg.h"

namespace rasp_ard_serial{

  // Initialize ROS node handler and a subscriber of "wheel_ang_vels" topic
  Mecanum4Wheels::Mecanum4Wheels() : wheel_ang_vel_topic("wheel_ang_vels", &Mecanum4Wheels::wheel_ang_vels_callback, this){
    nodeHandler.initNode();
    nodeHandler.subscribe(wheel_ang_vel_topic);
  }

  // Continuously check for new data in "wheel_ang_vels" topic.
  void Mecanum4Wheels::Loop(){
    nodeHandler.spinOnce();
  }

  // Callback function of "wheel_ang_vels" topic
  void Mecanum4Wheels::wheel_ang_vels_callback(const mecanum_ik::vector4_msg& msg){
    wheel_ang_vels = msg; // save received data.
  }

  // Get angular speeds of the 4 motors.
  mecanum_ik::vector4_msg Mecanum4Wheels::getWheelAngVels(){
    return wheel_ang_vels;  // Return a 4D vector (x, y, z, w)
  }

  // Get top left motor's angular speed.
  float Mecanum4Wheels::getTopLeftWheel(){
    return wheel_ang_vels.x;
  }

  // Get top right motor's angular speed.
  float Mecanum4Wheels::getTopRightWheel(){
    return wheel_ang_vels.y;
  }

  // Get bottom right motor's angular speed.
  float Mecanum4Wheels::getBottomRightWheel(){
    return wheel_ang_vels.z;
  }

  // Get bottom left motor's angular speed.
  float Mecanum4Wheels::getBottomLeftWheel(){
    return wheel_ang_vels.w;
  }
}