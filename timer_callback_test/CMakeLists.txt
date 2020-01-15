cmake_minimum_required(VERSION 2.8.3)
project(timer_callback_test)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

find_package(Boost REQUIRED COMPONENTS thread)


catkin_package()
include_directories(${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})

add_executable(testtest src/testtest.cpp)
target_link_libraries(testtest ${catkin_LIBRARIES} ${Boost_LIBRARIES})
