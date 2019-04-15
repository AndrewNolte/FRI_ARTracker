#include "ros/ros.h"
#include "hw5/AlvarMarker.h"
#include "hw5/TFBroadcastPR.h"

#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

//This file *also* has been modified, but can serve as a starting point
int main(int argc, char **argv) {
  ros::init(argc, argv, "hw5_nav_node");
  ros::NodeHandle n;
  TFBroadcastPR tfb("translated_marker", &n);

  MoveBaseClient ac("move_base", true);
  while(!ac.waitForServer(ros::Duration(5.0)));

  NavPR navpr(ac);

  ros::Subscriber sub = node.subscribe("translated_marker", 1, &NavPr::nav_callback, &navpr);


  move_base_msgs::MoveBaseGoal goal
  AlvarMarker am(n, tf_l, navPR, "nav_kinect_rgb_optical_frame");

  ros::AsyncSpinner spinner(1);
  spinner.start();
  ros::waitForShutdown();

  return 0;
}
