#!/bin/bash

turnon(){

	echo "turn the light on"
	if [[ $(date +%H) -ge 19 || $(date +%H) -le 6 ]];then
		echo "it's nighttime between 19:00 and 7:00"
		python3 /home/pi/asleep.py&
	elif [[ $(date +%H) -ge 7 && $(date +%H) -le 19 ]];then
		echo "it's daytime between 7 and 19:00"
		python3 /home/pi/awake.py&
	fi

}

if [[ -z $(ps -ef|grep -v grep|grep -e awake.py -e asleep.py) ]];then
	echo "process not running"
	turnon
else
	echo "it's running! bye."
fi
