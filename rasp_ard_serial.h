#include <ros.h>
#include "vector4_msg.h"

#ifndef RASP_ARD_SERIAL_H
#define RASP_ARD_SERIAL_H

namespace rasp_ard_serial{
  // This class initialize and run ROS serial on Arduino.
  // Subscribe to "/wheel_ang_vels" topic whose construct includes
  //  float x   // angular velocity of top left wheel
  //  float y   // angular velocity of top right wheel
  //  float z   // angular velocity of bottom right wheel
  //  float w   // angular velocity of bottom left wheel
  // The class has methods to get all wheel's velocities and individual velocity;
  class Mecanum4Wheels{
    private:
      mecanum_ik::vector4_msg wheel_ang_vels;   // Holds motors' angular speed
      ros::Subscriber<mecanum_ik::vector4_msg, Mecanum4Wheels> wheel_ang_vel_topic; // subscriber holder
      ros::NodeHandle nodeHandler;  // ROS handler
    public:
      Mecanum4Wheels();
      void Loop();
      mecanum_ik::vector4_msg getWheelAngVels();
      void wheel_ang_vels_callback(const mecanum_ik::vector4_msg& msg);
      float getTopLeftWheel();
      float getTopRightWheel();
      float getBottomRightWheel();
      float getBottomLeftWheel();
  };
}
#endif