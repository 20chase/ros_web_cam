#include <ros/ros.h>  
#include <image_transport/image_transport.h>  
#include <cv_bridge/cv_bridge.h>  
#include <sensor_msgs/image_encodings.h>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/highgui/highgui.hpp>

image_transport::Publisher image_pub;

int main(int argc, char **argv)
{
	ros::init(argc, argv, "web_cam");

	ros::NodeHandle nh;

	image_transport::ImageTransport it(nh); 

	ros::Rate loopRate(20);

	image_pub = it.advertise("camera/image_raw", 1);

	cv::VideoCapture cap(0);

	cv::Mat frame;

	cv_bridge::CvImagePtr cv_ptr;

	while (1)
	{
		cap >> frame;

        sensor_msgs::ImagePtr msg;  

		msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();  

		image_pub.publish(msg); 

		usleep(50);
	}



}




