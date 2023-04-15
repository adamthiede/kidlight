# kidlight

very simple python, cron, shell scripts to turn on different lights at a specific time

## awake.py and asleep.py

both are the same thing basically, but different defaults. Should technically be one script with an argument.

## isthelighton.sh

checks if the scripts are running. If not, runs them in the background according to the correct schedule. 

## cron

put this in your crontab.


side note - raspberry pis are bad at keeping time. Put sntp -S pool.ntp.org in root's cron for every few minutes or something. (or just `timedatectl set-ntp true`)

## clock.ino

I soldered appropriate headers on to the following components and stacked them top to bottom in this order. The program makes them into a clock. I copied a lot of example code to make this work.

- [Adafruit OLED Featherwing display](https://www.adafruit.com/product/4650)
- [Adafruit Feather M0 Express](https://www.adafruit.com/product/3403)
- [Adafruit RTC Featherwing board](https://www.adafruit.com/product/2922)

These are the libraries in my `~/Arduino/libraries/` folder. I added Adafruit's board URL. [Instructions here](https://learn.adafruit.com/add-boards-arduino-v164/setup)

- `Adafruit_BusIO`
- `Adafruit_DMA_neopixel_library`
- `Adafruit_GFX_Library`
- `Adafruit_NeoPixel`
- `Adafruit_SH110X`
- `RTClib`

What I've made is a clock that has a battery-backed RTC. It kinda has to be plugged into a computer to be reset, or you can use buttons A and C to change the time in either direction. Button B can rotate the display.

![photo of the listed microcontroller components with a clock on the display](microcontroller_clock.jpg)

I've added the 3d-printed case STL file and SCAD file (usable in OpenSCAD).

