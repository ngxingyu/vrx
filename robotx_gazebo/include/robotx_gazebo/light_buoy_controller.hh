#pragma once

#include <gazebo/gazebo.hh>
#include <ros/ros.h>
#include <std_msgs/ColorRGBA.h>
#include <std_srvs/Trigger.h>

/// \brief Controls the RobotX light buoy (scan the code challenge)
/// 
/// Selects a random sequence of 3 colors selected from red, green, blue, and yellow
/// without consecutive repeats. This sequence is displayed simultaneously on the light buoy's
/// 3 panels, each for 1 second, followed by a second with the panels off. A new sequence
/// can be generated by calling a ROS service. Be be configured with the following sdf tags:
/// <robotNamespace> ROS namespace of Node, can be used to have multiple light buoys
class LightBuoyController : public gazebo::ModelPlugin
{
public:
  void Load(gazebo::physics::ModelPtr _parent, sdf::ElementPtr _sdf);
private:
  /// \brief Creates a std_msgs::ColorRGBA message from 4 doubles
  static std_msgs::ColorRGBA CreateColor(double _r, double _g, double _b, double _a);
  // The 4 colors (plus OFF) that can be displayed
  static const std_msgs::ColorRGBA RED;
  static const std_msgs::ColorRGBA GREEN;
  static const std_msgs::ColorRGBA BLUE;
  static const std_msgs::ColorRGBA YELLOW;
  static const std_msgs::ColorRGBA OFF;
  using colors_t = std::pair<std_msgs::ColorRGBA, std::string>;
  /// \brief List of the color options with their string name for logging
  static const colors_t COLORS[5];
private:
  /// \brief display the next color in the sequence, or start over if at the end
  void IncrementState(const ros::TimerEvent& _event);
  /// \brief Callback for change pattern service, calls other changePattern internaly
  bool ChangePattern(std_srvs::Trigger::Request& _req, std_srvs::Trigger::Response& _res);
  /// \brief Generate a new pattern and reset state to OFF
  void ChangePattern(std::string& _message);

  /// \brief Publisher to set color to each of the 3 panels using the gazebo_ros_color plugin
  ros::Publisher panelPubs[3];
  /// \brief Node handle
  ros::NodeHandle nh;
  /// \brief Service to generate and display a new color sequence
  ros::ServiceServer changePatternServer;
  /// \brief Timer triggered every 1 second (in simulated time) to update the color
  ros::Timer timer;
  /// \brief Track current index in pattern
  uint8_t state;
  /// \brief The current pattern to display, pattern_[3] is always OFF
  using pattern_t = std::array<uint8_t, 4>;
  pattern_t pattern;
  /// \brief Locks state_ and pattern_
  std::mutex mutex;
};
