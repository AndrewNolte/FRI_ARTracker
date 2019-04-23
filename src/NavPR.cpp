#include "hw5/NavPR.h"
#include <math.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>

#include <iostream>

NavPR::NavPR(MoveBaseClient &ac, ros::NodeHandle *node) :
	actionClient(ac),
	pubGoalPose(node->advertise<geometry_msgs::PoseStamped>("follower_goal_pose", 1)) {}

void NavPR::receivePose(const geometry_msgs::Pose &pose) {
	std::cout << "NavPR callback triggered" << std::endl;

	// Determine quaternion orientation to turn to
	/*double turnAngle = atan2(pose.pose.position.y, pose.pose.position.x);
	tf::Quaternion quat;
	quat.setRPY(0, 0, turnAngle * 0.25);
	geometry_msgs::Quaternion goalOrientation;
	tf::quaternionTFToMsg(quat, goalOrientation);*/

	// Determine position to drive to
	geometry_msgs::PoseStamped goalPose;
	goalPose.pose.position.x = pose.position.x;
	goalPose.pose.position.y = pose.position.y;
	goalPose.pose.position.z = pose.position.z;

	move_base_msgs::MoveBaseGoal goal;
	goal.target_pose = goalPose;
	
	goal.target_pose.header.frame_id = "base_link";
	goal.target_pose.header.stamp = ros::Time::now();
	
	double angle = atan2(pose.position.z, pose.position.x);
  tf::Quaternion direction;
  direction.setRPY(0, 0, 0.2 * angle);
  goal.target_pose.pose.orientation.w = direction.w();
 	goal.target_pose.pose.orientation.x = direction.x();
  goal.target_pose.pose.orientation.y = direction.y();
  goal.target_pose.pose.orientation.z = direction.z();
	
	actionClient.sendGoal(goal);
	actionClient.waitForResult();
}

void NavPR::navCb(const geometry_msgs::PoseStamped &pose) {
	std::cout << "NavPR callback triggered" << std::endl;

	// Determine quaternion orientation to turn to
	/*double turnAngle = atan2(pose.pose.position.y, pose.pose.position.x);
	tf::Quaternion quat;
	quat.setRPY(0, 0, turnAngle * 0.25);
	geometry_msgs::Quaternion goalOrientation;
	tf::quaternionTFToMsg(quat, goalOrientation);*/

	// Determine position to drive to
	geometry_msgs::PoseStamped goalPose;
	goalPose.pose.position.x = pose.pose.position.x;
	goalPose.pose.position.y = pose.pose.position.y;
	goalPose.pose.position.z = 0;
	goalPose.pose.orientation = pose.pose.orientation;
	goalPose.header = pose.header;

	// Transform pose to robot frame
	/*tf::TransformListener listener;

	tf::StampedTransform transform;
	listener.lookupTransform("camera_link", "base_link", ros::Time(0), transform);
	transformPose(transform, goalPose);

	pubGoalPose.publish(goalPose);*/

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
