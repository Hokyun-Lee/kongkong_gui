#include "kongkong_gui/kongkong_gui.h"
#include <pluginlib/class_list_macros.h>
#include <QStringList>

namespace kongkong_gui {

KongKongPlugin::KongKongPlugin()
  : rqt_gui_cpp::Plugin()
  , widget_(0)
{
  TOTALDOF = 4;
  // Constructor is called first before initPlugin function, needless to say.

  // give QObjects reasonable names
  setObjectName("KongKongPlugin");
}

void KongKongPlugin::initPlugin(qt_gui_cpp::PluginContext& context)
{
  // access standalone command line arguments
  QStringList argv = context.argv();
  // create QWidget
  widget_ = new QWidget();
  // extend the widget with all attributes and children from UI file
  ui_.setupUi(widget_);
  // add widget to the user interface
  context.addWidget(widget_);

  jointstates_Sub = nh_.subscribe("/kongkong/joint_states", 100, &KongKongPlugin::subCallback, this);
  //myPub = nh_.advertise<std_msgs::Float32>("/test",100);

  connect(ui_.SendButton, SIGNAL(clicked()), this, SLOT(sendbutton()));
  connect(ui_.SimStartButton, SIGNAL(clicked()), this, SLOT(simstartbutton()));
  connect(ui_.SimStopButton, SIGNAL(clicked()), this, SLOT(simstopbutton()));
  connect(ui_.SendInitButton, SIGNAL(clicked()), this, SLOT(sendinitbutton()));

  myJoint = nh_.advertise<sensor_msgs::JointState>("/guiparam",1);
  vrep_sim_start_pub_ = nh_.advertise<std_msgs::Bool>("/startSimulation", 5);
  vrep_sim_stop_pub_ = nh_.advertise<std_msgs::Bool>("/stopSimulation", 5);
  exec_pub_ = nh_.advertise<std_msgs::Float32>("/exec_time",1);
}

void KongKongPlugin::sendbutton()
{
  // std::cout << "Moo ya ho~~!" << std::endl;
  // ui_.myLabel->setText(QString::fromUtf8("Muyaho"));

  // myMsg.data = ui_.lineEdit->text().toFloat();
//   myPub.publish(myMsg);
  std::cout << "Send Button" << std::endl;
  sensor_msgs::JointState msg;
  msg.position.resize(TOTALDOF);
  msg.position[0] = ui_.lineEdit_0->text().toFloat();
  msg.position[1] = ui_.lineEdit_1->text().toFloat();
  msg.position[2] = ui_.lineEdit_2->text().toFloat();
  msg.position[3] = ui_.lineEdit_3->text().toFloat();
  myJoint.publish(msg);

  std_msgs::Float32 exec;
  exec.data = ui_.Exec_Time->text().toFloat();
  exec_pub_.publish(exec);
  // std::cout << "exec: " << ui_.Exec_Time->text().toFloat() << std::endl;
}

void KongKongPlugin::simstartbutton()
{
  std::cout << "Sim Start Button" << std::endl;
  std_msgs::Bool msg;
  msg.data = true;
  vrep_sim_start_pub_.publish(msg);
}

void KongKongPlugin::simstopbutton()
{
  std::cout << "Sim Stop Button" << std::endl;
  std_msgs::Bool msg;
  msg.data = true;
  vrep_sim_stop_pub_.publish(msg);  
}

void KongKongPlugin::sendinitbutton()
{
  std::cout << "Send Init Button" << std::endl;
  sensor_msgs::JointState msg;
  msg.position.resize(TOTALDOF);
  msg.position[0] = 0;
  msg.position[1] = 0;
  msg.position[2] = 0;
  msg.position[3] = 0;
  myJoint.publish(msg);

  std_msgs::Float32 exec;
  exec.data = ui_.Exec_Time->text().toFloat();
  exec_pub_.publish(exec);
}

void KongKongPlugin::subCallback(const sensor_msgs::JointStateConstPtr &msg)
{
  // std::cout << "subcallback" << std::endl;
  ui_.label_0->setText(QString::number(rad2deg(msg->position[0])));
  ui_.label_1->setText(QString::number(rad2deg(msg->position[1])));
  ui_.label_2->setText(QString::number(rad2deg(msg->position[2])));
  ui_.label_3->setText(QString::number(rad2deg(msg->position[3])));
}

void KongKongPlugin::shutdownPlugin()
{
  // TODO unregister all publishers here
}

void KongKongPlugin::saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const
{
  // TODO save intrinsic configuration, usually using:
  // instance_settings.setValue(k, v)
}

void KongKongPlugin::restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings)
{
  // TODO restore intrinsic configuration, usually using:
  // v = instance_settings.value(k)
}

/*bool hasConfiguration() const
{
  return true;
}

void triggerConfiguration()
{
  // Usually used to open a dialog to offer the user a set of configuration
}*/

} // namespace

PLUGINLIB_EXPORT_CLASS(kongkong_gui::KongKongPlugin, rqt_gui_cpp::Plugin)