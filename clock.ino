#include "RTClib.h"
#include <Adafruit_NeoPixel.h>
//OLED Display Setup
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

// OLED FeatherWing buttons map to different pins depending on board:
#define BUTTON_A  9
#define BUTTON_B  6
#define BUTTON_C  5

// Date and time functions using a PCF8523 RTC connected via I2C and Wire lib

#define NPPIN 8
Adafruit_NeoPixel pixels(1, NPPIN, NEO_GRB + NEO_KHZ800);

RTC_PCF8523 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {
  pixels.begin();
  Serial.begin(57600);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    pixels.setPixelColor(0, pixels.Color(150, 0, 0));
    pixels.setBrightness(50);
    pixels.show();
    Serial.flush();
    abort();
  }

/*
  if (! rtc.initialized() || rtc.lostPower()) {
    Serial.println("RTC is NOT initialized, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    // rtc.adjust(DateTime(2021, 09, 05, 17, 17, 0));
    // Note: allow 2 seconds after inserting battery or applying external power
    // without battery before calling adjust(). This gives the PCF8523's
  }
*/
  rtc.start();

  // The PCF8523 can be calibrated for:
  //        - Aging adjustment
  //        - Temperature compensation
  //        - Accuracy tuning
  // The offset mode to use, once every two hours or once every minute.
  // The offset Offset value from -64 to +63. See the Application Note for calculation of offset values.
  // https://www.nxp.com/docs/en/application-note/AN11247.pdf
  // The deviation in parts per million can be calculated over a period of observation. Both the drift (which can be negative)
  // and the observation period must be in seconds. For accuracy the variation should be observed over about 1 week.
  // Note: any previous calibration should cancelled prior to any new observation period.
  // Example - RTC gaining 43 seconds in 1 week
  float drift = 43; // seconds plus or minus over oservation period - set to 0 to cancel previous calibration.
  float period_sec = (7 * 86400);  // total obsevation period in seconds (86400 = seconds in 1 day:  7 days = (7 * 86400) seconds )
  float deviation_ppm = (drift / period_sec * 1000000); //  deviation in parts per million (μs)
  float drift_unit = 4.34; // use with offset mode PCF8523_TwoHours
  // float drift_unit = 4.069; //For corrections every min the drift_unit is 4.069 ppm (use with offset mode PCF8523_OneMinute)
  int offset = round(deviation_ppm / drift_unit);
  // rtc.calibrate(PCF8523_TwoHours, offset); // Un-comment to perform calibration once drift (seconds) and observation period (seconds) are correct
  // rtc.calibrate(PCF8523_TwoHours, 0); // Un-comment to cancel previous calibration

  Serial.print("Offset is "); Serial.println(offset); // Print to control offset

  // OLED Display Setup
  Serial.begin(115200);
  display.begin(0x3C, true); // Address 0x3C default
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);
  // Clear the buffer.
  display.clearDisplay();
  display.display();
  display.setRotation(3);
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
}

void textDisplayTest() {
  // text display tests
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.print("Connecting to SSID\n'adafruit':");
  display.print("connected!");
  display.println("IP: 10.0.1.23");
  display.println("Sending val #0");
  display.display(); // actually display all of the above
}

void printRtcTime(DateTime now) {
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  Serial.print(" since midnight 1/1/1970 = ");
  Serial.print(now.unixtime());
  Serial.print("s = ");
  Serial.print(now.unixtime() / 86400L);
  Serial.println("d");

  // calculate a date which is 7 days, 12 hours and 30 seconds into the future
  DateTime future (now + TimeSpan(7, 12, 30, 6));

  Serial.print(" now + 7d + 12h + 30m + 6s: ");
  Serial.print(future.year(), DEC);
  Serial.print('/');
  Serial.print(future.month(), DEC);
  Serial.print('/');
  Serial.print(future.day(), DEC);
  Serial.print(' ');
  Serial.print(future.hour(), DEC);
  Serial.print(':');
  Serial.print(future.minute(), DEC);
  Serial.print(':');
  Serial.print(future.second(), DEC);
  Serial.println();

  Serial.println();
}

void increaseTime() {
  DateTime tm=rtc.now();
  rtc.adjust(DateTime(tm.year(), tm.month(), tm.day(), tm.hour(), tm.minute()+1, 0));
}
void decreaseTime() {
  DateTime tm=rtc.now();
  rtc.adjust(DateTime(tm.year(), tm.month(), tm.day(), tm.hour(), tm.minute()-1, 0));
}
void rotateDisplay(){
  switch (display.getRotation()) {
    case 0:
      display.setRotation(3);
      break;
    case 1:
      display.setRotation(3);
      break;
    case 2:
      display.setRotation(1);
      break;
    case 3:
      display.setRotation(1);
      break;
  }
}

void loop () {
  DateTime now = rtc.now();
  //printRtcTime(now);
  int hr = now.hour();
  int mn = now.minute();
  String shr = String(hr);
  String smn = String(mn);
  if (mn < 10) {
    smn = "0" + smn;
  }
  if (hr < 10) {
    shr = " " + shr;
  }
  String tstr = shr + ":" + smn;
  display.setTextSize(4);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(5, 16);
  display.clearDisplay();
  display.println(tstr);
  display.display();
  Serial.print("current time is: ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.println();

/*
  if ( (hr==6 and mn>=30) or (hr>=12 and (hr<=14 and mn<=29))) {
    //Serial.println("Setting pixel to yellow, for early morning, or naptime");
    pixels.setPixelColor(0, pixels.Color(150, 150, 0));
    pixels.setBrightness(50);
    pixels.show();
  }
  else*/
  if ((hr==6 and mn>=30) or (hr==7) or (hr==14 and mn >=30)) {
    //Serial.println("Setting pixel to green, for day");
    pixels.setPixelColor(0, pixels.Color(0, 150, 0));
    pixels.setBrightness(10);
    pixels.show();
  }

  if(!digitalRead(BUTTON_A)) increaseTime();
  if(!digitalRead(BUTTON_B)) rotateDisplay();
  if(!digitalRead(BUTTON_C)) decreaseTime();
  delay(1000);
  yield();
  display.display();
}
