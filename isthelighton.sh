#!/bin/bash

turnon(){
	curdate=$(date +%H%M|sed 's/^0*//')
	echo "turn the light on"
	if [[ $curdate -ge 1830 || $curdate -le 650 ]];then
		echo "it's nighttime between 18:30 and 6:50"
		python3 /home/pi/asleep.py&
	elif [[ $curdate -ge 651 && $curdate -le 1829 ]];then
		echo "it's daytime between 7 and 19:00"
		python3 /home/pi/awake.py&
	fi

}

if [[ -z $(ps -ef|grep -v grep|grep -e awake.py -e asleep.py) ]];then
	echo "process not running"
	turnon
else
	echo "$(ps -ef|grep -v grep|grep -e awake.py -e asleep.py)"
	echo "it's running! bye."
fi
