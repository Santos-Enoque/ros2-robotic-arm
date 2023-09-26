#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

struct SimpleSubscriber : rclcpp::Node {
    public:
    SimpleSubscriber() : Node("simple_subscriber") {
        subscription_ = create_subscription<std_msgs::msg::String>("chatter", 10, std::bind(&SimpleSubscriber::messageCallback, this, std::placeholders::_1));
    }

    void messageCallback(const std_msgs::msg::String::SharedPtr message) const {
        RCLCPP_INFO(get_logger(), "I heard: '%s'", message->data.c_str());
    }

    private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto nodeptr = std::make_shared<SimpleSubscriber>();
    rclcpp::spin(nodeptr);
    rclcpp::shutdown();
    return 0;
}