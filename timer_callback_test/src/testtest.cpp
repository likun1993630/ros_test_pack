#include "ros/ros.h"  
#include "std_msgs/String.h"
#include <boost/thread.hpp>  
  
/** 
 * This tutorial demonstrates the use of timer callbacks. 
 */  
  
void callback1(const ros::TimerEvent&)  
{  
  // ROS_INFO("TimerCallback 1 triggered");  
  ROS_INFO_STREAM("[TimerCallback 1 thread=" << boost::this_thread::get_id() << "]");
}  
  
void callback2(const ros::TimerEvent&)  
{  
  // ROS_INFO("TimerCallback 2 triggered");  
  ROS_INFO_STREAM("[TimerCallback 2 thread=" << boost::this_thread::get_id() << "]");
}  

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  // ROS_INFO("I heard: [%s]", msg->data.c_str());
  ROS_INFO_STREAM("[chatterCallback thread=" << boost::this_thread::get_id() << "]");
}
  
int main(int argc, char **argv)  
{  
  ros::init(argc, argv, "testtest");  
  ros::NodeHandle n;  
  
  ros::Timer timer1 = n.createTimer(ros::Duration(0.1), callback1);  
  ros::Timer timer2 = n.createTimer(ros::Duration(0.2), callback2);  
  ros::Subscriber sub = n.subscribe("chatter", 10, chatterCallback);
  
  ros::spin();  
  
  return 0;  
} 
