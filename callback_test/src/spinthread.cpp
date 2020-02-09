#include "ros/ros.h"  
#include "std_msgs/String.h"
#include <boost/thread.hpp> 
#include <boost/thread/thread.hpp>
  
/** 
 * This tutorial demonstrates the use of timer callbacks. 
 */  

void run()  
{    
    ROS_INFO_STREAM("[run thread=" << boost::this_thread::get_id() << "]");
}

void heavywork()
{ 
  //ROS_INFO_STREAM("[heavywork thread=" << boost::this_thread::get_id() << "]");
  int count = 1000;
  for (int i = 0; i < count; ++i)
  {
    for (int j = 0; j < count; ++j)
    {
      for (int k = 0; k < count; ++k)
      {
         for (int n = 0; n < 1; ++n)
         {
           int a = 0;
           a ++;
         }
      }
    }
  }
}

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

  //ROS_INFO_STREAM("[chatterCallback thread=" << boost::this_thread::get_id() << "]");

  //boost::thread t1( boost::bind(&run));
  boost::thread t2( boost::bind(&heavywork));

  t2.join();
  //t2.try_join_for(boost::chrono::milliseconds(100));
  //t1.join();
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}
  
int main(int argc, char **argv)  
{  
  ros::init(argc, argv, "testtest");  
  ros::NodeHandle n;  
  
  // ros::Timer timer1 = n.createTimer(ros::Duration(1), callback1);  
  // ros::Timer timer2 = n.createTimer(ros::Duration(1), callback2);  
  ros::Subscriber sub = n.subscribe("chatter", 1, chatterCallback);

  ROS_INFO_STREAM("[main function thread=" << boost::this_thread::get_id() << "]");
  
  ros::spin();  
  
  return 0;  
} 
