#include <ros/ros.h>
#include <std_msgs/Int16MultiArray.h>
#include <tf/transform_datatypes.h>
#include <joyDrivers.h>
#include <stdio.h>
#define pi 3.14159265


joyStruct joystick;
int leftw,rightw;
std_msgs::Int16MultiArray twist;
ros::Publisher vel_pub_;
ros::Subscriber joy_sub_;





void joyCallback(sensor_msgs::Joy joy)
{
  joystick = driverXbox360Wired(joy);
  rightw = 200*joystick.RstickVer;
  leftw = 200*joystick.RstickVer;
  rightw+=50*joystick.LstickHor;
  leftw-=50*joystick.LstickHor;
  std::cout<<"Calc\n";
  twist.data.clear();
  twist.data.push_back(leftw);
  twist.data.push_back(rightw);
  twist.data.push_back(0);
  twist.data.push_back(0);
  // twist.data[1] = rightw;
  vel_pub_.publish(twist);


}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_turtle");
  ros::NodeHandle nh_;
  std::cout<<"Something"<<std::endl;

  /*twist.layout.dim = (std_msgs::MultiArrayDimension *)
  malloc(sizeof(std_msgs::MultiArrayDimension)*2);
  twist.layout.dim[0].label = "height";
  twist.layout.dim[0].size = 4;
  twist.layout.dim[0].stride = 1;
  twist.layout.data_offset = 0;
  */
  
  

  vel_pub_ = nh_.advertise<std_msgs::Int16MultiArray>("/cmd", 10);
  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, joyCallback);
  ros::spin();
}