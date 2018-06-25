#include <chrono> 

// Standard Dependecies
#include <iostream>
#include <string.h>

#include <string>

// RCL
#include "rclcpp/rclcpp.hpp"

// Msg 
#include "nav_msgs/msg/odometry.hpp"

// TF2
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
    
using namespace std::chrono_literals;

int main(int argc, char * argv[])    
{
    static double g_imu_z;
    double x_pos = 0.0;
    double y_pos = 0.0;
    std::string odom_frame = "odom";
    std::string base_link = "base_footprint";
    
    rclcpp::init(argc, argv);   // init ros node
    auto node = rclcpp::Node::make_shared("lino_tf");  // create node

    auto odom_pub = node->create_publisher<nav_msgs::msg::Odometry>("odom");    
    
    auto odom_msg = std::make_shared<nav_msgs::msg::Odometry>();
    auto odom_tf_msg = std::make_shared<geometry_msgs::msg::TransformStamped>();    

    rclcpp::WallRate loop_rate(20);  // timer
            
    //rcutils_time_point_value_t now;
    //odom_msg->header.stamp = RCL_NS_TO_S(now);
    odom_msg->header.frame_id = odom_frame;
    odom_msg->child_frame_id = base_link;
    /* robot position is x y z */
    odom_msg->pose.pose.position.x = x_pos;
    odom_msg->pose.pose.position.y = y_pos;
    odom_msg->pose.pose.position.z = 0.0;

    /* robot orientation in quaternion */
    tf2::Quaternion quat;
    quat.setRPY(0.0, 0.0, g_imu_z); // RPY: Roll Pitch Yaw
    odom_msg->pose.pose.orientation.x = quat.x();
    odom_msg->pose.pose.orientation.y = quat.y();
    odom_msg->pose.pose.orientation.z = quat.z();
    odom_msg->pose.pose.orientation.w = quat.w();

    /* linear speed from encoders */
    //odom.twist.twist.linear.x = linear_velocity_x;
    //odom.twist.twist.linear.y = linear_velocity_y;
    odom_msg->twist.twist.linear.z = 0.0;
    /* angular speed from IMU */
    odom_msg->twist.twist.angular.x = 0.0;
    odom_msg->twist.twist.angular.y = 0.0;
    odom_msg->twist.twist.angular.z = g_imu_z;

    odom_pub->publish(odom_msg);
                
    tf2_ros::TransformBroadcaster br(node);

    //odom_tf_msg->header.stamp = odom_msg->header.stamp;
    odom_tf_msg->header.frame_id = odom_frame;
    odom_tf_msg->child_frame_id = base_link;
    odom_tf_msg->transform.translation.x = x_pos;
    odom_tf_msg->transform.translation.y = y_pos;
    odom_tf_msg->transform.translation.z = 0.0;
    odom_tf_msg->transform.rotation.x = quat.x();
    odom_tf_msg->transform.rotation.y = quat.y();
    odom_tf_msg->transform.rotation.z = quat.z();
    odom_tf_msg->transform.rotation.w = quat.w();

    br.sendTransform(*odom_tf_msg);
}