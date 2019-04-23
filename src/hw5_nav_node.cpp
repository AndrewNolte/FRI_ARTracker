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

  std::cout << "Contacting robot base..." << std::endl;

  MoveBaseClient ac("move_base", true);
  while(!ac.waitForServer(ros::Duration(5.0)));

  std::cout << "Building PR chain..." << std::endl;

  std::string tfbTopicName = "transformed_marker";

  TFBroadcastPR tfb(tfbTopicName, &node);
  tf::TransformListener tfl;
  AlvarMarker am(node, tfl, tfb, "nav_kinect_rgb_optical_frame");

  NavPR navPr(ac, &node);
  node.subscribe(tfbTopicName, 1, &NavPR::navCb, &navPr);

  std::cout << "Spinning up..." << std::endl;

  ros::AsyncSpinner spinner(1);
  spinner.start();
  ros::waitForShutdown();

  return 0;
}
