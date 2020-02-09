#include "ros/ros.h"  
#include "std_msgs/String.h"
#include <boost/thread.hpp>  
  
/** 
 * This tutorial demonstrates the use of timer callbacks. 
 */  

#include <ctime>
const clock_t delay = CLOCKS_PER_SEC;

void delaytime(double second)
{
  clock_t start = clock();
  while(ros::ok() && clock() - start < delay*second){};
}

void heavywork()
{
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

  // clock_t start = clock();
  // while(ros::ok() && clock() - start < delay*1){};

} 
  
void callback2(const ros::TimerEvent&)  
{  
  // ROS_INFO("TimerCallback 2 triggered");  
  ROS_INFO_STREAM("[TimerCallback 2 thread=" << boost::this_thread::get_id() << "]");
}  

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  // ROS_INFO("I heard: [%s]", msg->data.c_str());

  //heavywork();
  ROS_INFO_STREAM("[chatterCallback thread=" << boost::this_thread::get_id() << "]");
}
  
int main(int argc, char **argv)  
{  
  ros::init(argc, argv, "testtest");  
  ros::NodeHandle n;  
  
  ros::Timer timer1 = n.createTimer(ros::Duration(0.1), callback1);  
  ros::Timer timer2 = n.createTimer(ros::Duration(0.2), callback2);  
  ros::Subscriber sub = n.subscribe("chatter", 1, chatterCallback);

  ROS_INFO_STREAM("[main function thread before while=" << boost::this_thread::get_id() << "]");
  
  ros::Rate r(10);

  while(ros::ok())
  { 

    //heavywork();

    //ROS_INFO_STREAM("[while function thread before spinOnce=" << boost::this_thread::get_id() << "]");
    ros::spinOnce(); 
    ROS_INFO_STREAM("[while function thread after spinOnce=" << boost::this_thread::get_id() << "]");

    //delaytime(1);
    r.sleep();
  }

  ROS_INFO_STREAM("[main function thread after while=" << boost::this_thread::get_id() << "]");

  return 0;  
} 