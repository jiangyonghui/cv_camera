// Copyright [2015] Takashi Ogura<t.ogura@gmail.com>

#include "cv_camera/driver.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "cv_camera");
  ros::NodeHandle private_node("~");
  cv_camera::Driver driver(private_node, private_node);
  
  bool wait_for_subscriber = false;
  private_node.getParam("wait_for_subscriber", wait_for_subscriber);
  
  try
  {
    driver.setup();
    while (ros::ok())
    {
      if (wait_for_subscriber)
      {
        if (driver.getNumSubscribers()) {driver.proceed();}
        else {ROS_WARN_ONCE("No subscribers connected!");}
      }
      else {driver.proceed();}
      
      ros::spinOnce();
    }
  }
  catch (cv_camera::DeviceError &e)
  {
    ROS_ERROR_STREAM("cv camera open failed: " << e.what());
    return 1;
  }

  return 0;
}
