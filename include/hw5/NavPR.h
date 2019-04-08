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
  NavPR(tf::TransformListener &tfL, MoveBaseClient &ac);

  void receivePose(geometry_msgs::Pose &pose);

protected:
  MoveBaseClient &_ac;
  tf::TransformListener &_tfL;
};

#endif
