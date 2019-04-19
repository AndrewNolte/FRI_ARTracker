#include "hw5/NavPR.h"
#include <math.h>
#include <tf/tf.h>

NavPR::NavPR(MoveBaseClient &ac) : actionClient(ac) {}

void NavPR::receivePose(const geometry_msgs::Pose &pose) {}

void NavPR::navCb(const geometry_msgs::PoseStamped &pose) {
	/*// Determine quaternion orientation to turn to
	double turnAngle = atan2(pose.pose.position.y, pose.pose.position.x);
	tf::Quaternion quat;
	quat.setRPY(0, 0, turnAngle);
	geometry_msgs::Quaternion goalOrientation;
	tf::quaternionTFToMsg(quat, goalOrientation);

	// Turn to face marker
	geometry_msgs::PoseStamped turnPose;
	turnPose.pose.position.x = 0;
	turnPose.pose.position.y = 0;
	turnPose.pose.position.z = 0;
	turnPose.pose.orientation = goalOrientation;
	turnPose.header = pose.header;

	move_base_msgs::MoveBaseGoal turnGoal;
	turnGoal.target_pose = turnPose;
	actionClient.sendGoal(turnGoal);
	actionClient.waitForResult();

	// Navigate to pose
	geometry_msgs::PoseStamped goalPose;
	goalPose.pose.position.x = pose.pose.position.x;
	goalPose.pose.position.y = pose.pose.position.y;
	goalPose.pose.position.z = 0;
	goalPose.pose.orientation = pose.pose.orientation;
	goalPose.header = pose.header;

	move_base_msgs::MoveBaseGoal goal;
	goal.target_pose = goalPose;
	actionClient.sendGoal(goal);
	actionClient.waitForResult();*/

	geometry_msgs::PoseStamped goalPose;
	goalPose.pose.position.x = 0.25;
	goalPose.pose.position.y = 0;
	goalPose.pose.position.z = 0;
	goalPose.pose.orientation = pose.orientation;

	move_base_msgs::MoveBaseGoal moveGoal;
	moveGoal.target_pose = goalPose;
	actionClient.sendGoal(moveGoal);
	actionClient.waitForResult();
}
