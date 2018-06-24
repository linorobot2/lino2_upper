/*
 * To use navigation stack in ROS, robot must satisfy the following requirement
 * 1) Relationship of joints (tf) by odom_pub
 * 2) Linear/angular velocities by local planner -> vel -> base controller
 * Optional:
 * 1) sensor_mgs(imu/laser/pointcloud) for recovery behavior
 */
#include "lino2_base_node.hpp"

//#include "rclcpp/time.hpp"

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

/* LinoBase Constructor */
LinoBase::LinoBase(): Node("base")
{
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

