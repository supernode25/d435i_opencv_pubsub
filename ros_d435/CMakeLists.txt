cmake_minimum_required(VERSION 3.0.2)
project(ros_d435)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  roscpp
  sensor_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES opencv
  CATKIN_DEPENDS cv_bridge roscpp sensor_msgs 
# DEPENDS system_lib
)

include_directories(
  include
 ${catkin_INCLUDE_DIRS}
)

add_executable(d435_img_node src/d435_main.cpp)
target_link_libraries(d435_img_node ${catkin_LIBRARIES})