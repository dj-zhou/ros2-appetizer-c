#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_srvs/srv/empty.hpp"

using namespace std::chrono_literals;
using namespace rclcpp;

static Client<std_srvs::srv::Empty>::SharedPtr client;

void chatterCallback(const std_msgs::msg::String::SharedPtr msg) {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Received a string: '%s'",
                msg->data.c_str());
}

void timerCallback() {
    auto request = std::make_shared<std_srvs::srv::Empty::Request>();
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"),
                "Calls a <std_srvs::srv::Empty> request");
    auto result = client->async_send_request(request);
    ( void )result;
}

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);

    auto node = rclcpp::Node::make_shared("listener");

    auto chatter_sub = node->create_subscription<std_msgs::msg::String>(
        "/chatter", 10, &chatterCallback);
    auto timer = node->create_wall_timer(5s, &timerCallback);
    client     = node->create_client<std_srvs::srv::Empty>("/toggle");

    rclcpp::spin(node);

    return 0;
}
