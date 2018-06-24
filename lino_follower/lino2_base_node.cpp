// Standard Dependecies
#include <iostream>
#include <string.h>

#include "lino2_base_node.hpp"

//#include "rclcpp/time.hpp"

/* ROS1 Dependencies
#include "tf2/LinearMath/Quartenion.h"
#include "tf2_ros/transform_broadcaster.h"
*/

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

using namespace std::chrono_literals;

/* LinoBase Constructor */
LinoBase::LinoBase(): Node("base"), x_pos(0.0), y_pos(0.0), theta(0.0)
{
        /* Odometry publisher
        */
        odom_pub = this->create_publisher<nav_msgs::msg::Odometry>("odom");
        auto odom_callback =
            [this]() -> void {
                auto odom = nav_msgs::msg::Odometry();
                //odom.header.stamp = current_time;
                odom.header.frame_id = "odom";
                /* robot's position in x,y, and z */
                odom.pose.pose.position.x = x_pos;
                odom.pose.pose.position.y = y_pos;
                odom.pose.pose.position.z = 0.0;
                /* robot's heading in quaternion */
                //odom.pose.pose.orientation = odom_quat;

                odom.child_frame_id = "base_footprint";
                /* linear speed from encoders */
                //odom.twist.twist.linear.x = linear_velocity_x;
                //odom.twist.twist.linear.y = linear_velocity_y;
                odom.twist.twist.linear.z = 0.0;

                odom.twist.twist.angular.x = 0.0;
                odom.twist.twist.angular.y = 0.0;
                /* angular speed from IMU */
                odom.twist.twist.angular.z = g_imu_z;

                this->odom_pub->publish(odom);
            };
        
        // Rate
        odom_timer = this->create_wall_timer(1000ms, odom_callback);

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


/* dynamic tf broadcaster */

/* Load parameters - port, base_link, speed */

/* tf magic */