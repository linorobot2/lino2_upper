/* Linorobot2 ROS2 Prototype */

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"

/* Inherit node and uses lambda function to shorten callback syntax.
 * Possible to use std::bind() to register member function as a callback.
 * Different from past style, due to composition of multiple nodes in 
 * same executable 
 * Subscribe to Twist msg type through 'cmd_vel' topic.
 * Publish Odom msg type through 'odom' topic. 
 * NOTE: PASSING OF Twist-Odom IS STRICTLY PROTOTYPING. 
 * To work on Sensor msg type in the near future */

class LinoFollower : public rclcpp::Node
{
public:
    // Constructor
    LinoFollower(): Node("lino_follower")
    {
        publisher_ = this->create_publisher<nav_msgs::msg::Odometry>("odom");
        subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "cmd_vel",
            [this](geometry_msgs::msg::Twist::UniquePtr vel) {
            // UniquePtr or SharedPtr?
            auto odom = nav_msgs::msg::Odometry();
            odom.twist.twist.linear.x = vel->linear.x;    
            RCLCPP_INFO(this->get_logger(), "DEBUG - linear.x: %s", vel->linear.x)
        });
    }

private:
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr publisher_;
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LinoFollower>());
    rclcpp::shutdown();
    return 0;
}
