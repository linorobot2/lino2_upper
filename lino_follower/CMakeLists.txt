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
#find_package(teleop_twist_keyboard REQUIRED)

message(STATUS "Starting lino2 build ..")
file(GLOB LINO_SOURCES 
  lino2_main.cpp
  lino2_base_node.cpp
  lino2_base_node.hpp
)

add_executable(lino_node ${LINO_SOURCES})
ament_target_dependencies(lino_node rclcpp nav_msgs lino_msgs tf2)

install(TARGETS
  lino_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
