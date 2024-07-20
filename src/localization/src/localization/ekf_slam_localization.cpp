#include "localization/ekf_slam_localization.h"
#include "geometry_msgs/Point.h"
#include <cmath>
using namespace std;

geometry_msgs::Quaternion yaw_to_quaternion( const double& yaw ){
	geometry_msgs::Quaternion quaternion;
	quaternion.w = cos( yaw / 2.0 );
	quaternion.x = 0.0;
	quaternion.y = 0.0;
	quaternion.z = sin( yaw / 2.0 );
	return quaternion;
}

EKF_Localization::EKF_Localization( const Eigen::VectorXd& alpha,const Eigen::MatrixXd& q ) : _u(),_z(),_mu( Eigen::VectorXd::Zero(3)),
_sigma( Eigen::MatrixXd::Zero(3, 3)),_alpha( alpha ),_q( q ) {

	_sigma(0,0) = 0.005000;
	_sigma(1,1) = 0.005000;
	_sigma(2,2) = 0.005000;

	//////for testin only/////
	//_u.linear.x = 0.5;
	//_u.angular.z = 0.5;
}

EKF_Localization::~EKF_Localization() {}

void EKF_Localization::handle_command( const geometry_msgs::Twist::ConstPtr& msg ){
	_u = *msg;
	return;
}

void EKF_Localization::handle_odometry( const nav_msgs::Odometry::ConstPtr& msg ){
	_u = msg->twist.twist;
	return;
}

void EKF_Localization::handle_landmarks( const perception::Landmarks::ConstPtr& msg ){
	_mu.conservativeResize(_mu.size() + 3 * msg  -> landmarks.size());
	_sigma.conservativeResizeLike(Eigen::MatrixXd::Zero(_mu.size(), _mu.size()));
	int temp_idx = 3;
	for( unsigned int i = 0; i < msg->landmarks.size(); i++ ){
		_mu(temp_idx) = msg -> landmarks[i].x;
		_mu(temp_idx +1) = msg -> landmarks[i].y;
		_mu(temp_idx +2) = msg -> landmarks[i].signature;
		_sigma(temp_idx, temp_idx) = 0.01; //assuming small noise since these are given landmarks.
		_sigma(temp_idx + 1, temp_idx + 1) = 0.01;
		_sigma(temp_idx + 2, temp_idx + 2) = 0.01;
		temp_idx += 3;
	}
		return;
}


void EKF_Localization::handle_observations( const perception::Observations::ConstPtr& msg ){
	_z = *msg;
	return;
	}

