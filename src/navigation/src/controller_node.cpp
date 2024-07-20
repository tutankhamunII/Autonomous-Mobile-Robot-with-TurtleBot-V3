#include "ros/ros.h"
#include "geometry_msgs/Polygon.h"
#include "navigation/nav.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Point32.h"

int main(int argc, char* argv[]){
	
	ros::init(argc, argv, "controller_node");
	ros::NodeHandle node_handle;
	ros::Publisher vel_publisher = node_handle.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/navi", 1, true);
	ros::Publisher LD_point = node_handle.advertise<geometry_msgs::Point32>("lookahead", 1, true);

	sleep( 1 );
	double frequency = 10;
	ros::Rate timer( frequency );
	while( ros::ok() ){
        	
		ros::spinOnce();
		geometry_msgs::Twist vel;
		geometry_msgs::Point32 la;
		std::vector<double> data = pure_pursuit();
		
		vel.linear.x = data[0];
		vel.angular.z = data[1];
		la.x = data[2];
		la.y = data[3];
		la.z = data[4];
		
		vel_publisher.publish(vel);
		LD_point.publish(la);
        	timer.sleep();
        }
	return 0;
}
