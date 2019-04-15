#include "NavPR.h"

NavPR::NavPR(MoveBaseClient &ac) {
	_ac = ac;
}

void NavPR::nav_callback(geometry_msgs::PoseStamped &pose) {



	move_base_msgs::MoveBaseGoal goal;
	goal.target_pose = pose;

	//do stuff

	goal.target_pose.position.z = 0;

	


	ac.sendGoal(goal);
	ac.waitForResult();
}