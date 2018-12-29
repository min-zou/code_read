#include "ros/ros.h"
#include "pingfang_msgs/Drive.h"
#include "pingfang_msgs/Feedback.h"

#include "rock_driver.h"
#include <stdint.h>

const float pi = 3.1415927;
const float ticks_rad = 8.276;   //the ticks for one rad /100
rock_driver * drv = rock_driver::CreateDriver(rock_driver::DRIVER_TYPE_SERIALPORT);
int left_command = 0;
int right_command = 0;
int last_left_command = 1;
int last_right_command = 1; 
void callback(const pingfang_msgs::Drive::ConstPtr& msg)
{
    left_command = msg->drivers[0] * ticks_rad;
    right_command = msg->drivers[1] * ticks_rad;
    if(left_command != last_left_command && right_command != last_right_command ){ 
    	drv->sendcmd(left_command, right_command);
	last_left_command = left_command;
	last_right_command = right_command;
	}
}




int main(int argc, char * argv[])
{
    ros::init(argc, argv, "rock_driver_node");
    std::string serial_port;
    int serial_baudrate = 115200;
    int rate;
    int ticks_round;
    int32_t enc_left = 0;
    int32_t enc_right = 0;
    int32_t left;
    int32_t right;
    int32_t d_left;
    int32_t d_right;
    int32_t encbuffer[2];
    ros::NodeHandle nh;
    ros::NodeHandle nh_private("~");
    nh_private.param<std::string>("serial_port",serial_port,"/dev/ttyUSB0");
    nh_private.param<int>("serial_baudrate", serial_baudrate, 115200); 
    nh_private.param<int>("rate",rate,10);
    nh_private.param<int>("ticks_round",ticks_round,5200);
    ros::Rate loop_rate(rate);

    ros::Publisher feedback_pub = nh.advertise<pingfang_msgs::Feedback>("feedback",1);

     

    
    if (!drv) {
        fprintf(stderr, "Create Driver fail, exit\n");
        return -2;
    }

    if(drv->connect(serial_port.c_str(), (uint32_t)serial_baudrate) == -1)
	{
	    fprintf(stderr, "Error, cannot bind to the specified serial port %s.\n", serial_port.c_str());
	    return -1;
	}
    drv->start();

    ros::Subscriber cmd_sub =  nh.subscribe("cmd_drive", 1, callback);
    ros::Time time_now;
    ros::Time time_then = ros::Time::now();
    double cal_duration;
     
    while(ros::ok())
    {
        pingfang_msgs::Feedback feedback_msg;
        time_now =ros::Time::now();
	cal_duration = (time_now -time_then).toSec();
	time_then = time_now;
        
        if(drv->getenc(encbuffer) == -1)
	{
	    ROS_INFO("con't get the encode date.");
	}else{
            left = *encbuffer;
            right = *(encbuffer+1);
            d_left = left - enc_left;
            d_right = right - enc_right;
	    enc_left = left;
	    enc_right = right;
	    feedback_msg.header.stamp = time_now;
            feedback_msg.drivers[0].measured_travel = left * 2 * pi/ticks_round;
	    feedback_msg.drivers[1].measured_travel = right * 2 * pi/ticks_round;
	    feedback_msg.drivers[0].measured_velocity = d_left * 2 * pi/(ticks_round * cal_duration);
            feedback_msg.drivers[1].measured_velocity = d_right * 2 * pi/(ticks_round * cal_duration);
	    feedback_msg.pcb_temperature =30;
	    feedback_msg.mcu_temperature =30;
            feedback_pub.publish(feedback_msg);
	}
	ros::spinOnce();
	loop_rate.sleep();
    }
    drv->sendstop();
    rock_driver::DisposeDriver(drv);
    return 0;
}
