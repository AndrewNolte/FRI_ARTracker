#include "ros/ros.h"
#include "hw5/TFBroadcastPR.h"
#include <iostream>
#include "geometry_msgs/PoseStamped.h"

TFBroadcastPR::TFBroadcastPR(std::string topic_out, ros::NodeHandle *node) 
  : pub_pose(node->advertise<geometry_msgs::PoseStamped>(topic_out, 1)) {


}

void TFBroadcastPR::receivePose(const geometry_msgs::Pose &pose) {
  std::cout << "published" << std::endl;

  geometry_msgs::PoseStamped newPose;

  newPose.header.frame_id = "camera_rgb_frame";
  newPose.header.stamp = ros::Time();

  newPose.pose.position.x = pose.position.x;
  newPose.pose.position.y = pose.position.y;
  newPose.pose.position.z = pose.position.z+1;

  pub_pose.publish(newPose);

  // tf::Transform transform;
  // transform.setOrigin( tf::Vector3(pose.position.x, pose.position.y, pose.position.z) );

  // tf::Quaternion q;
  // q.setRPY(0, 0, 0);
  // transform.setRotation(q);
  // br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "camera_link", "camera_link_transformed"));
}
