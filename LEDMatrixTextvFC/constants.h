/*
    Author: Paul Kummer
    Date: 9/24/2022
    License: Open Source
    File: constants.h
*/

//Wifi connection
const char* ssid            = "YourNetwork";
const char* password        = "YourPassword";

//NTP Client
const int16_t utcOffsetSec   = -18000;
String daysOfTheWeek[7]       = {"SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY"};

//LED Values
#define LED_TYPE            WS2812 // //WS2811
#define DATA_PIN            D2
#define COLOR_ORDER         GRB //RGB //
#define NUM_LEDS            140 //100 //
#define BRIGHTNESS          25 //200 //
#define VOLTAGE             5
#define MAX_POWER_MILLIAMPS 200 //1000 //2000 //3000 is max for my PSU
#define LED_WIDTH		    28 //19 //
#define LED_HEIGHT		    5

//IR Values
const uint16_t kRecvPin   = 14;
const uint32_t kBaudRate  = 74880; //74880 115200

//Open Times sun-sat
const uint16_t openTimes[7] = {600, 600, 600, 600, 600, 600, 600};

//Close Times sun-sat
const uint16_t closeTimes[7] = {1080, 1320, 1320, 1320, 1320, 1320, 1200};
