#ifndef _ROS_mecanum_ik_vector4_msg_h
#define _ROS_mecanum_ik_vector4_msg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mecanum_ik
{

  class vector4_msg : public ros::Msg
  {
    public:
      typedef float _x_type;
      _x_type x;
      typedef float _y_type;
      _y_type y;
      typedef float _z_type;
      _z_type z;
      typedef float _w_type;
      _w_type w;

    vector4_msg():
      x(0),
      y(0),
      z(0),
      w(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->x);
      offset += serializeAvrFloat64(outbuffer + offset, this->y);
      offset += serializeAvrFloat64(outbuffer + offset, this->z);
      offset += serializeAvrFloat64(outbuffer + offset, this->w);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->x));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->y));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->z));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->w));
     return offset;
    }

    virtual const char * getType() override { return "mecanum_ik/vector4_msg"; };
    virtual const char * getMD5() override { return "a779879fadf0160734f906b8c19c7004"; };

  };

}
#endif
