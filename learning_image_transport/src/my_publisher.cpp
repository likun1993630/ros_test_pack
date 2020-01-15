#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sstream> // for converting the command line parameter to integer
#include <bitset>

int main(int argc, char** argv)
{
  // Check if video source has been passed as a parameter
  if(argv[1] == NULL) return 1;

  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("camera/image", 1);

  // Convert the passed as command line parameter index for the video device to an integer
  std::istringstream video_sourceCmd(argv[1]);
  int video_source;
  // Check if it is indeed a number
  if(!(video_sourceCmd >> video_source)) return 1;

  cv::VideoCapture cap(video_source);

  // Check if video device can be opened with the given index
  if(!cap.isOpened()) return 1;

  // @获取采集视频数据的格式：这里是YUYV
  // @An openCV VideoCapture object is the easiest way to capture video, 
  // @ but it automatically converts the frames to BGR format.
  // @尽管原始的图像是YUYV，但是Opencv读取的时候自动转换，所以输出的frame还是 BGR 格式的
  int ex = cap.get(CV_CAP_PROP_FOURCC);
  // int ex = static_cast<int>(inputVideo.get(CV_CAP_PROP_FOURCC));
  // Transform from int to char via Bitwise operators
  char EXT[] = {(char)(ex & 0XFF),(char)((ex & 0XFF00) >> 8),(char)((ex & 0XFF0000) >> 16),(char)((ex & 0XFF000000) >> 24),0};
  for(int i=0; i<sizeof(EXT); i++)
    std::cout << EXT[i];
  std::cout << std::endl;

  int ma = cap.get(CV_CAP_PROP_CONVERT_RGB);
  std::cout << ma << std::endl;

  //cap.set(CV_CAP_PROP_CONVERT_RGB, false);

  cv::Mat frame;
  sensor_msgs::ImagePtr msg;

  ros::Rate loop_rate(5);
  while (nh.ok()) {
    cap >> frame;
    // Check if grabbed frame is actually full with some content
    if(!frame.empty()) {

      //std::cout << (std::bitset<32>)frame.flags << std::endl;

      //COLOR_YUV2BGR_YUYV
      //COLOR_YUV2BGR_UYVY
      cv::Mat newframe;
      cv::Mat newframe2;
      //cv::cvtColor( frame,newframe,cv::COLOR_YUV2BGR_YUYV);
      cv::cvtColor( frame,newframe2,cv::COLOR_BGR2YUV);

      cv::imshow("new",frame);

      msg = cv_bridge::CvImage(std_msgs::Header(),"yuv422",newframe2).toImageMsg();
      pub.publish(msg);
      cv::waitKey(1);
    }

    ros::spinOnce();
    loop_rate.sleep();
  }
}

//"bgr8",