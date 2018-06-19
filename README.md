# Lino2 ROS2 prototype

Linorobot on ROS2! Prototyping in progress..

## Aim

Linorobot on teleops as navigation stack is still work in progress

### Dependencies

* [ROS2_teleops_keyboard](https://github.com/ros2/teleop_twist_keyboard) - Not available in Ardent by default


### To Install

```
ament build --symlink-install --only-package lino2
```

### To run
```
ros2 run lino2 follower
```

### Some Plans

* [Navigation](https://github.com/ros2/navigation) - Not continued for ROS2, strictly demo only

* [Navigation2](https://github.com/ros-planning/navigation2) - Started planning on June 2018


### To do list
* Micro-RTPS agent to base controller
* Receive teleops command and move 



