#include "ros/ros.h"
#include "geometry_msgs/Polygon.h"

geometry_msgs::Polygon _points;

void handle_points(const geometry_msgs::Polygon::ConstPtr &msg)
{
	_points = *msg;
}
int main(int argc, char* argv[]){

	ros::init(argc, argv, "executive_node");
	ros::NodeHandle node_handle;

	ros::Publisher waypoint = node_handle.advertise<geometry_msgs::Polygon>("waypoints_nav", 1, true);
	ros::Subscriber get_waypoiny = node_handle.subscribe("waypoints", 1, handle_points);

	double frequency = 1;
	ros::Rate timer(frequency);
	ros::spinOnce();
	sleep(2);
	while(ros::ok()){
		ros::spinOnce();
		waypoint.publish(_points);
	}

	return 0;
}
