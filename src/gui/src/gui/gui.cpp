#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "gui/gui.h"
#include <math.h>
#include "perception/Observations.h"
using namespace std;
double quaternion_to_yaw( const geometry_msgs::Quaternion& quaternion ){
	
	double yaw = atan2(2 * (quaternion.w * quaternion.z + quaternion.x * quaternion.y), 1 - 2 * (quaternion.y * quaternion.y + quaternion.z * quaternion.z));
	return yaw; 
}

GUI:: GUI( QWidget * parent ) : QGLWidget( parent ), _timer(), _zoom( 5.0 ), _center( 0.0, 0.0 ), _laserscan(), _odom(), observations() {
	
	setMinimumSize( 600, 600 );
	setFocusPolicy(Qt::StrongFocus);
	connect( &_timer, SIGNAL( timeout() ), this, SLOT( timer_callback() ) );
	_timer.start( 10 );
}

GUI::~GUI() {}

void GUI::handlePath(const geometry_msgs::Polygon::ConstPtr& msg){
	
	_path = *msg;
	updateGL();
	return;
}

void GUI::handleLaserScan( const sensor_msgs::LaserScan::ConstPtr& msg ){

	_laserscan = *msg;
	updateGL();
	return;
}

void GUI::handleOdom( const nav_msgs::Odometry::ConstPtr& msg ){

	_odom = *msg;
	updateGL();
	return;
}

void GUI::handleEstimatedOdom(const nav_msgs::Odometry::ConstPtr& msg){
	
	_estimated_odom = *msg;
	updateGL();
	return;
}

void GUI::handleObservations( const perception::Observations::ConstPtr& msg){
	
	observations = *msg;
	updateGL();
	return;
}

void GUI::handleGoal(const geometry_msgs::Point32::ConstPtr& msg){

	_goal = *msg;
	updateGL();
	return;
}

void GUI::handleLandmarks(const perception::Landmarks::ConstPtr& msg){

	_landmarks = *msg;
	updateGL();
	return;
}

void GUI::handleObservedLandmarks(const perception::Landmarks::ConstPtr &msg){

	_observed_landmarks = *msg;
	updateGL();
	return;
}

void GUI::handleMap( const nav_msgs::OccupancyGrid::ConstPtr& msg ){

	_map = *msg;
	return;
}

void GUI::handleSimulatedObstacles( const geometry_msgs::Polygon::ConstPtr& msg ){
	
	_simulated_obstacles = *msg;
	return;
}
void GUI::timer_callback( void ){

	ros::spinOnce();
	return;
}

void GUI::initializeGL(){

	glClearColor( 1.0, 1.0, 1.0, 1.0 );
	glEnable( GL_LINE_SMOOTH );
	glEnable( GL_BLEND );
	return;
}

void GUI::resizeGL( int width,int height ){

	glViewport( 0, 0, width, height );
	return;
}

void GUI::paintGL(){

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double ratio = ( double )( size().width() ) / ( double )( size().height() );
	gluOrtho2D( -_zoom * ratio + _center.first, _zoom * ratio + _center.first, -
	_zoom + _center.second, _zoom + _center.second );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawGrid();
	drawCoordinateSystem();
	drawMap( _map, 1.0, 1.0, 1.0 );
	drawLaserScan(_odom.pose.pose,  _laserscan, 0.0, 0.0, 1.0 );
	drawPose( _odom.pose.pose, 0.0, 0.0, 0.0, 0.1225 );
	drawPose( _estimated_odom.pose.pose, 0.2, 0.2, 0.2, 0.1225 );
	//drawRobotSensorHorizon( _estimated_odom.pose.pose, 0.2, 0.2, 0.2, -M_PI/4.0, M_PI/4.0, 5.0 );
	drawGoal( _goal, 0.0, 1.0, 0.0);
	drawLandmarks( _landmarks, 1.0, 0.0, 0.0, 15.0 );
	//drawLandmarks( _observed_landmarks, 0.5, 0.5, 0.0, 15.0 );
	drawObstacles( _simulated_obstacles, 0.0, 0.0, 1.0 );
	drawPath(_path, 0.0, 1.0, 0.0);
	//drawObservations(0.0, 0.0, 1.0, 10);
	return;
}

