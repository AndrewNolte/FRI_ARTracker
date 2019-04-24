#include "ros/ros.h"
#include "hw5/TFBroadcastPR.h"
#include <iostream>
#include "geometry_msgs/PoseStamped.h"
#include <Eigen/Dense>
#include "hw5/PoseRecipient.h"

TFBroadcastPR::TFBroadcastPR(std::string topic_out, ros::NodeHandle *node)
  : pub_pose(node->advertise<geometry_msgs::PoseStamped>(topic_out, 1)) {}

// Receives a pose from Alvar
void TFBroadcastPR::receivePose(const geometry_msgs::Pose &pose) {
  std::cout << "TFBroadcastPR callback triggered" << std::endl;

  // Translate 1 meter along the z axis
  Eigen::Quaterniond rot(pose.orientation.w, pose.orientation.x, pose.orientation.y, pose.orientation.z);
  Eigen::MatrixXd newPoseRotated(3, 1);
  newPoseRotated(0, 0) = 0;
  newPoseRotated(1, 0) = 0;
  newPoseRotated(2, 0) = 1;

  // Rotate 1 meter translation to marker orientation
  newPoseRotated = rot.normalized().toRotationMatrix() * newPoseRotated;

  // Add translation to transformation in progress
  geometry_msgs::PoseStamped newPose;
  newPose.header.frame_id = "camera_link";
  newPose.header.stamp = ros::Time();
  newPose.pose.position.x = newPoseRotated(0,0) + pose.position.x;
  newPose.pose.position.y = newPoseRotated(1,0) + pose.position.y;
  newPose.pose.position.z = newPoseRotated(2,0) + pose.position.z;

  // Flip pi radians around the z axis
  Eigen::MatrixXd zAxis(3, 1);
  zAxis << 0, 1, 0;
  Eigen::Quaterniond newPoseOrientation(pose.orientation.w, pose.orientation.x, pose.orientation.y, pose.orientation.z);
  Eigen::AngleAxisd rZ(3.14159, zAxis);
  newPoseOrientation = rZ * newPoseOrientation;

  newPose.pose.orientation.x = newPoseOrientation.x();
  newPose.pose.orientation.y = -newPoseOrientation.y();
  newPose.pose.orientation.z = newPoseOrientation.z();
  newPose.pose.orientation.w = -newPoseOrientation.w();

  pub_pose.publish(newPose);
}
