#include "navigation/nav.h"
#include <cmath>
#include <algorithm>
//i have to check paths for obstacles before adding them.
//so i check the node for legality and also the path to it
//for obstacles.
//
std::ostream& operator<<(std::ostream& os, const Node p) {
    os << "(X: " << p.x << ", Y: " << p.y << ", f: " << p.f << ", g: " << p.g <<", h: " << p.h << ", BP: " << p.pb << ")";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        os << *(vec[i]) << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const geometry_msgs::Polygon &path){

	for(size_t i = 0; i < path.points.size(); i++)
	{
		os << "x: " << path.points[i].x << "\n" << "y: " << path.points[i].y << "\n" << "z: " << path.points[i].z;
	}
	return os;
}
geometry_msgs::Quaternion yaw_to_quaternion( const double& yaw ){
        geometry_msgs::Quaternion quaternion;
        quaternion.w = cos( yaw / 2.0 );
        quaternion.x = 0.0;
        quaternion.y = 0.0;
        quaternion.z = sin( yaw / 2.0 );
        return quaternion;
}

double quiaternion_to_yaw(const geometry_msgs::Quaternion msg){
	
	return std::atan2(2 * (msg.w * msg.z + msg.x * msg.y), 1 - 2 * (msg.y * msg.y + msg.z * msg.z));

}

int x_to_row( const nav_msgs::OccupancyGrid& map, const double& x, const double& discretization ){
        return round( x / discretization + ( double )( ( map.info.width - 1 ) / 2 ));
}

int y_to_col( const nav_msgs::OccupancyGrid& map, const double& y, const double&discretization ){
        return round( y / discretization + ( double )( ( map.info.height - 1 ) / 2 ));
}
double row_to_x( const nav_msgs::OccupancyGrid& map, const int& row, const double& discretization ){
        return ( discretization * ( double )( -( ( int )( map.info.width ) - 1 ) /2.0 + row ) );
}

double col_to_y( const nav_msgs::OccupancyGrid& map, const int& col, const double& discretization ){
        return ( discretization * ( double )( -( ( int )( map.info.height ) - 1 ) /2.0 + col ) );
}

bool row_col_in_map( const nav_msgs::OccupancyGrid& map, const int& row, const int& col ){
        if( ( row < 0 ) || ( col < 0 ) ){
                return false;
        }
        else if ( ( row >= map.info.width ) || ( col >= map.info.height ) ){
                return false;
        }
        else {
                return true;
        }
}

Node::Node(){}
Node::~Node(){}

navi::navi(){
	map_resolution = 0.10;
	node_resolution = 0.30;
	max_iterations = 10000; //thousands
	raduis = 0.20;
	
	///for testing only///
	//_goal.x = 4;
	//_goal.y = 5;
	//_goal.z = 0.10;
}

navi::~navi(){}

void navi::handle_map(const nav_msgs::OccupancyGrid::ConstPtr& msg){
	_ocmap = *msg;
	return;
}

void navi::handle_waypoints(const geometry_msgs::Polygon::ConstPtr& msg){
	_waypoints = *msg;
	return;
}
void navi::handle_odom(const nav_msgs::Odometry::ConstPtr& msg){
	_estimated_odom = *msg;
	return;
}

void navi::handle_goal(const geometry_msgs::Point32::ConstPtr& msg){
	//std::cout << "got goal" << msg -> x << ", " << msg -> y << ", " << msg -> z << std::endl;
	_goal = *msg;
	return;
}

int navi::in_open_list(const std::shared_ptr<Node> node){
	
	for(int i = 0; i < open.size(); i++){
		if(node->x == open[i] -> x && node->y == open[i] -> y){
			return i;
		}
	}
	return 0;
}

bool navi::in_closed_list(const std::shared_ptr<Node> node){
	
	for(int i = 0; i < closed.size(); i++){
                if(node->x == closed[i] -> x && node->y == closed[i] -> y){
                        return true;
                }
        }
        return false;
}

