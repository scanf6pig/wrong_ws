#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char** argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;
    ros::Rate rate(10);  // 设置发布频率

    // 创建图像发布器
    ros::Publisher image_pub = nh.advertise<sensor_msgs::Image>("image_topic", 10);

    // 创建一个400x600的像素值为0的图像
    cv::Mat image(400, 600, CV_8UC1, cv::Scalar(0));

    // 进行像素操作（将图像的一部分区域设置为白色）
    cv::Rect roi(300, 200, 100, 100);
    image(roi) = cv::Scalar(255);

    // 将图像转换为ROS消息并发布
    cv_bridge::CvImage img_bridge;
    sensor_msgs::Image img_msg;
    std_msgs::Header header;

    header.stamp = ros::Time::now();
    img_bridge = cv_bridge::CvImage(header, sensor_msgs::image_encodings::MONO8, image);
    img_bridge.toImageMsg(img_msg);

    while (ros::ok())
    {
        // 发布图像消息
        image_pub.publish(img_msg);
        ROS_INFO("Image published");

        // 等待一段时间
        rate.sleep();
    }

    return 0;
}
