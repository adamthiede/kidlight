#!/usr/bin/env python3
from gpiozero import LED, Button
from time import sleep
from signal import pause
import datetime

#define time sequence
hours=12
minutes=(hours*60)
time=(minutes*60)
#define gpio
green=LED(17)
red=LED(27)
button=Button(26)
#default
red.on()
green.off()

asleep=True

def wakeup():
    red.off()
    green.on()
    print("time to wake up. resetting time.")
    global asleep
    asleep=False
    time=(18*60*60) #18 hours

def sleepy():
    red.on()
    green.off()
    print("time for bed now.")
    global asleep
    asleep=True
    time=(12*60*60) #12 hours

def toggle():
    global asleep
    if asleep==True:
        wakeup()
    else:
        sleepy()
    sleep(1)

while True:
    print(f"{asleep} status")
    button.when_released=toggle()
    button.wait_for_press()
    button.wait_for_release()

