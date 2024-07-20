#ifndef GUI_H
#define GUI_H
#include <iostream>
#include <map>
#include "ros/ros.h"
#include <QtCore/QTimer>
#include <QtGui/QKeyEvent>
#include <QtWidgets/QWidget>
#include <QtOpenGL/QGLWidget>
#include "nav_msgs/Odometry.h"
#include "nav_msgs/Path.h"
#include "nav_msgs/OccupancyGrid.h"
#include "sensor_msgs/LaserScan.h"
#include "perception/Observations.h"
#include "perception/Landmarks.h"
#include "geometry_msgs/Polygon.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Point.h"
#include "map_msgs/OccupancyGridUpdate.h"
class GUI: public QGLWidget {
Q_OBJECT
public:
GUI( QWidget * parent = NULL );
virtual ~GUI();
void handleLaserScan( const sensor_msgs::LaserScan::ConstPtr& msg );
void handleOdom( const nav_msgs::Odometry::ConstPtr& msg );
void handleEstimatedOdom( const nav_msgs::Odometry::ConstPtr& msg );
void handleObservations( const perception::Observations::ConstPtr& msg);
void handleGoal( const geometry_msgs::Point32::ConstPtr& msg );
void handleLandmarks( const perception::Landmarks::ConstPtr& msg );
void handleObservedLandmarks( const perception::Landmarks::ConstPtr& msg );
void handleMap( const nav_msgs::OccupancyGrid::ConstPtr& msg );
void handleSimulatedObstacles( const geometry_msgs::Polygon::ConstPtr& msg );
void handlePath(const geometry_msgs::Polygon::ConstPtr& msg);
protected slots:
void timer_callback( void );
protected:
virtual void initializeGL();
virtual void resizeGL( int width, int height );
virtual void paintGL();
void drawCoordinateSystem( void );
void drawGrid();
void drawPose( const geometry_msgs::Pose& pose, const double& red = 0.0,
const double& green = 0.0, const double& blue = 0.0, const double&
radius = 0.1225 );
void drawPoint( const geometry_msgs::Point& point, const double& red =
0.0, const double& green = 0.0, const double& blue = 0.0, const double
& size = 1.0 );
void drawLaserScan( const geometry_msgs::Pose& pose, const sensor_msgs::
LaserScan& laserscan, const double& red, const double& green, const
double& blue );
void drawObservations(const double& red = 0.0, const double& green = 0.0,const double& blue = 0.0, const double& size = 1.0 );
void drawRobotSensorHorizon( const geometry_msgs::Pose& pose, const double
& red = 0.0, const double& green = 0.0, const double& blue = 0.0,
const double& minAngle = -M_PI/4.0, const double& maxAngle = M_PI/4.0,
const double& maxRange = 5.0 );
void drawLandmarks( const perception::Landmarks& polygon, const double& red = 0.0, const double& green = 0.0, const double& blue = 0.0, const double& size = 1.0 );
void drawMap( const nav_msgs::OccupancyGrid& map, const double& r,const double& g, const double& b );
void drawObstacles( const geometry_msgs::Polygon& obstacles, const double& r, const double& g, const double& b );
void drawPath(const geometry_msgs::Polygon& path, const double& r, const double& g, const double& b );
void drawGoal(const geometry_msgs::Point32& goal,const double& r, const double& g, const double& b );
virtual void keyPressEvent(QKeyEvent * event);
QTimer _timer;
double _zoom;
std::pair< double, double > _center;

sensor_msgs::LaserScan _laserscan;
nav_msgs::Odometry _odom;
perception::Observations observations;
nav_msgs::Odometry _estimated_odom;
nav_msgs::OccupancyGrid _map;
geometry_msgs::Point32 _goal;
nav_msgs::Path _projection;
perception::Landmarks _landmarks;
perception::Landmarks _observed_landmarks;
std::map< int, geometry_msgs::Point > _observed_landmarks_map;
geometry_msgs::Polygon _simulated_obstacles;
geometry_msgs::Polygon _path;
};
#endif /* GUI_H */


