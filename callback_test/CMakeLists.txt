cmake_minimum_required(VERSION 2.8.3)
project(callback_test)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

find_package(Boost REQUIRED COMPONENTS thread)


catkin_package()
include_directories(${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

add_executable(callbacktalker src/talker.cpp)
target_link_libraries(callbacktalker ${catkin_LIBRARIES})

add_executable(spin src/spin.cpp)
target_link_libraries(spin ${catkin_LIBRARIES} ${Boost_LIBRARIES})

add_executable(spinonce src/spinonce.cpp)
target_link_libraries(spinonce ${catkin_LIBRARIES} ${Boost_LIBRARIES})

add_executable(MultiThreadedSpinner src/MultiThreadedSpinner.cpp)
target_link_libraries(MultiThreadedSpinner ${catkin_LIBRARIES} ${Boost_LIBRARIES})

add_executable(spinthread src/spinthread.cpp)
target_link_libraries(spinthread ${catkin_LIBRARIES} ${Boost_LIBRARIES})