// ROS1 Dependencies
#include "tf2/LinearMath/Quartenion.h"
#include "tf2_ros/transform_broadcaster.h"

#include "lino2_base_node.hpp"

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LinoBase>());

    return 0; 
}