#ifndef LINOBASENODE_H_
#define LINOBASENODE_H_

// RCL
#include "rclcpp/rclcpp.hpp"

// Msg 
#include "nav_msgs/msg/odometry.hpp"
//#include "sensor_msgs/msg/imu.hpp"
#include "geometry_msgs/msg/twist.hpp"

// ROS1 Dependencies
#include "tf2/LinearMath/Quartenion.h"
#include "tf2_ros/transform_broadcaster.h"

class LinoBase: public rclcpp::Node
{
public:
    LinoBase():
    Node('base_controller'),
    rate(10.0),
    x_pos(0.0),
    y_pos(0.0),
    theta(0.0)
    {
    }
    void velCallBack(const lino_msgs::Velocities& vel);
    void IMUCallBack(const sensor_msgs::Imu& imu);
private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_pub;
    // RAW_VEL subscriber
    // NAV_MSG subscriber

    tf::TransformBroadcaster odom_broadcaster;

    double rate;
    double x_pos;
    double y_pos;
    double theta;

};

#endif /* LINOBASENODE_H_ */