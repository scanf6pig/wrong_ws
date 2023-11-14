#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <limits>
void scancallback(const sensor_msgs::LaserScan::ConstPtr& msg);

void scancallback(const sensor_msgs::LaserScan::ConstPtr &msg) {
    //处理传入数据
    float min_distance = std::numeric_limits<float>::max();
    for (float range : msg->ranges)
    {
        if(range<min_distance)
        {
            min_distance = range;
        }
    }

    ROS_INFO("Min distance: %.2f",min_distance);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "smb_highlevel_controller_node");
    ros::NodeHandle nh;
//创建订阅者订阅/scan话题
    ros::Subscriber scan_sub = nh.subscribe("/scan" , 1000 , scancallback);

    ros::spin();//循环监听并处理回调函数

    return 0;
}