void EKF_Localization::step( const double& dt ){
// implement motion model step for time dt (make sure to account for zero angular velocity)
	Eigen::VectorXd temp_mu = _mu;
        Eigen::MatrixXd temp_sigma = _sigma;
	Eigen::MatrixXd Fx = Eigen::MatrixXd::Zero(3, 3 + 3 * (temp_mu.size() - 3)/3);
	Eigen::MatrixXd identity = Eigen::MatrixXd::Identity(Fx.cols(), Fx.cols());
	Eigen::MatrixXd Mt = Eigen::MatrixXd::Zero(2,2);
	Eigen::MatrixXd Vt = Eigen::MatrixXd::Zero(3,2);
	Eigen::MatrixXd Gjacobian = Eigen::MatrixXd::Zero(3,3);
	Eigen::VectorXd motion_model(3);

	Fx(0,0) = 1;
	Fx(1,1) = 1;
	Fx(2,2) = 1;

	if(_u.angular.z == 0){
		_u.angular.z = 0.000000001;
	}

	motion_model(0) = -(_u.linear.x/_u.angular.z) * sin(_mu(2)) + (_u.linear.x/_u.angular.z) * sin(_mu(2) + _u.angular.z * dt);
        motion_model(1) = (_u.linear.x/_u.angular.z) * cos(_mu(2)) - (_u.linear.x/_u.angular.z) * cos(_mu(2) + _u.angular.z * dt);
        motion_model(2) =  _u.angular.z * dt;
	

	Gjacobian(0,2) = -(_u.linear.x/_u.angular.z) * cos(_mu(2)) + (_u.linear.x/_u.angular.z) * cos(_mu(2) + _u.angular.z * dt);
	Gjacobian(1,2) = -(_u.linear.x/_u.angular.z) * sin(_mu(2)) + (_u.linear.x/_u.angular.z) * sin(_mu(2) + _u.angular.z * dt);
	
	Mt(0,0) = _alpha(0) * (_u.linear.x * _u.linear.x) + _alpha(1) * (_u.angular.z * _u.angular.z);
	Mt(1,1) = _alpha(2) * (_u.linear.x * _u.linear.x) + _alpha(3) * (_u.angular.z * _u.angular.z);
	
	Vt(0,0) = (-sin(temp_mu(2)) + sin(temp_mu(2) + _u.angular.z * dt)) / _u.angular.z;
	Vt(1,0) = (cos(temp_mu(2)) - cos(temp_mu(2) + _u.angular.z * dt)) / _u.angular.z;
	Vt(0,1) = ((_u.linear.x * (sin(temp_mu(2)) - sin(temp_mu(2) + _u.angular.z * dt))) / (_u.angular.z * _u.angular.z)) + ((_u.linear.x * cos(temp_mu(2) + _u.angular.z * dt) * dt) / _u.angular.z);
	Vt(1,1) = (-(_u.linear.x * (cos(temp_mu(2)) - cos(temp_mu(2) + _u.angular.z * dt))) / (_u.angular.z * _u.angular.z)) + ((_u.linear.x * sin(temp_mu(2) + _u.angular.z * dt) * dt) / _u.angular.z);
	Vt(2,1) = dt;	

	Eigen::MatrixXd Rt = Vt * Mt * Vt.transpose();

	temp_mu = temp_mu + (Fx.transpose() * motion_model);
	
	Eigen::MatrixXd Gt = identity + (Fx.transpose() * Gjacobian * Fx);
	
	temp_sigma = Gt * temp_sigma * Gt.transpose() + Fx.transpose() * Rt * Fx;
	
	for(unsigned int itr = 0; itr < _z.observations.size(); itr++){ 
// implement measurement model step for all observations
		bool flag = true;
		int landmark_last_index = 0;
		for(int check = 5; check < temp_mu.size(); check += 3){
			if(_z.observations[itr].signature == temp_mu(check)){
				flag = false;
				std::cout << "I saw this! " << _z.observations[itr] << std::endl;
				landmark_last_index = check;
				break;
			}
		}
		if(flag){
			std::cout << "new:  " << _z.observations[itr] << std::endl;

			int last_index = temp_mu.size();
			int sigma_rows = temp_sigma.rows();
			int sigma_cols = temp_sigma.cols();

			temp_mu.conservativeResize(temp_mu.size() + 3);
			temp_sigma.conservativeResizeLike(Eigen::MatrixXd::Zero(temp_mu.size(), temp_mu.size()));
			
			temp_mu(last_index) = temp_mu(0) + _z.observations[itr].range * cos(_z.observations[itr].bearing + temp_mu(2));
			temp_mu(last_index + 1) = temp_mu(1) + _z.observations[itr].range * sin(_z.observations[itr].bearing + temp_mu(2));
			temp_mu(last_index + 2) = _z.observations[itr].signature;
			
			temp_sigma(sigma_rows, sigma_cols) = 1000000; // assuming high initial noise.
			temp_sigma(sigma_rows + 1, sigma_cols + 1) = 1000000;
			temp_sigma(sigma_rows + 2, sigma_cols + 2) = 1000000;
					
			landmark_last_index = last_index + 2;
			
		}
			
		float landmark_x = temp_mu(landmark_last_index - 2);
		float landmark_y = temp_mu(landmark_last_index - 1);
		int landmark_signature = temp_mu(landmark_last_index);

		Eigen::VectorXd current_z (3);
		current_z << _z.observations[itr].range, _z.observations[itr].bearing, _z.observations[itr].signature;


		Eigen::VectorXd delta (2);
		delta << landmark_x - temp_mu(0), landmark_y - temp_mu(1);
		//std::cout << "before delta" << std::endl;
		double temp_q = delta.transpose() * delta;
		
		//std::cout << "after delta" << std::endl;

		Eigen::VectorXd predicted_z (3);
		predicted_z << sqrt(temp_q), atan2(delta(1), delta(0)) - temp_mu(2), _z.observations[itr].signature;
		//std::cout << "here2" << std::endl;
		int Fxj_columns = 3 * (temp_mu.size() - 3)/3 + 3;
		Eigen::MatrixXd Fxj = Eigen::MatrixXd::Zero(6, Fxj_columns);

		Fxj(0,0) = 1;
		Fxj(1,1) = 1;
		Fxj(2,2) = 1;
		Fxj(3, 3 + (3 * (itr + 1) - 3)) = 1;
                Fxj(4, 4 + (3 * (itr + 1) - 3)) = 1;
                Fxj(5, 5 + (3 * (itr + 1) - 3)) = 1;
		std::cout << "here2004" << std::endl;
		Eigen::MatrixXd Hjacobian = Eigen::MatrixXd::Zero(3,6);
		Hjacobian << -sqrt(temp_q)*delta(0), -sqrt(temp_q)*delta(1), 0, sqrt(temp_q)*delta(0), sqrt(temp_q)*delta(1), 0,
			     delta(1), -delta(0), -temp_q, -delta(1), delta(0), 0,
			     0, 0, 0, 0, 0, temp_q;
		Eigen::MatrixXd Ht = 1/temp_q * Hjacobian * Fxj;			
		Eigen::MatrixXd temp_vec = (Ht * temp_sigma * Ht.transpose()) + _q;
		
		Eigen::MatrixXd kalman_gain = temp_sigma * Ht.transpose() * temp_vec.inverse();
		temp_mu = temp_mu + kalman_gain * (current_z - predicted_z);
		
		Eigen::MatrixXd identity2 = Eigen::MatrixXd::Identity(kalman_gain.rows(), Ht.cols());
		temp_sigma = ( identity2 - kalman_gain * Ht) * temp_sigma;
		std::cout << "DONE!" << std::endl;
	}
// clear past observations
	_mu = temp_mu;
	_sigma = temp_sigma;
	std::cout << "mean: " << std::endl << _mu << std::endl;
	//std::cout << "cov: " << std::endl << _sigma << std::endl;	
	_z.observations.clear();
	return;
}

nav_msgs::Odometry EKF_Localization::estimated_odometry( void )const{
	nav_msgs::Odometry msg;
	msg.pose.pose.position.x = _mu( 0 );
	msg.pose.pose.position.y = _mu( 1 );
	msg.pose.pose.orientation = yaw_to_quaternion( _mu( 2 ) );
	return msg;
}
