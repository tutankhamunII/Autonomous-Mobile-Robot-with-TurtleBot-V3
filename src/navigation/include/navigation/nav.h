#include <vector>
#include <memory>
#include "nav_msgs/OccupancyGrid.h"
#include "geometry_msgs/Polygon.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
struct Node {
    float x, y;  // Coordinates
    float f;
    float h;
    float g;
    std::shared_ptr<Node> pb;
    bool is_open;
    std::vector<std::shared_ptr<Node>> neighbors;  // List of pointers to adjacent nodes
	
    Node();
    virtual ~Node();
};
//class control{

//	public:
//	control();
//	virtual ~control();
//	void pure_pursuit();
//	geometry_msgs::Twist _command;
//	geometry_msgs::Polygon _path;
//	nav_msgs::Odometry _estimated_odom;

//};
class navi {
	public:
	navi();
	virtual ~navi();
	geometry_msgs::Polygon solve();
	bool is_goal();
	void handle_map(const nav_msgs::OccupancyGrid::ConstPtr& msg);
	void handle_odom(const nav_msgs::Odometry::ConstPtr& msg);
	void handle_goal(const geometry_msgs::Point32::ConstPtr& msg);
	void handle_waypoints(const geometry_msgs::Polygon::ConstPtr& msg);
	bool check_map(const double& x, const double& y, const double& raduis, const double& threshold);
	int in_open_list(const std::shared_ptr<Node> node);
	bool in_closed_list(const std::shared_ptr<Node> node);
	void change_cost(const std::shared_ptr<Node> parent, const std::shared_ptr<Node> child, float cost);
	bool is_at_goal(const std::shared_ptr<Node> node);
	void expand_node(const std::shared_ptr<Node> node);
	void calculate_full_cost(const std::shared_ptr<Node> parent, const std::shared_ptr<Node> child, float cost);
	geometry_msgs::Point32 lookahead_point(int index);
	geometry_msgs::Polygon construct_path();
	void pure_pursuit();
	//protected:
	float raduis;
	std::vector<std::shared_ptr<Node>> open;
	std::vector<std::shared_ptr<Node>> closed;
	int max_iterations;
	float node_resolution;
	float map_resolution;
	geometry_msgs::Twist _command;
	geometry_msgs::Point32 _goal;
	nav_msgs::OccupancyGrid _ocmap;
	nav_msgs::Odometry _estimated_odom;
	std::vector<std::vector<Node>> nodes;
	geometry_msgs::Polygon _path;
	geometry_msgs::Point32 _lookahead;
	geometry_msgs::Polygon _waypoints;
	int curr_goal = 0;
	bool got_path;
	bool finished_path = true;
	bool loop_flag = true;
};
