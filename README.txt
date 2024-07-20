There are two launch files in the launch directory. One for simulation called "simulation.launch" that startsnodes like goal_publisher, landmark_publisher, obstacle_publisher, GUI, simulator. It also starts the rest ofthe archtecture.
The other is named "robot.launch" and it only launches the required nodes by robot, including perception.

It is unfortunate that my robot is not moving very effectively due to corrupted pure pursuit implementation. I have trying to debug it with no luck. The percetpion, simulator, and GUI nodes are working fine (GUI have some problems that never arised before like lasers going throught obstacles and landmarks seems to be printed multiple times as the robot moves. The landmark draw functions are commented to assist visualization since they fill the GUI, but you may uncomment them to see the general behavior). 

The SLAM package is working as expected (math tested with actual SLAM problems and with the landmark_publisher)

The planning package works as expected (tested by publishing goals and monitor the drawn path on the GUI).Since my pure pursuit is not working I am currently navigating to one goal through the goal publisher but I still capture the waypoints message in the navigation module and have commented logic to go through the goals (i think because the pure pursuit is corrupted this logic fails and terminates navigation so i commented it).

To launch the project, simply navigate to the launch directory and run "roslaunch file.launch", replacing file with either "simulator" or "robot"