//bool navi::check_map(const double& x, const double& y, const double& raduis, const double& threshold){

  //  int row = x_to_row(_ocmap, x, 0.10);
    //int col = y_to_col(_ocmap, y, 0.10);
    //int offset = ceil(nodeSize / (2 * 0.10))
    //int offset = ceil(raduis / 0.10);
    //for (int i = -offset; i <= offset; i++) {
      //  for (int j = -offset; j <= offset; j++) {
          //  if (row_col_in_map(_ocmap, row + i, col + j)) {
        //        int index = (row + i) * _ocmap.info.height + col + j;
		//the comparison was flipped.
		//missing it
            //    if (_ocmap.data[index] > threshold) {
                //    return false;
              //  }
            //}
       // }
    //}
    //double occupancyRate = (double)occupiedCells / (double)totalCells;
    //return occupancyRate < 0.5;
    //if any grid is occupied = node is illegal.
	
//}
bool navi::check_map( const double& x,const double& y,const double& radius,const double& threshold ){
        int row = x_to_row( _ocmap, x, _ocmap.info.resolution);
        int col = y_to_col( _ocmap, y, _ocmap.info.resolution);
        int offset = ceil( radius / _ocmap.info.resolution);
        for( int i = -offset; i < offset; i++ ){
                double dx = row_to_x(_ocmap, row + i, _ocmap.info.resolution ) - x;
                for( int j = -offset; j < offset; j++ ){
                        double dy = col_to_y( _ocmap, col + j, _ocmap.info.resolution ) - y;
                        if( row_col_in_map(_ocmap, row + i, col + j ) && ( sqrt( dx * dx + dy * dy ) < radius ) ){
                                int index = ( row + i ) * _ocmap.info.height + col + j;
                                if( _ocmap.data[ index ] > threshold ){
                                        return false;
                                }
                        }
                }
        }
return true;
}

void navi::expand_node(const std::shared_ptr<Node> node){
	
	float cost = 0;
	for(int i = -1; i <= 1; i++){
		for(int j = -1; j <= 1; j++){
			if(i == 0 && j == 0){
				continue;
			}
			else if (abs(i) == 1 && abs(j) == 1) {
				cost = sqrt(2*pow(node_resolution,2));	
			}
			else{
				cost = node_resolution;
			}
			
			std::shared_ptr<Node> child = std::make_shared<Node>();
			child -> x = node -> x + i;// * node_resolution;
			child -> y = node -> y + j;// * node_resolution;
			int idx = in_open_list(child);
			if(in_closed_list(child)){
				continue;
			}	
			else if(idx){
				change_cost(node, open[idx], cost);
			}
			else{
				//obstacle avoidance!
				if(check_map(child -> x * node_resolution, child -> y * node_resolution, raduis, 0)){
				node -> neighbors.push_back(child);
				calculate_full_cost(node, child, cost);
				open.push_back(child);
				}
			}
		}
	}
	return;
}

void navi::calculate_full_cost(const std::shared_ptr<Node> parent, const std::shared_ptr<Node> child, float cost){
	
	if(parent == child){
                child -> g = 0;
		child -> h = sqrt(pow(_goal.x - child -> x, 2) + pow(_goal.y - child -> y, 2));
		child -> f = child -> h + child -> g;
		child -> pb = NULL;
                return;
        }
	child -> g = parent -> g + cost;
	child -> h = sqrt(pow(_goal.x - child -> x, 2) + pow(_goal.y - child -> y, 2));
	child -> f = child -> h + child -> g;
	child -> pb = parent;
	return;
}

bool navi::is_at_goal(const std::shared_ptr<Node> node){
	
	//std::cout << "node to be checkd: " << node->x << ", " << node->y << std::endl;
	float distance = sqrt(pow(_goal.x - node -> x, 2) + pow(_goal.y - node -> y, 2));
	if(distance < _goal.z){
		//std::cout << "reached" << std::endl;
		return true;
	}
	return false;	

}

void navi::change_cost(const std::shared_ptr<Node> parent, const std::shared_ptr<Node> child, float cost){
	
	float new_cost = child -> h + parent -> g + cost;
	if(new_cost < child -> f){
		child -> f = new_cost;
		child -> g = parent -> g + cost;
		child -> pb = parent;
	}
	return;	
}
geometry_msgs::Polygon navi::construct_path(){
	
	geometry_msgs::Polygon path;
	geometry_msgs::Point32 point1;
	geometry_msgs::Point32 point2;
	for(int i = 0; i < closed.size(); i++){
		point1.x = closed[i] -> x;
		point1.y = closed[i] -> y;
		path.points.push_back(point1);
	}

	geometry_msgs::Polygon path_interpolated;
	path_interpolated.points.push_back(path.points[0]);
	for(int i = 0; i < path.points.size() - 1; i++){
		point1 = path.points[i];
		point2 = path.points[i+1];
		float distance = sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
		int segments = distance / 0.10;
		for(int j = 1; j < segments; j++){
			geometry_msgs::Point32 new_point;
			double temp = j / static_cast<double>(segments);
			new_point.x = point1.x + temp * (point2.x - point1.x);
			new_point.y = point1.y + temp * (point2.y - point1.y);
			path_interpolated.points.push_back(new_point);
		}
		path_interpolated.points.push_back(point2);
	}
	return path_interpolated;
}