void GUI::drawGoal(const geometry_msgs::Point32& goal, const double& r, const double& g, const double& b ){

	glColor4f( r, b, g, 1);
        glPointSize(20);
        glBegin( GL_POINTS );
        glVertex3f( goal.x, goal.y, 0.0);
        glEnd();
        glPointSize( 1.0 );
	return;
}

void GUI::drawPath(const geometry_msgs::Polygon& path, const double& r, const double& g, const double& b){

	if(path.points.size() >= 2){
	glColor4f( r, b, g, 1);
        glPointSize(2);
        glBegin( GL_LINE_STRIP );
	for(int i = 0; i < path.points.size(); i++){
		glVertex3f( path.points[i].x, path.points[i].y, 0.0);

	}
        glEnd();
        glPointSize( 1.0 );
	}
        return;
		
}

void GUI::drawObstacles(const geometry_msgs::Polygon& obstacles, const double& r, const double& g, const double& b){

	glColor4f( r, b, g, 1.0 );
	glBegin( GL_LINE_LOOP );
	for (int i = 0; i < obstacles.points.size(); i++){
		glBegin(GL_LINE_LOOP);
		for (int j = 0; j < 50; ++j) {
       			float theta = 2.0f * 3.1415926f * float(j) / float(50);
        		float x = obstacles.points[i].z * cosf(theta); 
        		float y = obstacles.points[i].z * sinf(theta);
        		glVertex2f(x + obstacles.points[i].x, y + obstacles.points[i].y);
		}
		glEnd();
	}
	glEnd();	
	return;
}

void GUI::drawLandmarks(const perception::Landmarks& polygon, const double& red, const double& green, const double& blue, const double& size){

	glColor4f( red, blue, green, 1);
	glPointSize(size);
	glBegin( GL_POINTS );
	for (int i = 0; i < polygon.landmarks.size(); i++){
		glVertex3f( polygon.landmarks[i].x, polygon.landmarks[i].y, 0.0);
	}
	glEnd();
	glPointSize( 1.0 );
	return;
}

void GUI::drawCoordinateSystem( void ){

	glBegin( GL_LINES );
	glColor4f( 1.0, 0.0, 0.0, 1.0 );
	glVertex3f( 0.0, 0.0, 0.0 );
	glVertex3f( 1.0, 0.0, 0.0 );
	glColor4f( 0.0, 1.0, 0.0, 1.0 );
	glVertex3f( 0.0, 0.0, 0.0 );
	glVertex3f( 0.0, 1.0, 0.0 );
	glColor4f( 0.0, 0.0, 1.0, 1.0 );
	glVertex3f( 0.0, 0.0, 0.0 );
	glVertex3f( 0.0, 0.0, 1.0 );
	glEnd();
	return;
}

void GUI::drawGrid( void ){

	glColor4f( 0.8, 0.8, 0.8, 1.0 );
	glLineWidth( 2.0 );
	glBegin( GL_LINES );
	for( int i = -10; i <= 10; i++ ){
		glVertex3f( -10.0, ( double )( i ), 0.0 );
		glVertex3f( 10.0, ( double )( i ), 0.0 );
		glVertex3f( ( double )( i ), -10.0, 0.0 );
		glVertex3f( ( double )( i ), 10.0, 0.0 );
	}
	glEnd();
	glLineWidth( 1.0 );
}

void GUI::drawLaserScan(const geometry_msgs::Pose& pose, const sensor_msgs::LaserScan& laserscan, const double& red, const double& green, const double& blue){

	glPushMatrix();
	glTranslated( pose.position.x, pose.position.y, 0.0 );
	glRotated( quaternion_to_yaw( pose.orientation ) * 180.0 / M_PI, 0.0, 0.0,1.0 );
	glColor4f( 1.0, 0.0, 0.0, 1.0 );
	glLineWidth( 2.0 );
	glBegin( GL_LINES );
	for( unsigned int i = 0; i < laserscan.ranges.size(); i++ ){
		double angle = laserscan.angle_min + ( double )( i ) * laserscan.angle_increment;
		glVertex3f( 0.0, 0.0, 0.0 );
		glVertex3f( laserscan.ranges[ i ] * cos( angle ), laserscan.ranges[ i ] * sin( angle ), 0.0 );
	}
	glEnd();
	glLineWidth( 1.0 );
	glPopMatrix();
	return;
}

