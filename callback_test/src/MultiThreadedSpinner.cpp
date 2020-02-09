#include "ros/ros.h"  
#include "std_msgs/String.h"
#include <boost/thread.hpp>  
#include <iostream>
  
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

void sleeptime(double second)
{
  double fr = 1/second;
  ros::Rate r(fr);
  r.sleep();
}


  
void callback1(const ros::TimerEvent&)  
{  
  // ROS_INFO("TimerCallback 1 triggered");  
  delaytime(3);
  ROS_INFO_STREAM("[TimerCallback 1 thread=" << boost::this_thread::get_id() << "]");

} 
  
void callback2(const ros::TimerEvent&)  
{  
  // ROS_INFO("TimerCallback 2 triggered");  
  delaytime(3);
  ROS_INFO_STREAM("[TimerCallback 2 thread=" << boost::this_thread::get_id() << "]");
}  

void chatterCallback1(const std_msgs::String::ConstPtr& msg)
{ 
  ROS_INFO("I heard: [%s]", msg->data.c_str());

  //heavywork();
  //sleeptime(3);
  delaytime(3);
  //sleep(1000);
  ROS_INFO_STREAM("[chatterCallback thread=" << boost::this_thread::get_id() << "]");
}
  
int main(int argc, char **argv)  
{  
  ros::init(argc, argv, "testtest");  
  ros::NodeHandle n;
  
  // ros::Timer timer1 = n.createTimer(ros::Duration(0.1), callback1);  
  // ros::Timer timer2 = n.createTimer(ros::Duration(0.2), callback2);  
  ros::Subscriber sub = n.subscribe("chatter", 20, chatterCallback1);

  ROS_INFO_STREAM("[main function thread before spinner=" << boost::this_thread::get_id() << "]");

  ros::AsyncSpinner spinner(1);

  // while(ros::ok())
  // { 
  //   clock_t start = clock();
  //   spinner.start();

  // }

  ros::Rate r(1);  
  while (ros::ok())
  {  
    ROS_INFO_STREAM("Main thread [" << boost::this_thread::get_id() << "].");
    spinner.start();
    //spinner.stop();
    r.sleep();
  }

  std::cout << "node end" << std::endl;

  return 0;  
} 