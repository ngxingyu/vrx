cmake_minimum_required(VERSION 2.8.3)
project(robotx_2022)

find_package(catkin REQUIRED COMPONENTS
	roslaunch
	vrx_gazebo
	wave_gazebo
	xacro
	geometry_msgs
	roscpp
)

catkin_package(
	CATKIN_DEPENDS
	xacro
	geometry_msgs
	roscpp
	rotors_gazebo_plugins
)

xacro_add_files(
	worlds/qualification_course.world.xacro
	worlds/semis_course.world.xacro
	worlds/finals_course.world.xacro
	INSTALL DESTINATION worlds
)

# Install all the world files
install(DIRECTORY worlds/
	DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/worlds
)

# Install all the launch files
install(DIRECTORY launch/
	DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
)
