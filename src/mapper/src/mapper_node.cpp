#include "mapper/ocmap.h"
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "nav_msgs/Odometry.h"
#include "nav_msgs/OccupancyGrid.h"

int main(int argc, char* argv[]){
	ros::init(argc, argv, "mapper_node");
	ros::NodeHandle node_handle;
	OCMap ocmap_obj;
	ros::Publisher updated_map = node_handle.advertise<nav_msgs::OccupancyGrid>("map",1,true);
	ros::Subscriber laser_data = node_handle.subscribe("scan", 1, &OCMap::handle_laser, &ocmap_obj);
	ros::Subscriber odom_data = node_handle.subscribe("odom", 1, &OCMap::handle_odom, &ocmap_obj);
	double frequency = 50;
	ros::Rate timer(frequency);
	while(ros::ok()){
		ocmap_obj.update(ocmap_obj._odom.pose.pose, ocmap_obj._laser); 
		updated_map.publish(ocmap_obj.ocmap);
		ros::spinOnce();
		timer.sleep();
	}
	return 0;

}
