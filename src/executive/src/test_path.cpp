#include "ros/ros.h"
#include "geometry_msgs/Polygon.h"
#include "geometry_msgs/Point32.h"
int main(int argc, char* argv[]){
	
	ros::init(argc, argv, "test_path");
	ros::NodeHandle node_handle;
	
	geometry_msgs::Polygon path;
	geometry_msgs::Point32 point1;
	geometry_msgs::Point32 point2;
	geometry_msgs::Point32 point3;
	geometry_msgs::Point32 point4;
	geometry_msgs::Point32 point5;
	geometry_msgs::Point32 point6;
        geometry_msgs::Point32 point7;
        geometry_msgs::Point32 point8;
        geometry_msgs::Point32 point9;
        geometry_msgs::Point32 point10;

	point1.x = 0;
	point1.y = 0;
	point1.z = 0;

	point2.x = 1;
        point2.y = 0;
        point2.z = 0;

	point3.x = 2;
        point3.y = 0;
        point3.z = 0;

	point4.x = 3;
        point4.y = 0;
        point4.z = 0;

	point5.x = 3;
        point5.y = 3;
        point5.z = 0;

	point6.x = 4;
        point6.y = 4;
        point6.z = 0;

	point7.x = 5;
        point7.y = 5;
        point7.z = 0;
	
	point8.x = 5;
        point8.y = 6;
        point8.z = 0;

	point9.x = 5;
        point9.y = 7;
        point9.z = 0;
	
	point10.x = 5;
        point10.y = 8;
        point10.z = 0;


	path.points.push_back(point1);
	path.points.push_back(point2);
	path.points.push_back(point3);
	path.points.push_back(point4);
	path.points.push_back(point5);
	path.points.push_back(point6);
        path.points.push_back(point7);
        path.points.push_back(point8);
        path.points.push_back(point9);
        path.points.push_back(point10);

	ros::Publisher path_pub = node_handle.advertise<geometry_msgs::Polygon>("path", 1, true);

	sleep(3);

	path_pub.publish(path);

	sleep(1);
	return 0;


}
