#!/bin/sh
xterm -e " roslaunch my_robot world.launch" &
sleep 10
xterm -e " roslaunch mapping mapping.launch" &
sleep 15
xterm -e " rosrun teleop_twist_keyboard teleop_twist_keyboard.py" &

