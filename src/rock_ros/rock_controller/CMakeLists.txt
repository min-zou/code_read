cmake_minimum_required(VERSION 2.8.3)
project(rock_controller)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rosconsole
  roslaunch
  roslint
  pingfang_msgs
)

catkin_package(
    INCLUDE_DIRS include
    CATKIN_DEPENDS pingfang_msgs roscpp
)


include_directories( include ${catkin_INCLUDE_DIRS}
)

add_executable(rock_driver_node src/rock_driver_node.cpp src/rock_serial.cpp src/rock_driver.cpp )

target_link_libraries(rock_driver_node ${catkin_LIBRARIES})

add_dependencies(rock_driver_node pingfang_msgs_gencpp)

roslint_cpp(
  src/rock_driver_node.cpp
  src/rock_serial.cpp
  src/rock_driver.cpp
  include/rock_driver.h
  include/rock_serial.h
  include/rock_rxtx.h
  include/rock_driver_serial.h
  )

roslaunch_add_file_check(launch)



