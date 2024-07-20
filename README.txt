- This is a comprehensive autonomous mobile robot stack that implements grid mapping, EKF SLAM Localization, A* search motion planning, and Pure Pursuit with PID controller for path following.

- The stack is implemented using ROS Noetic and is deployed for testing on a TurtleBot V3 Differential drive robot. 

- The project also implements a GUI that shows the location of obstacles, robot, landmarks, and the current path to the waypoint. The GUI updates with a high frequency.

- Two launch files are uses to start the robot, simulator.launch will start all modules with the addition to a simulator module that simulates robotic movement based on hard-coded waypoints
using noise-corrected motion model and hard-coded landmark positions. The robot.launch file starts all modules including the landmarks computer vision recognition module that registers landmarks
data using Intel TrueDepth camera. It also also starts the lower-level executive node that sends motion commands to the Turtlebot to move. 

- Using desktop version of ROS Noetic on a ubuntu machine, this project is a plug and play module. build the catkin workspace with catkin_make and then launch either launch files with 
ros launch "file_name.launch"
