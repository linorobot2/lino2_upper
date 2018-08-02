cmake_minimum_required(VERSION 3.5)
project(lino2)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(lino_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(geometry_msgs REQUIRED)
#find_package(teleop_twist_keyboard REQUIRED)

message(STATUS "Starting lino2 build ..")
set(LINO_SOURCES 
  lino2_main.cpp
  lino2_base_node.cpp
)

add_executable(lino_node ${LINO_SOURCES})
#add_executable(lino_tf lino2_tf.cpp)

ament_target_dependencies(lino_node rclcpp lino_msgs)
#ament_target_dependencies(lino_tf rclcpp nav_msgs geometry_msgs tf2 tf2_ros)

install(TARGETS
  lino_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
