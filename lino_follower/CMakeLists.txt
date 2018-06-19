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
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
#find_package(teleop_twist_keyboard REQUIRED)

add_executable(follower follower.cpp)
ament_target_dependencies(follower rclcpp geometry_msgs nav_msgs)

install(TARGETS
  follower
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
