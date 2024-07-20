#include <iostream>
#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "localization/ekf_slam_localization.h"

using namespace std;

int main( int argc, char* argv[] ){

Eigen::VectorXd alpha = Eigen::VectorXd::Zero( 6 );
alpha( 0 ) = 0.005;
alpha( 1 ) = 0.005;
alpha( 2 ) = 0.005;
alpha( 3 ) = 0.005;
alpha( 4 ) = 0.005;
alpha( 5 ) = 0.005;

Eigen::MatrixXd q = Eigen::MatrixXd::Zero( 3, 3 );
q( 0, 0 ) = 0.05 * 0.05;
q( 1, 1 ) = 0.05 * 0.05;
q( 2, 2 ) = 0.05 * 0.05;

EKF_Localization ekf_localization( alpha, q );
ros::init( argc, argv, "ekf_slam_localization_node" );
ros::NodeHandle node_handle;

//ros::Subscriber velocity_subscriber = node_handle.subscribe("cmd_vel_mux/input/navi", 1, &EKF_Localization::handle_command, &ekf_localization);
ros::Subscriber odometry_subscriber = node_handle.subscribe("odom", 1, &EKF_Localization::handle_odometry, &ekf_localization);
//ros::Subscriber landmarks_subscriber = node_handle.subscribe("landmarks",1, &EKF_Localization::handle_landmarks, &ekf_localization);
ros::Subscriber observations_subscriber = node_handle.subscribe("observations", 1, &EKF_Localization::handle_observations, &ekf_localization);
ros::Publisher estimated_odometry_publisher = node_handle.advertise<nav_msgs::Odometry >("estimated_odom", 1, true);

ekf_localization._u.linear.x = 0.4;
ekf_localization._u.angular.z = -0.4;

perception::Observation obv1;
perception::Observation obv2;
perception::Observation obv3;
obv1.range = 5;
obv1.bearing = 1;
obv1.signature = 1;
obv2.range = 5;
obv2.bearing = -1;
obv2.signature = 2;
obv3.range = 9;
obv3.bearing = 2;
obv3.signature = 2;
perception::Observations arr;
arr.observations.push_back(obv1);
arr.observations.push_back(obv2);
//arr.observations.push_back(obv3);

ekf_localization._z = arr;

ekf_localization._sigma << 0.5000, 0.0100, 0.0100, 0.0100, 0.5000, 0.0100, 0.0100, 0.0100, 0.5000;

sleep( 1 );
double frequency = 10; //50.0;
ros::Rate timer( frequency );
while( ros::ok() ){
        ekf_localization.step( 1.0/frequency );
        estimated_odometry_publisher.publish( ekf_localization.estimated_odometry());
        ros::spinOnce();
        timer.sleep();
        }
return 0;
}

