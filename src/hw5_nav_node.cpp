#include "ros/ros.h"
#include "hw5/AlvarMarker.h"
#include "hw5/TFBroadcastPR.h"
#include "hw5/NavPR.h"
#include <iostream>

#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

int main(int argc, char **argv) {
  std::cout << "In startup..." << std::endl;

  ros::init(argc, argv, "hw5_nav_node");
  ros::NodeHandle node;
  // TFBroadcastPR tfb("translated_marker", &node);

  std::cout << "Contacting robot base..." << std::endl;

  // Wait while connection with base is established
  MoveBaseClient ac("move_base", true);
  while(!ac.waitForServer(ros::Duration(5.0)));

  std::cout << "Building subscribers..." << std::endl;

  NavPR navPr(ac, &node);
  // ros::Subscriber sub = node.subscribe("translated_marker", 1, &NavPR::navCb, &navPr);
  tf::TransformListener tfl;
  AlvarMarker am(node, tfl, navPr, "nav_kinect_rgb_optical_frame");
  // AlvarMarker am(node, tfl, tfb, "camera_rgb_frame");

  std::cout << "Spinning up..." << std::endl;

  ros::AsyncSpinner spinner(1);
  spinner.start();
  ros::waitForShutdown();

  return 0;
}
