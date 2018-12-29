/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include "../include/pingfang_setgoals/qnode.hpp"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace pingfang_setgoals {

/*****************************************************************************
** Implementation
*****************************************************************************/

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

QNode::QNode(int argc, char** argv ) :
	init_argc(argc),
	init_argv(argv)
	{}

QNode::~QNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
	wait();
}

bool QNode::init() {
	ros::init(init_argc,init_argv,"pingfang_setgoals");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	//ros::NodeHandle n;
	// Add your ros communications here.
	//chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
	//start();
	return true;
}

bool QNode::init(const std::string &master_url, const std::string &host_url) {
	std::map<std::string,std::string> remappings;
	remappings["__master"] = master_url;
	remappings["__hostname"] = host_url;
	ros::init(remappings,"pingfang_setgoals");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	//ros::NodeHandle n;
	
	// Add your ros communications here.
	//chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
	//start();
	return true;
}

void QNode::run() {
	ros::Rate loop_rate(rate);
//	int count = 0;
	MoveBaseClient ac("move_base", true);
	while(!ac.waitForServer(ros::Duration(5.0))){
   		ROS_INFO("Waiting for the move_base action server to come up");
  	}
	
  	ROS_INFO("Sending goal");
  	ac.sendGoal(goal);

  	ac.waitForResult();

  	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
	{
    		ROS_INFO("Succeed");
		Q_EMIT isSucceed(true);
	}
  	else
	{
    		ROS_INFO("The base failed to the goals for some reason");
		Q_EMIT isSucceed(false);
	}

	while ( !ros::ok() )
	{
		std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
		Q_EMIT rosShutdown();
	}
	loop_rate.sleep();
	Q_EMIT isFinished();

 // 	return 0;
//	while ( ros::ok() ) {

//		std_msgs::String msg;
//		std::stringstream ss;
//		ss << "hello world " << count;
//		msg.data = ss.str();
//		chatter_publisher.publish(msg);
//		log(Info,std::string("I sent: ")+msg.data);
//		ros::spinOnce();
//		loop_rate.sleep();
//		++count;
//	}
//	std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
//	Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}

void QNode::addGoals(double px,double py,double pz ,double ox,double oy,double oz,double ow,double loop_rate)
{
	goal.target_pose.header.frame_id = "/map";
 	goal.target_pose.header.stamp = ros::Time::now();

  	goal.target_pose.pose.position.x = px;
	goal.target_pose.pose.position.y = py;
	goal.target_pose.pose.position.z = pz;

  	goal.target_pose.pose.orientation.x = ox;
	goal.target_pose.pose.orientation.y = oy;
	goal.target_pose.pose.orientation.z = oz;
	goal.target_pose.pose.orientation.w = ow;
	rate = loop_rate;	
}


}  // namespace pingfang_setgoals
