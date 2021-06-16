#ifndef KONGKONG_H
#define KONGKONG_H

#include <rqt_gui_cpp/plugin.h>
#include <kongkong_gui/ui_kongkong_gui.h>
#include <QWidget>
#include <std_msgs/Bool.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/JointState.h>
#include <iostream>

#include <ros/ros.h>

#define PI 3.14159265359
#define deg2rad(deg)  ((deg) * PI / 180.0)
#define rad2deg(rad)  ((rad) * 180.0 / PI)

namespace kongkong_gui {

class KongKongPlugin
  : public rqt_gui_cpp::Plugin
{
  Q_OBJECT
public:
  KongKongPlugin();
  int TOTALDOF;
  virtual void initPlugin(qt_gui_cpp::PluginContext& context);
  virtual void shutdownPlugin();
  virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const;
  virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings);

  //ros::Publisher myPub;
  //std_msgs::Float32 myMsg;
  ros::Subscriber jointstates_Sub;
  void subCallback(const sensor_msgs::JointStateConstPtr &msg);
  
  ros::Publisher myJoint;
  ros::Publisher vrep_sim_start_pub_;
  ros::Publisher vrep_sim_stop_pub_;
  ros::Publisher exec_pub_;
  

protected slots:
  virtual void sendbutton();
  virtual void simstartbutton();
  virtual void simstopbutton();
  virtual void sendinitbutton();

//signals:
  // Comment in to signal that the plugin has a way to configure it
  //bool hasConfiguration() const;
  //void triggerConfiguration();
private:
  Ui::KongKongGuiWidget ui_;
  QWidget* widget_;
  ros::NodeHandle nh_;
};
} // namespace

#endif // my_namespace__my_plugin_H
