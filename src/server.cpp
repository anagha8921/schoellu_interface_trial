#include "rclcpp/rclcpp.hpp"
#include "microscope_srvs/srv/set_light_color_mode.hpp"
#include "microscope_msgs/msg/light_color_mode.hpp"
// #include "tutorial_interfaces/msg/service.hpp"


#include <memory>

void set_colour_mode(const std::shared_ptr<microscope_srvs::srv::SetLightColorMode::Request> request,     // CHANGE
          std::shared_ptr<microscope_srvs::srv::SetLightColorMode::Response> response)  // CHANGE
{
   RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %ld",   // CHANGE
                request->light_color_mode.light_color_mode);
  std::string error_meta[3];
  std::vector<std::string> myVector;
  if(request->light_color_mode.light_color_mode==0)
  {
   error_meta[0] = "fluorescence_overlay_mode";
   myVector.assign(std::begin(error_meta), std::end(error_meta));

   response->status.error_code=0;
   response->status.error_message="SUCCESS";  
   response->status.error_meta=myVector;                                                               
   RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Colour mode set to fluorescence_overlay_mode: [%ld]", (long int)response->status.error_code);  
  }
  else{ 
   error_meta[0] = "whitelight_color_mode";
    myVector.assign(std::begin(error_meta), std::end(error_meta));
   response->status.error_code=1;
   response->status.error_message="SUCCESS";  
   response->status.error_meta=myVector;                                                               
   RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Colour mode set to whitelight_color_mode: [%ld]", (long int)response->status.error_code);  
  }
 
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("client");  // CHANGE

    // rclcpp::Service<microscope_srvs::srv::SetLightColorMode>::SharedPtr set_colour_mode=                 // CHANGE
    // node->create_service<microscope_srvs::srv::SetLightColorMode>("set_colour_mode_service",set_colour_mode);     // CHANGE
    auto set_colour_mode_service = node->create_service<microscope_srvs::srv::SetLightColorMode>(
        "set_colour_mode_service",
        set_colour_mode  // Pass the callback function directly
    );

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to set Colour mode....");      // CHANGE

  rclcpp::spin(node);
  rclcpp::shutdown();
}