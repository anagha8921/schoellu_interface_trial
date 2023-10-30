cmake_minimum_required(VERSION 3.8)
project(schoellu_interface_trial)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)


#...
find_package(microscope_srvs REQUIRED)        # CHANGE
find_package(microscope_msgs REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)


add_executable(server src/server.cpp)
ament_target_dependencies(server
  rclcpp microscope_srvs microscope_msgs)                      #CHANGE

add_executable(client src/client.cpp)
ament_target_dependencies(client
  rclcpp microscope_srvs)                      #CHANGE

install(TARGETS
  server
  client
  DESTINATION lib/${PROJECT_NAME})

ament_package()
