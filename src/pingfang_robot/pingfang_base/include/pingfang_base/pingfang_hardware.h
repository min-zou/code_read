#ifndef PINGFANG_BASE_PINGFANG_HARDWARE_H
#define PINGFANG_BASE_PINGFANG_HARDWARE_H

#include "hardware_interface/joint_state_interface.h"
#include "hardware_interface/joint_command_interface.h"
#include "hardware_interface/robot_hw.h"
#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "pingfang_msgs/Drive.h"
#include "pingfang_msgs/Feedback.h"
#include <string>
#include "realtime_tools/realtime_publisher.h"
#include "boost/thread.hpp"

namespace pingfang_base
{

class PingfangHardware : public hardware_interface::RobotHW
{
public:
  PingfangHardware();
  void copyJointsFromHardware();
  void publishDriveFromController();

private:
  void feedbackCallback(const pingfang_msgs::Feedback::ConstPtr& msg);

  ros::NodeHandle nh_;
  ros::Subscriber feedback_sub_;
  realtime_tools::RealtimePublisher<pingfang_msgs::Drive> cmd_drive_pub_;

  hardware_interface::JointStateInterface joint_state_interface_;
  hardware_interface::VelocityJointInterface velocity_joint_interface_;

  // These are mutated on the controls thread only.
  struct Joint
  {
    double position;
    double velocity;
    double effort;
    double velocity_command;

    Joint() : position(0), velocity(0), effort(0), velocity_command(0)
    {
    }
  }
  joints_[4];

  // This pointer is set from the ROS thread.
  pingfang_msgs::Feedback::ConstPtr feedback_msg_;
  boost::mutex feedback_msg_mutex_;
};

}  // namespace pingfang_base

#endif  // PINGFANG_BASE_PINGFANG_HARDWARE_H
