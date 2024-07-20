#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <Eigen/Dense>
#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include "perception/Landmarks.h"
#include "perception/Observations.h"
#include "geometry_msgs/Polygon.h"
#include <cmath>
#include <random>
class Simulator {
public:
Simulator();
virtual ~Simulator();
void step( const double& dt );
double sample(const double& varience)const;
void handle_command( const geometry_msgs::Twist::ConstPtr& msg );
void update_observed_landmarks( void );
void update_observations( void );
void handle_landmarks( const perception::Landmarks::ConstPtr& msg );
void handle_obstacles( const geometry_msgs::Polygon::ConstPtr& msg );
int seen_before(int signature, bool selector);
nav_msgs::Odometry odometry_msg( void )const;
sensor_msgs::LaserScan scan_msg( void )const;
geometry_msgs::Polygon simulated_obstacles_msg( void )const;
perception::Landmarks& landmarks( void ){ return _landmarks; };
perception::Landmarks& observed_landmarks( void ){ return
_observed_landmarks; };
perception::Observations& observations( void ){ return _observations; };
geometry_msgs::Polygon& obstacles( void ){ return _obstacles; };
protected:
Eigen::Vector3d _x;
Eigen::Vector3d _u;
double _alpha1;
double _alpha2;
double _alpha3;
double _alpha4;
double _alpha5;
double _alpha6;
double _range_noise;
double _bearing_noise;
double _t;
unsigned _num_scan_angles;
perception::Landmarks _landmarks;
perception::Landmarks _observed_landmarks;
perception::Observations _observations;
geometry_msgs::Polygon _obstacles;
double _observationMaxRange;
double _observationMaxAngle;
//std::default_random_engine re;
};
#endif /* SIMULATOR_H */
