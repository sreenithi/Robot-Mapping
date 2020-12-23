# Robot Mapping
A simple robot modelled using URDF and programmed using ROS that can map the environment around it using the RTAB-Map Mapping algorithm

The ROS project consists of 2 packages, **my_robot** and **mapping**. The *my_robot* package contains the robot and world models which can be visualised in the Gazebo simulator when the package is run using the *roslaunch* command. The *mapping* package is responsible for running the rtabmap node to perform the mapping of the environment

The generated map of the environment can be downloaded from this [Google Drive link](https://drive.google.com/file/d/1iizsyYIMYCqfuBdb5KPcZWPgI7CdbKGo/view?usp=sharing). Any new map generated when running the rtabmap node for mapping is saved to the mapping/db folder (You will have to create the db folder in the mapping package when running for the first time).

To view the existing map dowloaded from the link, run the command<br>
`rtabmap-databaseViewer (map db location)/rtabmap.db`

## Nodes
* rtabmap (Mapping)
* rtabmap (Localisation)

  
## ROS and Ubuntu version used
ROS Kinetic in Ubuntu 16.04
