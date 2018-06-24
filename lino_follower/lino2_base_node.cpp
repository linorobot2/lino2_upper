/*
 * To use navigation stack in ROS, robot must satisfy the following requirement
 * 1) Relationship of joints (tf) by odom_pub
 * 2) Linear/angular velocities by local planner -> vel -> base controller
 * Optional:
 * 1) sensor_mgs(imu/laser/pointcloud) for recovery behavior
 */

// Standard Dependecies
#include <iostream>
#include <string.h>
#include <chrono>

#include "lino2_base_node.hpp"

//#include "rclcpp/time.hpp"

// TF2
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"

/* Global variables */
static double g_vel_x;
static double g_vel_y;
//static double g_vel_dt;
    
static double g_imu_z;
//static double g_imu_dt;


/* Clock */
//static rclcpp::Time g_last_loop_time(0.0);
//static rclcpp::Time g_last_vel_time(0.0);
//static rclcpp::Time g_last_imu_time(0.0);

// What is ecl namespace? use for pose

using namespace std::chrono_literals;

/* LinoBase Constructor */
LinoBase::LinoBase(): 
Node("base"),
x_pos(0.0), 
y_pos(0.0), 
odom_frame("odom"), 
base_link("base_footprint")
{
        /* Odometry publisher
        */
        odom_pub = this->create_publisher<nav_msgs::msg::Odometry>("odom");
        auto odom_callback =
            [this]() -> void {
                auto odom_msg = std::make_shared<nav_msgs::msg::Odometry>();
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

                this->odom_pub->publish(odom_msg);

                auto odom_tf_msg = std::make_shared<geometry_msgs::msg::TransformStamped>();
                
                tf2_ros::TransformBroadcaster br(Node);

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
            };
        
        // Rate - consider 20ms?
        odom_timer = this->create_wall_timer(200ms, odom_callback);

        /* Velocity subscriber with lambda function callback
         * Use: Set base linear and angular speed
         * To pass const geometry_msgs::msg::Twist::SharedPtr msg instead of lino_msg?
         * To figure out the rate (50Hz)
         * SharedPtr or UniquePtr? 
         */
        vel_sub = this->create_subscription<lino_msgs::msg::Velocities>(
            "raw_vel",
            [this](const lino_msgs::msg::Velocities::SharedPtr vel) 
            {
            // Current time - to use rcutil? rclcpp::Time?

            g_vel_x = vel->linear_x;
            g_vel_y = vel->linear_y;

            //g_vel_dt = (current_time - g_last_vel_time).Sec();
            //g_last_vel_time = current_time;
            }
        );

    }

