cmake_minimum_required(VERSION 2.8.3)
project(pingfang_nav)

find_package(catkin REQUIRED roslaunch dynamic_reconfigure)

catkin_python_setup()

generate_dynamic_reconfigure_options(cfg/CalibrateAngular.cfg cfg/CalibrateLinear.cfg)

catkin_package(CATKIN_DEPENDS dynamic_reconfigure)

roslaunch_add_file_check(launch)

install(
  DIRECTORY config launch maps
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

