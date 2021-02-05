#!/usr/bin/env python3
import time
from signal import pause
import datetime
# https://github.com/xtacocorex/CHIP_IO
import CHIP_IO.GPIO as GPIO

print("0 and 1 setup")
GPIO.setup("CSID0", GPIO.OUT)
GPIO.setup("CSID1", GPIO.OUT)

print("0 on")
GPIO.output("CSID0",GPIO.HIGH)
time.sleep(5)
print("0 off")
GPIO.output("CSID0",GPIO.LOW)
time.sleep(5)
print("1 on")
GPIO.output("CSID1",GPIO.HIGH)
time.sleep(5)
print("1 off")
GPIO.output("CSID1",GPIO.LOW)
