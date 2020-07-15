# kidlight

very simple python, cron, shell scripts to turn on different lights at a specific time

## awake.py and asleep.py

both are the same thing basically, but different defaults. Should technically be one script with an argument.

## isthelighton.sh

checks if the scripts are running. If not, runs them in the background according to the correct schedule. 

## cron

put this in your crontab.


side note - raspberry pis are bad at keeping time. Put sntp -S pool.ntp.org in root's cron for every few minutes or something.
