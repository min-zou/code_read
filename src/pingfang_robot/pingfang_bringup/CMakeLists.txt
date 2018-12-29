cmake_minimum_required(VERSION 2.8.3)
project(pingfang_bringup)

find_package(catkin REQUIRED COMPONENTS pingfang_msgs roslaunch roslint  roscpp sensor_msgs rock_imu rock_controller rplidar_ros)

catkin_package()

roslaunch_add_file_check(launch)

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
