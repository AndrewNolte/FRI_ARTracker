#include "NavPR.h"
#include <math.h>
#include <tf/tf.h>

NavPR::NavPR(MoveBaseClient &ac) {
	actionClient = ac;
}

void NavPR::navCb(geometry_msgs::PoseStamped &pose) {
	// Determine quaternion orientation to turn to
	double turnAngle = atan2(pose.pose.position.x, pose.pose.position.y);
	tf::Quaternion quat;
	quat.setRPY(0, 0, turnAngle);
	geometry_msgs::Quaternion goalOrientation;
	tf::quaternionTFToMsg(quat, goalOrientation);

	// Turn to face marker
	geometry_msgs::PoseStamped turnPose;
	turnPose.position.x = 0;
	turnPose.position.y = 0;
	turnPose.position.z = 0;
	turnPose.orientation = goalOrientation;
	turnPose.header = pose.header;

	move_base_msgs::MoveBaseGoal turnGoal;
	turnGoal.pose = turnPose;
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
	goal.pose = goalPose;
	actionClient.sendGoal(goal);
	actionClient.waitForResult();
}
