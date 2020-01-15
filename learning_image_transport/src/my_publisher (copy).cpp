#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <camera_info_manager/camera_info_manager.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sstream> // for converting the command line parameter to integer
#include <sensor_msgs/image_encodings.h>

#include <sensor_msgs/CameraInfo.h>

int main(int argc, char** argv)
{
  // Check if video source has been passed as a parameter
  if(argv[1] == NULL) return 1;

  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::CameraPublisher pub = it.advertiseCamera("camera/image", 1);
  //camera_info_manager::CameraInfoManager cim(nh, "left");

  // Convert the passed as command line parameter index for the video device to an integer
  std::istringstream video_sourceCmd(argv[1]);
  int video_source;
  // Check if it is indeed a number
  if(!(video_sourceCmd >> video_source)) return 1;

  cv::VideoCapture cap(video_source);
  // Check if video device can be opened with the given index
  if(!cap.isOpened()) return 1;
  cv::Mat frame;
  sensor_msgs::ImagePtr msg;
  //sensor_msgs::CameraInfo cameraInfo = cim.getCameraInfo();
  sensor_msgs::CameraInfo cameraInfo;

  ros::Rate loop_rate(5);
  while (nh.ok()) {
    cap >> frame;
    // Check if grabbed frame is actually full with some content
    if(!frame.empty()) {
      msg = cv_bridge::CvImage(std_msgs::Header(), sensor_msgs::image_encodings::YUV422 , frame).toImageMsg();
      pub.publish(*msg,cameraInfo);
      cv::waitKey(1);
    }

    ros::spinOnce();
    loop_rate.sleep();
  }
}