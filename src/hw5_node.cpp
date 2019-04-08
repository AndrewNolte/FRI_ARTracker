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

//I have removed code from this file. This is for illustration only. You will need to modify it to make your code work.

int main(int argc, char **argv) {
  ros::init(argc, argv, "hw5_node");
  ros::NodeHandle n;

  tf::TransformListener tf_l;
  //ROSINFOPoseRecipient pr;
  TFBroadcastPR broadPR("camera_rgb_optical_frame", "offset");        //Kinect connected to computer
  TFBroadcastPR broadPRNavFix("camera_rgb_optical_frame", "offset_navfixed");  //Kinect on robot
  TFBroadcastPR broadPRFlip("camera_rgb_optical_frame", "offset_flipped");  //Kinect on robot
  // TFBroadcastPR broadPR("nav_kinect_rgb_optical_frame", "offset");  //Kinect on robot
  // TFBroadcastPR broadPRNavFix("nav_kinect_rgb_optical_frame", "offset_navfixed");  //Kinect on robot
  // TFBroadcastPR broadPRFlip("nav_kinect_rgb_optical_frame", "offset_flipped");  //Kinect on robot

  NavPR navPR(tf_l, ac);

  SplitterPR navSplitter(broadPRNavFix, navPR);

  NavFixPR navFixPR(tf_l, navSplitter, "ar_marker_0");
  SplitterPR secondSplitter(broadPRFlip, navFixPR);

  OffsetPR offPR(0, 0, 1, broadPR);
  OffsetFlipPR offFlipPR(0, 0, 1, secondSplitter);

  SplitterPR firstSplitter(offPR, offFlipPR);
  // AlvarMarker am(n, tf_l, firstSplitter, "nav_kinect_rgb_optical_frame");  //Kinect on robot



  ros::AsyncSpinner spinner(1);
  spinner.start();
  ros::waitForShutdown();

  return 0;
}
