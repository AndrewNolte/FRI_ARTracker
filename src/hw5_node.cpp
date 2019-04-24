#include "ros/ros.h"
#include "hw5/AlvarMarker.h"
#include "hw5/TFBroadcastPR.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "hw5_node");

  ros::NodeHandle n;
  tf::TransformListener tfl;
  TFBroadcastPR broadcaster("translated_marker", &n, nullptr);

  AlvarMarker am(n, tfl, broadcaster, "camera_rgb_frame");

  ros::AsyncSpinner spinner(1);
  spinner.start();
  ros::waitForShutdown();

  return 0;
}
