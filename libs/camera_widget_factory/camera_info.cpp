#include "camera_info.h"


camera_info::~camera_info()
{

}

QString camera_info::description() const
{
   return descrip;
}

QString camera_info::deviceName() const
{
  return dev_name;
}

bool camera_info::isNull() const
{
   return false;
}

int camera_info::orientation() const
{
   return orient;
}

camera_position camera_info::position() const
{
   return (camera_position)pos;
}
