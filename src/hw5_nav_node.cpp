#include "hw5/AlvarMarker.h"
#include "hw5/NavPR.h"
#include "hw5/TFBroadcastPR.h"
#include "ros/ros.h"
#include <iostream>

#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>

int main(int argc, char** argv)
{
    // ROS startup
    std::cout << "In startup..." << std::endl;

    ros::init(argc, argv, "hw5_nav_node");
    ros::NodeHandle node;

    std::cout << "Contacting robot base..." << std::endl;

    // Connect to the base
    MoveBaseClient ac("move_base", true);
    while (!ac.waitForServer(ros::Duration(5.0)));

    std::cout << "Building PR chain..." << std::endl;

    // Proc Alvar and build PR chain
    NavPR navPr(ac, &node);
    tf::TransformListener tfl;
    AlvarMarker am(node, tfl, navPr, "nav_kinect_rgb_optical_frame");

    std::cout << "Ready to go!" << std::endl;

    ros::AsyncSpinner spinner(1);
    spinner.start();
    ros::waitForShutdown();

    return 0;
}
