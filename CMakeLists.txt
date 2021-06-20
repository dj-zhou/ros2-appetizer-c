cmake_minimum_required(VERSION 3.5)
project(ros2_appetizer_c)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)

include_directories(./include/)

# --------------------------------
add_executable(
  talker
  "src/talker_node.cpp"
)

ament_target_dependencies(
  talker
  rclcpp
  std_msgs
  std_srvs
)

install(TARGETS talker
  DESTINATION lib/${PROJECT_NAME}
)

# --------------------------------
add_executable(
  listener
  "src/listener_node.cpp"
)

ament_target_dependencies(
  listener
  rclcpp
  std_msgs
  std_srvs
)

install(TARGETS listener
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
