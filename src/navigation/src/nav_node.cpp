#include <ros/ros.h>
#include "navigation/nav.h"


int main(int argc, char* argv[]){

	ros::init(argc, argv, "planning_node");
	ros::NodeHandle node_handle;

	navi nav_obj;
	ros::Subscriber map_subscriber = node_handle.subscribe("map", 1, &navi::handle_map, &nav_obj);
	ros::Subscriber odom_subscriber = node_handle.subscribe("estimated_odom", 1, &navi::handle_odom, &nav_obj);
	//ros::Subscriber odom_subscriber = node_handle.subscribe("odom", 1, &navi::handle_odom, &nav_obj);
	ros::Subscriber goal_subscriber = node_handle.subscribe("goal", 1, &navi::handle_goal, &nav_obj);
	ros::Publisher path_publisher = node_handle.advertise<geometry_msgs::Polygon>("path", 1, true);
	ros::Publisher command = node_handle.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/navi", 1, true);
	ros::Publisher lookahead_point = node_handle.advertise<geometry_msgs::Point32>("lookahead", 1, true);	
	double frequency = 10;
	ros::Rate timer( frequency );
	ros::spinOnce();
	sleep(3);
	while( ros::ok()){
			ros::spinOnce();	
			geometry_msgs::Polygon path = nav_obj.solve();
			path_publisher.publish(path);
		nav_obj.pure_pursuit();
		command.publish(nav_obj._command);
		//lookahead_point.publish(nav_obj._lookahead);
		
		ros::spinOnce();
		timer.sleep();
	}
	return 0;
}
