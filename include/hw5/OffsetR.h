#ifndef ROS_INFO_POSE_RECIPIENT_H
#define ROS_INFO_POSE_RECIPIENT_H

#include "PoseRecipient.h"

class OffsetR : public PoseRecipient {
public:
  void receivePose(geometry_msgs::Pose &pose);

};

#endif
