#include "ros/ros.h"
#include "hw5/AlvarMarker.h"
#include "hw5/NavFixPR.h"
#include "hw5/NavPR.h"
#include "hw5/OffsetFlipPR.h"
#include "hw5/OffsetPR.h"
#include "hw5/OffsetR.h"
#include "hw5/OffsetTR.h"
#include "hw5/ROSINFOPoseRecipient.h"
#include "hw5/SplitterPR.h"

#include "hw5/TFBroadcastPR.h"

#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

//This file *also* has been modified, but can serve as a starting point
int main(int argc, char **argv) {
  ros::init(argc, argv, "hw5_nav_node");
  ros::NodeHandle n;

  tf::TransformListener tf_l;
  NavPR navPR(tf_l, ac);

  AlvarMarker am(n, tf_l, offPR, "camera_rgb_optical_frame");    //Kinect connected to computer
  // AlvarMarker am(n, tf_l, navPR, "nav_kinect_rgb_optical_frame");  //Kinect on robot

  ros::AsyncSpinner spinner(1);
  spinner.start();
  ros::waitForShutdown();

  return 0;
}
