#include <rclc/rclc.h>
#include <std_msgs/msg/int32.h>
#include <stdio.h>

typedef std_msgs__msg__Int32 Int32;

void callback(const void* void_message) {
    const Int32* message = ( const Int32* )void_message;
    printf("Got number: %d\n", message->data);
}

int main(int argc, char** argv) {
    rclc_init(argc, argv);

    rclc_node_t* node = rclc_create_node("listener");

    rclc_subscription_t* subscription = rclc_create_subscription(
        node, ROSIDL_GET_MESSAGE_TYPE_SUPPORT(std_msgs, Int32), "chatter",
        callback, 7, false);

    rclc_spin_node(node);

    rclc_destroy_subscription(subscription);
    rclc_destroy_node(node);

    return 0;
}
