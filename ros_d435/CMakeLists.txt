cmake_minimum_required(VERSION 3.0.2)
project(ros_d435)

find_package(catkin REQUIRED COMPONENTS
  image_transport
  cv_bridge
  roscpp
  sensor_msgs
  std_msgs
)

find_package (OpenCV REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES D435
  LIBRARIES opencv

  CATKIN_DEPENDS image_transport cv_bridge roscpp sensor_msgs std_msgs
# DEPENDS system_lib
)

include_directories(
  include
 ${catkin_INCLUDE_DIRS}
 ${OpenCV_INCLUDE_DIRS}
)

add_executable(d435_img_node src/d435_main.cpp)
target_link_libraries(d435_img_node ${catkin_LIBRARIES})