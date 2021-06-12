#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_srvs/srv/empty.hpp"

static bool talk_style;

void serviceCallback(
    const std::shared_ptr<std_srvs::srv::Empty::Request> request,
    std::shared_ptr<std_srvs::srv::Empty::Response> response) {
    ( void )request;
    ( void )response;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"),
                "Received a <std_srvs::srv::Empty> request");
    talk_style = !talk_style;
}

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    talk_style = true;
    auto node  = rclcpp::Node::make_shared("talker");
    auto chatter_pub =
        node->create_publisher<std_msgs::msg::String>("/chatter", 10);
    auto service =
        node->create_service<std_srvs::srv::Empty>("/toggle", &serviceCallback);

    rclcpp::WallRate loop_rate(2);

    auto message = std_msgs::msg::String();
    auto count   = 0;
    while (rclcpp::ok()) {
        if (talk_style) {
            message.data = "Hello, ROS2 and AGV! " + std::to_string(count++);
        }
        else {
            message.data = std::to_string(count++) + ": It's a good day today!";
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Publishing: '%s'",
                    message.data.c_str());

        chatter_pub->publish(message);

        rclcpp::spin_some(node);

        loop_rate.sleep();
    }

    return 0;
}
