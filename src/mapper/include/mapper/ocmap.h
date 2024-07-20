#ifndef OCMAP_H
#define OCMAP_H

#include <iostream>
#include <vector>
#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "sensor_msgs/LaserScan.h"
#include "nav_msgs/OccupancyGrid.h"

class OCMap {

public:
	//functions
	OCMap( const double& discretizationArg = 0.1, const unsigned int& numRowsArg = 256, const unsigned int& numColsArg = 256 );
	virtual ~OCMap();
	bool checkMap( const double& x, const double& y, const double& radius,const double& threshold );
	void update( const geometry_msgs::Pose& pose, const sensor_msgs::LaserScan& laserScan );
	void handle_laser(const sensor_msgs::LaserScan::ConstPtr &msg);
	void handle_odom(const nav_msgs::Odometry::ConstPtr &msg);
	//variables
	nav_msgs::OccupancyGrid ocmap;
	double discretization;
	std::vector< double > xs;
	std::vector< double > ys;
	double l0;
	double locc;
	double lfree;
	nav_msgs::Odometry _odom;
	sensor_msgs::LaserScan _laser;
};
std::ostream& operator<<( std::ostream& out, const OCMap& other );

#endif /* OCMAP_H */
