#ifndef LINO_BASE_NODE_H_
#define LINO_BASE_NODE_H_

// RCL
#include "rclcpp/rclcpp.hpp"

// Msg 
#include "nav_msgs/msg/odometry.hpp"
//#include "sensor_msgs/msg/imu.hpp"
#include "geometry_msgs/msg/twist.hpp"

// Lino Msg
#include "lino_msgs/msg/velocities.hpp"

class LinoBase: public rclcpp::Node
{
public:
    LinoBase():
    
private:
    rclcpp::TimerBase::SharedPtr odom_timer;
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_pub;
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub;
    rclcpp::Subscription<lino_msgs::msg::Velocities>::SharedPtr vel_sub;

    double rate;
    double x_pos;
    double y_pos;
    double theta;

};

#endif /* LINO_BASE_NODE_H_ */