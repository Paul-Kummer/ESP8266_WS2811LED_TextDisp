/*
    Author: Paul Kummer
    Date: 8/21/2022
    License: Open Source
    File: constants.h
*/

//Wifi connection
const char* ssid            = "NETGEAR92";
const char* password        = "breezyunicorn425";

//NTP Client
const int16_t utcOffsetSec   = -18000;
char* daysOfTheWeek[7]       = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//LED Values
#define LED_TYPE            WS2811
#define DATA_PIN            2
#define COLOR_ORDER         RGB
#define NUM_LEDS            100
#define BRIGHTNESS          250
#define VOLTAGE             5
#define MAX_POWER_MILLIAMPS 2000 //3000 is max for my PSU
#define LED_WIDTH		      	19
#define LED_HEIGHT		      5

//IR Values
const uint16_t kRecvPin   = 14;
const uint32_t kBaudRate  = 74880; //74880 115200