void GUI::drawObservations(const double& red, const double& green,const double& blue, const double& size){
	
	double yaw = quaternion_to_yaw( _odom.pose.pose.orientation );
	glColor4f( red, blue, green, size );
	glPointSize( 5.0 );
	glBegin( GL_POINTS );
	for (int i = 0; i < observations.observations.size(); i++){
		double range = observations.observations[i].range;
		double bearing = observations.observations[i].bearing;
		double x_observation = _odom.pose.pose.position.x + range * cos(bearing + yaw);
		double y_observation = _odom.pose.pose.position.y + range * sin(bearing + yaw);
		glVertex3f( x_observation, y_observation, 0.0);
	}
	glEnd();
	glPointSize( 1.0 );
	return;
}

void GUI::drawPose( const geometry_msgs::Pose& pose, const double& red, const double& green, const double& blue, const double& radius){
	
	glPushMatrix();
	glTranslated( pose.position.x, pose.position.y, 0.0 );
	glRotated( quaternion_to_yaw( pose.orientation ) * 180.0 / M_PI, 0.0, 0.0, 1.0 );
	unsigned int discretization = 33;
	glColor4f( red, blue, green, 1.0 );
	glLineWidth( 5.0 );
	glBegin( GL_LINE_STRIP );
	for( unsigned int i = 0; i < discretization; i++ ){
		double angle = 2.0 * M_PI * ( double )( i ) / ( double )( discretization -1 );
		glVertex3f( radius * cos( angle ), radius * sin( angle ), 0.0 );
	}
	glEnd();
	glBegin( GL_LINES );
	glVertex3f( radius, 0.0, 0.0 );
	glVertex3f( -radius, 0.0, 0.0 );
	glEnd();
	glBegin( GL_TRIANGLES );
	glVertex3f( radius, 0.0, 0.0 );
	glVertex3f( radius/4.0, radius/2.0, 0.0 );
	glVertex3f( radius/4.0, -radius/2.0, 0.0 );
	glEnd();
	glLineWidth( 1.0 );
	glPopMatrix();
	return;
}

void GUI::drawMap( const nav_msgs::OccupancyGrid& map, const double& r, const double& g, const double& b ){

	double half_discretization = map.info.resolution / 2.0;
	double min_x = -( double )( map.info.width - 1 ) * half_discretization;
	double min_y = -( double )( map.info.height - 1 ) * half_discretization;
	glPushMatrix();
	glBegin( GL_QUADS );
	for( unsigned int i = 0; i < map.info.width; i++ ){
		double x = min_x + ( double )( i ) * map.info.resolution;
		for( unsigned int j = 0; j < map.info.height; j++ ){
			double y = min_y + ( double )( j ) * map.info.resolution;
			double occ = 1.0 - ( 1.0 / ( 1.0 + exp( ( double )( map.data[ i * map.info.height + j ] ) * 0.05 ) ) );
			glColor4f( ( 1.0 - occ ) * r, ( 1.0 - occ ) * g, ( 1.0 - occ ) * b, 1.0);
			glVertex3f( x - half_discretization, y - half_discretization, 0.0 );
			glVertex3f( x + half_discretization, y - half_discretization, 0.0 );
			glVertex3f( x + half_discretization, y + half_discretization, 0.0 );
			glVertex3f( x - half_discretization,y + half_discretization, 0.0 );
		}
	}
	glEnd();
	glPopMatrix();
	return;
}

void GUI::keyPressEvent(QKeyEvent * event){
	if( event->matches( QKeySequence::Copy ) ){
		close();
		return;
	}
       	else {
		switch (event->key()) {
		case Qt::Key_Left:
			_center.first -= 0.5;
			break;
		case Qt::Key_Right:
			_center.first += 0.5;
			break;
		case Qt::Key_Down:
			_center.second -= 0.5;
			break;
		case Qt::Key_Up:
			_center.second += 0.5;
			break;
		case Qt::Key_I:
			if( _zoom > 0.5 ){
				_zoom -= 0.5;
			}
			break;
		case Qt::Key_O:
			_zoom += 0.5;
			break;
		default:
			cout << "could not handle key " << event->key() << endl;
			break;
		}
		updateGL();
	}
	return;
}


