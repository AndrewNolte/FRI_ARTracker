#include "ros/ros.h"
#include "hw5/TFBroadcastPR.h"
#include <iostream>
#include "geometry_msgs/PoseStamped.h"
#include <Eigen/Dense>

TFBroadcastPR::TFBroadcastPR(std::string topic_out, ros::NodeHandle *node) 
  : pub_pose(node->advertise<geometry_msgs::PoseStamped>(topic_out, 1)) {}

void TFBroadcastPR::receivePose(const geometry_msgs::Pose &pose) {
  std::cout << "TFBroadcastPR callback triggered" << std::endl;

  Eigen::Quaterniond rot(pose.orientation.w, pose.orientation.x, pose.orientation.y, pose.orientation.z);
  Eigen::MatrixXd newPoseRotated(3, 1);
  newPoseRotated(0, 0) = 0;
  newPoseRotated(1, 0) = 0;
  newPoseRotated(2, 0) = 1;

  newPoseRotated = rot.normalized().toRotationMatrix() * newPoseRotated;

  geometry_msgs::PoseStamped newPose;
  newPose.header.frame_id = "camera_link";
  newPose.header.stamp = ros::Time();
  newPose.pose.position.x = newPoseRotated(0,0) + pose.position.x;
  newPose.pose.position.y = newPoseRotated(1,0) + pose.position.y;
  newPose.pose.position.z = newPoseRotated(2,0) + pose.position.z;

  Eigen::MatrixXd zAxis(3, 1);
  zAxis << 0, 1, 0;
  Eigen::Quaterniond newPoseOrientation(pose.orientation.w, pose.orientation.x, pose.orientation.y, pose.orientation.z);
  Eigen::AngleAxisd rZ(3.14159, zAxis);
  newPoseOrientation = rZ * newPoseOrientation;

  newPose.pose.orientation.x = newPoseOrientation.x();
  newPose.pose.orientation.y = -newPoseOrientation.y();
  newPose.pose.orientation.z = newPoseOrientation.z();
  newPose.pose.orientation.w = -newPoseOrientation.w();

  std::cout << newPose.pose.position.x << " " <<
               newPose.pose.position.y << " " <<
               newPose.pose.position.z << std::endl;

  pub_pose.publish(newPose);
}
