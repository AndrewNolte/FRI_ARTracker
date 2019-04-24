#ifndef ROS_INFO_POSE_RECIPIENT_H
#define ROS_INFO_POSE_RECIPIENT_H

#include "hw5/PoseRecipient.h"
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>

class TFBroadcastPR : public PoseRecipient {
protected:
  ros::Publisher pub_pose;
  tf::TransformBroadcaster br;

public:
  TFBroadcastPR(std::string topic_out, ros::NodeHandle *node);

  void receivePose(const geometry_msgs::Pose &pose);

protected:
};

#endif
