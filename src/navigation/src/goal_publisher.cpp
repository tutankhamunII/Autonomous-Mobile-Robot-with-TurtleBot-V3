#include <iostream>
#include "ros/ros.h"
#include "geometry_msgs/Point32.h"

using namespace std;

int main( int argc, char* argv[] ){

	geometry_msgs::Point32 goal;
	goal.x = 4.0;
	goal.y = 5.0;
	goal.z = 0.1;
	ros::init( argc, argv, "goal_publisher" );
	ros::NodeHandle node_handle;
	ros::Publisher goal_publisher = node_handle.advertise< geometry_msgs::Point32 >( "goal", 1, true );
	sleep(2);
	goal_publisher.publish( goal );
	sleep(1);
	return 0;

}

