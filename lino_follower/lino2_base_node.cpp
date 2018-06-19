// Standard Dependecies
#include <iostream>
#include <string.h>

#include "lino2_base_node.hpp"

/* Global variables */
double g_vel_x = 0.0;
double g_vel_y = 0.0;

double g_vel_dt = 0.0;
double g_imu_dt = 0.0;
double g_imu_z = 0.0;

// Lino2 msg

// initialise global velocity and imu readings in a class?

// ROS time variables

/* cmd_vel callback -> set base linear and angular speed */

/* imu callback - to filter imu noise - possibly replace with kalman filter? */

/* dynamic tf broadcaster */

/* Load parameters - port, base_link, speed */

/* tf magic */