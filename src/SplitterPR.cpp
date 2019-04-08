#include "hw5/SplitterPR.h"

SplitterPR::SplitterPR(PoseRecipient &a, PoseRecipient &b) : _a(a), _b(b) {}

void SplitterPR::receivePose(geometry_msgs::Pose &pose) {
  _a.receivePose(pose);
  _b.receivePose(pose);
}
