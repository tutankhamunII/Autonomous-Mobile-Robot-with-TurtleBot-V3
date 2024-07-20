#include <iostream>
#include "simulator/simulator.h"
//#include <cmath.h>
#include <random>
#include <time.h>
#include <chrono>
using namespace std;
/**
* x(0) = x position
* x(1) = y position
* x(2) = heading
* u(0) = linear velocity (v)
* u(1) = angular_velocity (w)
*/
geometry_msgs::Quaternion yaw_to_quaternion( const double& yaw ){

	geometry_msgs::Quaternion quaternion;
	quaternion.x = 0;
	quaternion.y = 0;
	quaternion.w = cos(yaw/2);
	quaternion.z = sin(yaw/2);
	return quaternion;
}

Simulator::Simulator() : _x( 0.0, 0.0, 0.0 ), _u( 0.0, 0.0, 0.0 ), _num_scan_angles(128) {
	
	_alpha1 = 0.008;
	_alpha2 = 0.008;
	_alpha3 = 0.008;
        _alpha4 = 0.008;
        _alpha5 = 0.008;
        _alpha6 = 0.008;
}
Simulator::~Simulator() {}

void Simulator::step( const double& dt ){
	
	if(_u(1) == 0){
		_u(1) = 0.00000001;
		//return? I don't think so what about pure linear motion?
	}
	float V_hat = _u(0) + sample(_alpha1 * _u(0) * _u(0) + _alpha2 * _u(1) * _u(1));
	float W_hat = _u(1) + sample(_alpha3 * _u(0) * _u(0) + _alpha4 * _u(1) * _u(1));
	float Y_hat = sample(_alpha5 * _u(0) * _u(0) + _alpha6 * _u(1) * _u(1));
	_x(0) = _x(0) + (-V_hat/W_hat * sin(_x(2))) + (V_hat/W_hat) * sin(_x(2) + W_hat * dt);
	_x(1) = _x(1) + (V_hat/W_hat * cos(_x(2))) - (V_hat/W_hat) * cos(_x(2) + W_hat * dt);
	_x(2) = _x(2) + (W_hat * dt + Y_hat * dt);
	if(_x(2) < -M_PI){
		_x(2) = _x(2) + 2 * M_PI;
	}
	else if(_x(2) > M_PI){
		_x(2) = _x(2) - 2 * M_PI;
	}
	return;
}

void Simulator::handle_obstacles( const geometry_msgs::Polygon::ConstPtr& msg ){
	
	_obstacles = *msg;
	return;
}

double Simulator::sample(const double& varience)const{
	double sampled = 0;
	std::default_random_engine re;
	re.seed(std::chrono::system_clock::now().time_since_epoch().count());
	//std::uniform_real_distribution<double> unif(-sqrt(3 * varience), sqrt(3 * varience));
	std::uniform_real_distribution<double> unif(-varience,varience);
	for(int x = 0; x < 12; x++){
	sampled += unif(re);
	}
	cout << 0.5 * sampled << endl;
	return 0.5 * sampled;
}

void Simulator::handle_command( const geometry_msgs::Twist::ConstPtr& msg ){
	
	_u( 0 ) = msg->linear.x;
	_u( 1 ) = msg->angular.z;
	return;
}

void Simulator::handle_landmarks(const perception::Landmarks::ConstPtr& msg){
	
	_landmarks = *msg;	
	return;
}

nav_msgs::Odometry Simulator::odometry_msg( void )const{
	
	nav_msgs::Odometry msg;
	msg.header.stamp = ros::Time::now();
	msg.pose.pose.position.x = _x( 0 );
	msg.pose.pose.position.y = _x( 1 );
	msg.pose.pose.position.z = 0.0;
	msg.pose.pose.orientation = yaw_to_quaternion( _x( 2 ) );
	msg.twist.twist.linear.x = _u( 0 );
	msg.twist.twist.angular.z = _u( 1 );
	return msg;
}

