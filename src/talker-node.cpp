#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("talker");
    auto chatter_pub =
        node->create_publisher<std_msgs::msg::String>("chatter", 10);

    rclcpp::WallRate loop_rate(2);

    auto message = std_msgs::msg::String();
    auto count   = 0;
    while (rclcpp::ok()) {
        message.data = "Hello, ROS2 and AGV! " + std::to_string(count++);
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Publishing: '%s'",
                    message.data.c_str());

        chatter_pub->publish(message);

        rclcpp::spin_some(node);

        loop_rate.sleep();
    }

    return 0;
}
