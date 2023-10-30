#include <memory>

#include "rclcpp/rclcpp.hpp"
#include <thread>
#include "microscope_srvs/srv/set_light_color_mode.hpp"
#include "microscope_msgs/msg/light_color_mode.hpp"
#include "std_msgs/msg/string.hpp"
using std::placeholders::_1;
void printThreadID() {
    std::thread::id threadId = std::this_thread::get_id();
    std::cout << "Thread ID: " << threadId << std::endl;
}
void response_received_callback(const rclcpp::Client<microscope_srvs::srv::SetLightColorMode>::SharedFuture future)  // CHANGE
{
   RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Got the response!!!");
   auto result = future.get();
   RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Result: %d", result->status.error_code);
   printThreadID();
  
}


class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber(int a)
    : Node("minimal_subscriber")
    {
   
      client =  this->create_client<microscope_srvs::srv::SetLightColorMode>("set_colour_mode_service"); 
      auto request = std::make_shared<microscope_srvs::srv::SetLightColorMode::Request>();               // CHANGE
      // request->light_color_mode.light_color_mode = 1;// CHANGE
      request->light_color_mode.light_color_mode = a;// CHANGE
      request->light_color_mode.header.frame_id= "0";// CHANGE
      request->light_color_mode.header.stamp.sec= 10;// CHANGE
      request->light_color_mode.header.stamp.nanosec= 20;// CHANGE
      auto result = client->async_send_request(request,response_received_callback);
    }
 
    rclcpp::Client<microscope_srvs::srv::SetLightColorMode>::SharedPtr  client;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  int a= atoll(argv[1]);
  rclcpp::spin(std::make_shared<MinimalSubscriber>(a));
  rclcpp::shutdown();
  return 0;
}