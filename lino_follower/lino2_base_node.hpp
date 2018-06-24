#ifndef LINO_BASE_NODE_H_
#define LINO_BASE_NODE_H_

#include <chrono>

// RCL
#include "rclcpp/rclcpp.hpp"

// Msg 
#include "nav_msgs/msg/odometry.hpp"
#include "geometry_msgs/msg/twist.hpp"

// Lino Msg
#include "lino_msgs/msg/velocities.hpp"

class LinoBase: public rclcpp::Node
{
public:
    LinoBase();
    
private:
    rclcpp::TimerBase::SharedPtr odom_timer;
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_pub;
    rclcpp::Subscription<lino_msgs::msg::Velocities>::SharedPtr vel_sub;

    double x_pos;
    double y_pos;
    double theta;

};

#endif /* LINO_BASE_NODE_H_ */