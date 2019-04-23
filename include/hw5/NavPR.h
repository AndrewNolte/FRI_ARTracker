#ifndef NAV_PR_H
#define NAV_PR_H

#include "PoseRecipient.h"


#include <tf/tf.h>
#include <tf/transform_listener.h>

#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include <Eigen/Geometry>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class NavPR : public PoseRecipient {
public:
  NavPR(MoveBaseClient &ac,  ros::NodeHandle*pose);

  void receivePose(const geometry_msgs::Pose &pose);

  void navCb(const geometry_msgs::PoseStamped &pose);

  void transformPose(tf::StampedTransform &transform, geometry_msgs::PoseStamped &pose);

protected:
  MoveBaseClient &actionClient;
  ros::Publisher pubGoalPose;
};

#endif
