#ifndef LINO_BASE_NODE_H_
#define LINO_BASE_NODE_H_

#include <string>

// RCL
#include "rclcpp/rclcpp.hpp"

// Lino Msg
#include "lino_msgs/msg/velocities.hpp"

class LinoBase: public rclcpp::Node
{
public:
    LinoBase();
    
private:
    rclcpp::Subscription<lino_msgs::msg::Velocities>::SharedPtr vel_sub;
};

#endif /* LINO_BASE_NODE_H_ */