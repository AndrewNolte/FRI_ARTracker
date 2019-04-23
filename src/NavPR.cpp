#include "hw5/NavPR.h"
#include <math.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>

#include <iostream>

NavPR::NavPR(MoveBaseClient &ac, ros::NodeHandle *node) :
	actionClient(ac),
	pubGoalPose(node->advertise<geometry_msgs::PoseStamped>("follower_goal_pose", 1)) {}

void NavPR::receivePose(const geometry_msgs::Pose &pose) {}

void NavPR::navCb(const geometry_msgs::PoseStamped &pose) {
	std::cout << "NavPR callback triggered" << std::endl;

	// Determine quaternion orientation to turn to
	double turnAngle = atan2(pose.pose.position.y, pose.pose.position.x);
	tf::Quaternion quat;
	quat.setRPY(0, 0, turnAngle);
	geometry_msgs::Quaternion goalOrientation;
	tf::quaternionTFToMsg(quat, goalOrientation);

	// Determine position to drive to
	geometry_msgs::PoseStamped goalPose;
	goalPose.pose.position.x = pose.pose.position.x;
	goalPose.pose.position.y = pose.pose.position.y;
	goalPose.pose.position.z = 0;
	goalPose.pose.orientation = goalOrientation;
	goalPose.header = pose.header;

	// Transform pose to robot frame
	tf::TransformListener listener;

	tf::StampedTransform transform;
	listener.lookupTransform("camera_rgb_link", "base_link", ros::Time(0), transform);
	transformPose(transform, goalPose);

	pubGoalPose.publish(goalPose);

	move_base_msgs::MoveBaseGoal goal;
	goal.target_pose = goalPose;
	actionClient.sendGoal(goal);
	actionClient.waitForResult();
}

void NavPR::transformPose(tf::StampedTransform &transform, geometry_msgs::PoseStamped &pose) {
	// Translate
	tf::Vector3 tfOrigin = transform.getOrigin();

	Eigen::MatrixXd position(3, 1);
	position << pose.pose.position.x, pose.pose.position.y, pose.pose.position.z;

	position(0, 0) += tfOrigin.getX();
	position(1, 0) += tfOrigin.getY();
	position(2, 0) += tfOrigin.getZ();

	// Rotate
	tf::Quaternion tfQuat = transform.getRotation();
	geometry_msgs::Quaternion rosQuat;
	tf::quaternionTFToMsg(tfQuat, rosQuat);
	Eigen::Quaterniond rot(rosQuat.w, rosQuat.x, rosQuat.y, rosQuat.z);

	position = rot.normalized().toRotationMatrix() * position;

	// Update pose reference
	pose.pose.position.x = position(0, 0);
	pose.pose.position.y = position(1, 0);
	pose.pose.position.z = position(2, 0);
}
