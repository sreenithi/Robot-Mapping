#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <ball_chaser/DriveToTarget.h>

class ProcessImage
{
	ros::Subscriber sub1;
  	ros::ServiceClient client;
  	ros::NodeHandle n;
	bool moving;
  
  	public:
  
  		ProcessImage()
        {
        	sub1 = n.subscribe<sensor_msgs::Image>("/camera/rgb/image_raw", 10, &ProcessImage::process_image_callback, this);
          	client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
          	moving = false;
        }
  
  		void drive_robot(float lin_x, float ang_z)
        {
          	ROS_INFO("Driving robot with requested velocities");
        	ball_chaser::DriveToTarget srv;
          	srv.request.linear_x = lin_x;
          	srv.request.angular_z = ang_z;
          
          	if(! client.call(srv))
              ROS_ERROR("Failed to call service /ball_chaser/command_robot");
        }
  
  		void process_image_callback(const sensor_msgs::Image img)
        {
        	int white_pixel = 255;
          	int one_third = (int) (img.step / 3);
          	int direction = -1; 

          
          	for(int i = 0; i < img.height * img.step; i+=3)
            {              
              	if((img.data[i] == white_pixel) && (img.data[i+1] == white_pixel) && (img.data[i+2] == white_pixel))
                {
                    //to check if the ball is in the left, middle or right, 
                    //divide the image into 3 and check the white pixel number
                    //calculate and decide in which 'third' of the image the pixel falls
                  	if((i % img.step) < one_third)
                      	direction = 0;
                    else if((i % img.step) < (one_third*2))
                      	direction = 1;
                    else
                      	direction = 2;
                  	break;
                }
            }
          
          	switch(direction)
            {
              	case 0: drive_robot(0, 0.5);
                		moving = true;
                		break;
                case 1: drive_robot(0.5, 0);
                		moving = true;
                		break;
                case 2: drive_robot(0, -0.5);
                		moving = true;
                		break;
              	default: if(moving)
                  			drive_robot(0,0);
                			moving = false;
            }
        }
  
};

int main(int argc, char** argv)
{
	ros::init(argc, argv, "process_image");
  
  	ProcessImage piObj;
  
  	ros::spin();
}