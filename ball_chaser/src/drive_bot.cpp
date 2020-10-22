#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <ball_chaser/DriveToTarget.h>

class DriveBot{
  
	ros::Publisher motor_command_publisher;
  	ros::ServiceServer driveService;
  	ros::NodeHandle n;
  
  	public:
  
  		DriveBot()
        {
        	motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel",10);
          	driveService = n.advertiseService("/ball_chaser/command_robot",&DriveBot::handle_drive_request, this);
        }
  
  		bool handle_drive_request(ball_chaser::DriveToTarget::Request &req, ball_chaser::DriveToTarget::Response &res)
        {  
          	ROS_INFO("Received DriveToTarget request - linear.x: %1.2f, angular.z: %1.2f", req.linear_x, req.angular_z);
          
          	geometry_msgs::Twist motor_command;
          	motor_command.linear.x = req.linear_x;
          	motor_command.angular.z = req.angular_z;
          
          	motor_command_publisher.publish(motor_command);
          
//           	ros::Duration(0.15).sleep();
          	res.msg_feedback = "Motor commands set as follows - Linear_x: " + std::to_string(req.linear_x) + ", Angular_z: " + std::to_string(req.angular_z);
          
          	ROS_INFO_STREAM(res.msg_feedback);
          
          	return true;
        }
};

int main(int argc, char** argv)
{
	ros::init(argc, argv, "drive_bot");
  
  	DriveBot drive_robot;
  
  	ros::spin();
  	ROS_INFO("Ready to send motor commands");
  
  	return 0;
}