sensor_msgs::LaserScan Simulator::scan_msg( void )const{
	
	sensor_msgs::LaserScan msg;
	msg.angle_min = -M_PI/4.0;
	msg.angle_max = M_PI/4.0;
	msg.angle_increment = ( msg.angle_max - msg.angle_min ) / ( double )(_num_scan_angles - 1 );
	msg.range_min = 0.1;
	msg.range_max = 5.0;;
	vector< double > scan_angles( _num_scan_angles );
	for( unsigned int i = 0; i < _num_scan_angles; i++ ){
		scan_angles[i] = msg.angle_min + ( double )( i ) * msg.angle_increment;
	}
	vector< double > obstacle_angles( _obstacles.points.size() );
	vector< double > obstacle_distances( _obstacles.points.size() );
	vector< double > obstacle_phimaxs( _obstacles.points.size() );
	for( unsigned int i = 0; i < _obstacles.points.size(); i++ ){
		obstacle_angles[ i ] = atan2( _obstacles.points[ i ].y - _x( 1 ),_obstacles.points[ i ].x - _x( 0 ) ) - _x( 2 );
		if( obstacle_angles[ i ] < -M_PI ){
			obstacle_angles[ i ] += 2.0 * M_PI;
		} else if ( obstacle_angles[ i ] > M_PI ){
			obstacle_angles[ i ] -= 2.0 * M_PI;
		}
	
	obstacle_distances[ i ] = sqrt( pow( _obstacles.points[ i ].x - _x( 0 ),2.0 ) + pow( _obstacles.points[ i ].y - _x( 1 ), 2.0 ) );

	if( obstacle_distances[ i ] < _obstacles.points[ i ].z ){
		return msg;
	}
	obstacle_phimaxs[ i ] = atan2( _obstacles.points[ i ].z, sqrt( pow(
	obstacle_distances[ i ], 2.0 ) - pow( _obstacles.points[ i ].z, 2.0 )));
	}
	for( unsigned int i = 0; i < scan_angles.size(); i++ ){
		double min_range = msg.range_max;
			for( unsigned int j = 0; j < _obstacles.points.size(); j++ ){
				if( obstacle_distances[ j ] < ( msg.range_max + _obstacles.points[ j ].z)){
					if( ( scan_angles[ i ] > ( obstacle_angles[ j ] - obstacle_phimaxs[ j] ) ) && ( scan_angles[ i ] < ( obstacle_angles[ j ] +obstacle_phimaxs[ j ] ) ) ){
						double phi = scan_angles[ i ] - obstacle_angles[ j ];
						double a = 1.0 + pow( tan( phi ), 2.0 );
						double b = -2.0 * obstacle_distances[ j ];
						double c = pow( obstacle_distances[ j ], 2.0 ) - pow( _obstacles.points[ j ].z, 2.0 );

						double x1 = ( -b + sqrt( pow( b, 2.0 ) - 4 * a * c ) ) / ( 2.0 * a );
						double y1 = tan( phi ) * x1;
						double d1squared = pow( x1, 2.0 ) + pow( y1, 2.0 );
						double x2 = ( -b - sqrt( pow( b, 2.0 ) - 4 * a * c ) ) / ( 2.0 * a );
						double y2 = tan( phi ) * x2;
						double d2squared = pow( x2, 2.0 ) + pow( y2, 2.0 );
						double range = 0.0;
						if( d1squared < d2squared ){
							range = sqrt( d1squared );
						} else {
							range = sqrt( d2squared );
						}
						if( range < min_range ){
							min_range = range;
				}
			}		
		}
	}
	if( min_range > msg.range_min ){
		msg.ranges.push_back( std::min( min_range + sample( 0.001 ), ( double )(msg.range_max ) ) );
	} else {
		msg.ranges.push_back( 0.0 );
		}
	}
	return msg;
}

geometry_msgs::Polygon Simulator::simulated_obstacles_msg( void )const{
	
	return _obstacles;
}

int Simulator::seen_before(int signature, bool selector){
	
	if(selector){
		
		for(int i = 0; i < _observations.observations.size(); i++){
			if(_observations.observations[i].signature == signature){
				return i;
			}
		}
		return 0;
	}
	else{
		for(int i = 0; i < _observed_landmarks.landmarks.size(); i++){
                        if(_observed_landmarks.landmarks[i].signature == signature){
                                return i;
                        }
                }
		return 0;
	}
}

void Simulator::update_observations(){
	
	for(int i = 0; i < _landmarks.landmarks.size(); i++){
		
		perception::Observation temp;
		float x_relative =_landmarks.landmarks[i].x - _x(0);
		float y_relative =_landmarks.landmarks[i].y - _x(1);
		temp.range = sqrt(pow(x_relative, 2) + pow(y_relative, 2));
		temp.bearing = atan2(y_relative, x_relative) - _x(2);
		temp.signature = _landmarks.landmarks[i].signature;
		int seen = seen_before(_landmarks.landmarks[i].signature, true);
                if(seen){

                        _observations.observations[seen].range = temp.range;
			_observations.observations[seen].bearing = temp.bearing;
                }
		else{
			_observations.observations.push_back(temp);
		}

	}
	return;
}

void Simulator::update_observed_landmarks(){
	
	for(int i = 0; i < _observations.observations.size(); i++){
		if(seen_before(_observations.observations[i].signature, false) == true){
			continue;
		}
		perception::Landmark temp;
		float range = _observations.observations[i].range;
		float bearing = _observations.observations[i].bearing;
		temp.x = _x(0) + range * cos(bearing + _x(2));
		temp.y = _x(1) + range * sin(bearing + _x(2));
		temp.signature = _observations.observations[i].signature;
		_observed_landmarks.landmarks.push_back(temp);
	}
}
