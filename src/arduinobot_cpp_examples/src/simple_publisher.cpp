#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <chrono>
using namespace std::chrono_literals;

class SimplePublisher : public rclcpp::Node
{
    public:
    SimplePublisher() : Node("simple_publisher"), count_{0} {
        publisher_ = create_publisher<std_msgs::msg::String>("chatter", 10);
        timer_ = create_wall_timer(1s, std::bind(&SimplePublisher::timerCallback, this));
        RCLCPP_INFO(get_logger(), "SimplePublisher has been started.");
    }

    void timerCallback(){
        auto message = std_msgs::msg::String();
        message.data = "Hello World! " + std::to_string(count_++);
        RCLCPP_INFO(get_logger(), "Publishing: '%s'", message.data.c_str());
        publisher_->publish(message);
    }

    private:
    unsigned int count_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SimplePublisher>());
    rclcpp::shutdown();
    return 0;
}