geometry_msgs::Polygon navi::solve(){

	got_path = false;
	std::shared_ptr<Node> start_node = std::make_shared<Node>();
	start_node -> x = std::round(_estimated_odom.pose.pose.position.x / node_resolution);
	start_node -> y = std::round(_estimated_odom.pose.pose.position.y / node_resolution);	
	calculate_full_cost(start_node, start_node, 0);
	open.push_back(start_node);
	std::shared_ptr<Node> top = open.back();
	int iterations = 0;
	while((is_at_goal(top) == false) && iterations < max_iterations){
		std::sort(open.begin(), open.end(), [](const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) {return a->f > b->f;});
		top = open.back();
		open.pop_back();
		closed.push_back(top);
		//std::cout << "itr(" << iterations << ")>> " << "Open List: \n" << open << std::endl;
                //std::cout << "itr(" << iterations << ")>> " << "Closed List: \n" << closed << std::endl;
		expand_node(top);
		iterations ++;
	}
	if(iterations != max_iterations){
	//std::cout << "found goal!" << std::endl;
	got_path = true;
	}
	else if(iterations = max_iterations){
	//std::cout << "failed to find goal after max iterations" << std::endl;
	}
	geometry_msgs::Polygon path = construct_path();
	open.clear();
	closed.clear();
	_path = path;
	//std::cout <<"path: " << std::endl << path << std::endl;
	return path;
}

geometry_msgs::Point32 navi::lookahead_point(int index){
	
	geometry_msgs::Point32 temp;
	temp.x = _path.points[index].x;
	temp.y = _path.points[index].y;
	temp.z = _path.points[index].z;
	return temp;
}

void navi::pure_pursuit(){

	//if(loop_flag){
	//	_goal.x = _waypoints.points[curr_goal].x;
	//	_goal.y = _waypoints.points[curr_goal].y;
	//	_goal.z = _waypoints.points[curr_goal].z;
	//	loop_flag = false;
	//}
	float lookahead_gain = 1.0;
	float LD_distance = 0.3;
	float wheel_center = 0.23; //grabbed from ROS discourse for turtlebot2.
	double y_t = 0;
	double ld_2 = 0;
	double stearing_angle = 0;
	int curr_point = 0;
	int final_point = 0;
	float transformed_point_x = 0;
	float transformed_point_y = 0;
	float relative_x = 0;
	float relative_y = 0;
	float robot_x = 0;
	float robot_y = 0;
	float robot_bearing = 0;
	if(got_path){
		//std::cout <<"here" << std::endl;
		for(int i = 0; i < _path.points.size(); i++){
			
			robot_x = _estimated_odom.pose.pose.position.x;
			robot_y = _estimated_odom.pose.pose.position.y;
			robot_bearing = quiaternion_to_yaw(_estimated_odom.pose.pose.orientation);
			double distance = sqrt(pow(_path.points[i].x - robot_x , 2) + pow(_path.points[i].y - robot_y, 2));
			if(distance >= LD_distance){
				
				curr_point = i;
				relative_x = _path.points[i].x - robot_x;
				relative_y = _path.points[i].y - robot_y;
				transformed_point_x = relative_x * cos(robot_bearing) + relative_y * sin(robot_bearing);
				transformed_point_y = -relative_x * sin(robot_bearing) + relative_y * cos(robot_bearing);
				break;
			}
		}
	}
	_lookahead = lookahead_point(curr_point);
        ld_2 = LD_distance * LD_distance;
	stearing_angle = atan2(2 * wheel_center * transformed_point_y, ld_2);
	
	double curve = (2*sin(stearing_angle))/LD_distance; //pretty sure problem is here

	_command.linear.x = 0.4;
	_command.angular.z = curve * 0.4;
	final_point = curr_point;
	if(curr_point == _path.points.size()){
		curr_goal++;
		loop_flag = true;
	}
	return; 
}

