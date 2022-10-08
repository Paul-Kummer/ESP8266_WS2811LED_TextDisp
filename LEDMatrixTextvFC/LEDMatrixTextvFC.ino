/*
    Author: Paul Kummer
    Date: 9/24/2022
    License: Open Source
    File: LEDMatrixTextv2.ino

                [ INDIVIDUALLY ADDRESSABLE PIXEL STRING LAYOUT AS MATRIX ]

    (Symbol : Description)
    # _ : Border Frame
      * : Individually Addressable LED Pixel
    - | : 3-wire LED connecting wires

        COLUMNS| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10 |11 |12 |13 |14 |15 |16 |17 |18 |19
            _______________________________________________________________________________________
            #                                                         (NUMOFCOLUMNS, NUMOFROWS)   #       
  pixel 80  #    *---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*    # pixel 99  | 4
            #    |                                                                                #           |----
  pixel 79  #    *---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*    # pixel 60  | 3
            #                                                                                |    #           |----
  pixel 40  #    *---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*    # pixel 59  | 2
            #    |                                                                                #           |----
  pixel 39  #    *---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*    # pixel 20  | 1
            #                                                                                |    #           |----
  pixel 0   #----*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*    # pixel 19  | 0
            #  (0,0)                                                                              #           |-----
            #_____________________________________________________________________________________#           |ROWS

Each pixel is addressed incrementally on the string from the controllor starting at pixel 0.
Therefore, pixel 0 in the matrix is at position (0,0). However, pixel 21 is at position (19, 1)
because the string moves up to the next row from the end point of the previous row.
*/


/*
  /////////////////////////////////
 //     --- Includes ---        //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
//Wifi and NTP
//#include <NTPClient.h>
//#include <ESP8266WiFi.h>
//#include <WiFiUdp.h>

//IR Reciever
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>

//FastLED
#include <FastLED.h>

//Standard Library
#include <string>
#include <fstream>
#include <iostream>

//Custom Fonts
#include "./fonts/Font3x5.h"
#include "./fonts/Font6x5.h"

//Others
#include "./prototypes.h"
#include "./constants.h"

/*
  /////////////////////////////////
 //    --- Variables ---        //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
//Wifi and NTP
//WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetSec);
String curTime = "00:00";

//LEDS
CRGB leds[NUM_LEDS];

//IR
IRrecv irrecv(kRecvPin);
decode_results results;

//Fonts
int8_t CHAR_WIDTH   = 3; //num of pixels wide each character is.
int8_t CHAR_HEIGHT  = 5; //num of fixels high each character is.

//Script
Button buttonPress	= Nine;
Script script		= Announcements;

//Time
String timeStr = "NULL";
uint16_t curMinutes = 0;
uint16_t curHours = 0;
uint16_t totalTime = 0; //in minutes
uint8_t curDay = 0;
uint16_t curOpenTime = openTimes[curDay];
uint16_t curCloseTime = closeTimes[curDay];


/*
  /////////////////////////////////
 //    --- LED Funcs ---        //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
/*
    Info: 	Change from one font to another
    PreReq:	Must have the Font enum setup and pass a valid Font Enum as param
    Input:	Font enum
    Output:	None, global vars CHAR_HEIGHT and CHAR_WIDTH are modified
*/
void ChangeFont(Font newFont)
{
    //static std::bitset<30> normal = charMap6x5[character];
    //static std::bitset<30> bold = charMap6x5[character];
    switch(newFont)
    {
        case Normal:
            CHAR_WIDTH 	= 3;
            CHAR_HEIGHT = 5;
            //fontMatrix = &normal;
            break;
        case Bold:
            CHAR_WIDTH 	= 6;
            CHAR_HEIGHT = 5;
            //fontMatrix = &bold;
            break;
    }
}

/*
    Info: 	Protect against indexing an invalid index when accessing an LED
    PreReq:	NUM_LEDS must be defined as a non-negative number
    Input:	The uint16_t value of a proposed LED index
    Output:	The index of an LED on the actual string is valid
*/
bool ValidPix(uint16_t number)
{
    return (number >= 0 && number < NUM_LEDS);
}

/*
    Info: 	Retrieves the color values of specific colors so that the values don't need
            to be input manually every time.
    PreReq:	Color enum must be defined
    Input:	One of the following Color enumerables must be used;
            (Off, Red, Orange, Yellow, Green, Blue, Indigo, Violet, White, Random)
    Output:	An array of three color values in the order of [Red, Green Blue]. max value is 255, min is 0
*/
uint8_t* GetColor(Color col)
{
    static uint8_t rgb[3];
    uint8_t red, green, blue;

    switch(col)
    {
        case Unchanged:
            return nullptr;
        case Off:
            red = 0;	green = 0; 		blue = 0;
            break;
        case Red:
            red = 255;	green = 0; 		blue = 0;
            break;
        case DimRed:
            red = 50;	green = 0; 		blue = 0;
            break;
        case Orange:
            red = 255;	green = 200; 	blue = 0;
            break;
        case Yellow:
            red = 255;	green = 255; 	blue = 0;
            break;
        case BrightYellow:
            red = 194;	green = 252; 	blue = 3;
            break;
        case Green:
            red = 0;	green = 255; 	blue = 0;
            break;
        case SeafoamGreen:
            red = 3;	green = 252; 	blue = 186;
            break;
        case BrightGreen:
            red = 173;	green = 252; 	blue = 3;
            break;
        case DimGreen:
            red = 0;	green = 50; 	blue = 0;
            break;
        case Blue:
            red = 0;	green = 0; 		blue = 255;
            break;
        case SkyBlue:
            red = 0;	green = 242; 		blue = 255;
            break;
        case SoftBlue:
            red = 3;	green = 132; 		blue = 252;
            break;
        case DimBlue:
            red = 0;	green = 0; 		blue = 50;
            break;
        case Indigo:
            red = 85;	green = 0; 		blue = 125;
            break;
        case Violet:
            red = 128;	green = 0;		blue = 255;
            break;
        case Pink:
            red = 252;	green = 3; 	blue = 252;
            break;
        case White:
            red = 255;	green = 255;	blue = 255;
            break;
        case MediumWhite:
            red = 175;	green = 175;	blue = 175;
            break;
        case DimWhite:
            red = 50;	green = 50;		blue = 50;
            break;
        case On:
            red = 25;	green = 25;		blue = 25;
            break;
        case Random:
            red   = rand()%255; 
            green = rand()%255; 
            blue  = rand()%255;
            break;
    };

    rgb[0] = red;
    rgb[1] = green;
    rgb[2] = blue;

    return rgb;
}

/*
    Info: 	Locates the LED on the string so that its status can be updated.
    PreReq:	LED_WIDTH and LED_HEIGHT must be defined, I'm not sure what happens if you use an invalid
            coordinate. This could possibly be solved with something like (x % LED_WIDTH) and (y % LED_HEIGHT)
    Input:	The coordinates of the pixel matrix you want to get the pixel index from.
            Bottom Left is (0, 0), Top Right is (LED_WIDTH, LED_HEIGHT) 
    Output:	Index of an LED on the actual string, if the index is invalid the last LED is used
*/
uint16_t GetPixel(int16_t x, int16_t y) //gets a pixel from x, y coordinate in matrix
{
    uint16_t i;

    if(x < LED_WIDTH && x >= 0 && y < LED_HEIGHT && y >= 0)
    {
        if( y & 0x01) // Odd rows run backwards
        {
            int16_t reverseX = (LED_WIDTH - 1) - x;
            i = (y * LED_WIDTH) + reverseX;
        } 
        else // Even rows run forwards
        {
            i = (y * LED_WIDTH) + x;
        }

        i = ValidPix(i)? i: NUM_LEDS; //invalid values are output to last pixel
    }
    else
    {
        i = NUM_LEDS;
    }

    return i;
}

/*
    Info: 	Currently all pixels are lit with a random color. Temporary
    PreReq:	LED_HEIGHT and LED_WIDTH must be defined
    Input:	None
    Output:	None
*/
void Fill(Color fillColor)
{
    uint8_t *color = GetColor(fillColor);

    if(color)
    {
        for( int16_t y = 0; y < LED_HEIGHT; y++) 
        {
            for( int16_t x = 0; x < LED_WIDTH; x++) 
            {
                leds[GetPixel(x, y)]  = CRGB(color[0], color[1], color[2]);
            }
        }
    }
}

/*
    Info: 	Used to light up LEDs to form a alpha numeric character from the Font3x5 character map
            at a specified coordinate. The starting coordinate is the bottom left of the character.
            For the character to display, FastLED.show(); must be called after. This is not done
            in the function because FastLED.show(); is typically called after spelling a whole word
            so that the letters don't appear as they are processed.
    PreReq:	CHAR_WIDTH, CHAR_HEIGHT, LED_WIDTH, LED_HEIGHT, and Color enum must be defined 
            charMap3x5 must be defined with chars mapped to bitset<15> "this is done in Font3x5.h"
            Currently y coord must be zero, and x cannot exceed (LED_WIDTH - CHAR_WIDTH)
            This could possibly be solved with something like (x % LED_WIDTH) and (y % LED_HEIGHT)
    Input:	The 'char' that you want to display,
            Starting x coordinate of the bottom left of the character,
            Starting y coordinate of the bottom left of the character,
            A valid Enum color of (Off, Red, Orange, Yellow, Green, Blue, Indigo, Violet, White, Random)
    Output:	None
*/
void DrawChar(char character, int16_t xStartPos, int16_t yStartPos, Color charColor, Color bgColor, Font font)
{
    ChangeFont(font);

    std::bitset<15> normBitMatrix = charMap3x5[character];
    std::bitset<30> boldBitMatrix = charMap6x5[character];
    const uint8_t *fg = GetColor(charColor);
    uint8_t fgRed = fg[0], fgGreen = fg[1], fgBlue = fg[2];
    uint8_t *bg = GetColor(bgColor);
    uint8_t bgRed, bgGreen, bgBlue;
    int64_t count = 0, actualX=xStartPos, actualY=yStartPos;

    for(int16_t y=0; y < CHAR_HEIGHT; y++) 
    {
        for(int16_t x=0; x < CHAR_WIDTH; x++) 
        {
            switch(font)
            {
                case Normal:
                    if(normBitMatrix[count] == 1)
                    {
                        actualX = x + xStartPos; //) % LED_WIDTH;
                        actualY = y + yStartPos; //) % LED_HEIGHT;
                        leds[GetPixel(actualX, actualY)] = CRGB(fgRed, fgGreen, fgBlue);
                    }
                    else if(bg)
                    {
                        bgRed = bg[0]; bgGreen = bg[1]; bgBlue = bg[2];
                        actualX = x + xStartPos; //) % LED_WIDTH;
                        actualY = y + yStartPos; //) % LED_HEIGHT;
                        leds[GetPixel(actualX, actualY)] = CRGB(bgRed, bgGreen, bgBlue);
                    }
                    break;
                case Bold:
                    if(boldBitMatrix[count] == 1)
                    {
                        actualX = x + xStartPos; //) % LED_WIDTH;
                        actualY = y + yStartPos; //) % LED_HEIGHT;
                        leds[GetPixel(actualX, actualY)] = CRGB(fgRed, fgGreen, fgBlue);
                    }
                    else if(bg)
                    {
                        bgRed = bg[0]; bgGreen = bg[1]; bgBlue = bg[2];
                        actualX = x + xStartPos; //) % LED_WIDTH;
                        actualY = y + yStartPos; //) % LED_HEIGHT;
                        leds[GetPixel(actualX, actualY)] = CRGB(bgRed, bgGreen, bgBlue);
                    }
                    break;
            }

            count++;
        }
    }

    //FastLED.show();
    //
}

/*
    Info: 	Processes the characters of a string to display words using chapMap.
    PreReq:	CHAR_WIDTH and Color enum must be defined 
    Input:	String to be displayed,
            One of the following Color enumerables must be used;
            (Off, Red, Orange, Yellow, Green, Blue, Indigo, Violet, White, Random),
            FUTURE: TextEffect
    Output:	None
*/
void WriteText(String words, int16_t x, int16_t y, Color charColor, TextEffect effect, uint16_t effectSpeed, Color bgColor, Font font)
{
    ChangeFont(font);

    int16_t xStartPos = x, yStartPos = y;
    int16_t space = 1;
    int xAdvance = CHAR_WIDTH + space;
    int64_t wordsWidth = (words.length()*xAdvance);
    char curChar;

    switch(effect)
    {
        case Fixed: // Static text limited to 5 characters on a 19 LED wide display
            FastLED.clear();
            Fill(bgColor);

            //iterate over all the characters of dispText. Then advance the x position advances ahead for the next character
            //Two things must be kept track of 1.) The current character index; 2.) The x pixel index
            for(int16_t charIndex=0; charIndex < words.length(); charIndex++)
            {
                curChar = words[charIndex];
                DrawChar(curChar, xStartPos, yStartPos, charColor, Unchanged, font); //draw char could be sped up by passing each color value instead of calling getcolor for each char
                xStartPos += xAdvance;
            };

            FastLED.show();
            if(RXDelay(effectSpeed))break;
            break;
        case ScrollUp:
            WriteText(words, x, y, charColor, Fixed, 500, bgColor, font);
            for(int16_t up = 0; up < (LED_HEIGHT+1); up++)
            {
                FastLED.clear();
                Fill(bgColor);

                for(int16_t charIndex=0; charIndex < words.length(); charIndex++)
                {
                    curChar = words[charIndex];
                    DrawChar(curChar, xStartPos, (yStartPos+up), charColor, Unchanged, font);
                    xStartPos += xAdvance;
                };

                xStartPos = x;

                FastLED.show();
                if(up != LED_HEIGHT)
                {
                    if(RXDelay(effectSpeed))break;
                }	
            };

            RXDelay(10);
            break;
        case ScrollDown:
            
            break;
        case ScrollLeft:
            xStartPos = x + LED_WIDTH;

            for(int16_t left = 0; left < (wordsWidth + LED_WIDTH + CHAR_WIDTH + 1); left++)
            {
                FastLED.clear();
                Fill(bgColor);

                for(int16_t charIndex=0; charIndex < words.length(); charIndex++)
                {
                    curChar = words[charIndex];

                    if((xStartPos + CHAR_WIDTH) >= 0)
                    {
                        DrawChar(curChar, xStartPos, yStartPos, charColor, Unchanged, font);
                    }
                    
                    xStartPos += xAdvance;
                };

                xStartPos = x + LED_WIDTH - left;

                FastLED.show();
                if(left != LED_WIDTH + wordsWidth)
                {
                    if(RXDelay(effectSpeed))break;
                }	
            };

            RXDelay(10);
            break;
        case ScrollRight:
            xStartPos = x - wordsWidth;

            for(int16_t right = 0; right < (LED_WIDTH + wordsWidth + 1); right++)
            {
                FastLED.clear();
                Fill(bgColor);

                for(int16_t charIndex=0; charIndex < words.length(); charIndex++)
                {
                    curChar = words[charIndex];
                    if((xStartPos + CHAR_WIDTH) >= 0)
                    {
                        DrawChar(curChar, xStartPos, yStartPos, charColor, Unchanged, font);
                    }
                    
                    xStartPos += xAdvance;
                };

                xStartPos = x - wordsWidth + right;

                FastLED.show();
                if(right != LED_WIDTH + wordsWidth)
                {
                    if(RXDelay(effectSpeed))break;
                }	
            };

            RXDelay(10);
            break;
        case Blink:
            
            break;
        case FadeIn:
            
            break;
        case FadeOut:
            
            break;
    };
}

String ReadFile()
{
    
}

/*
  /////////////////////////////////
 //    --- Other Funcs ---      //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
/*
    Info:   A count down timer
    PreReq: Color enum must be defined
    Input:  None
    Output: None
*/
void StartTimer()
{

}


/*
    Info: 	Incrementally lights up LEDs with a random color with a fading trail
    PreReq:	Color enum must be defined
    Input:	None
    Output:	None
*/
void SnakingComet(uint16_t speed)
{
    int16_t trailLength = 10;
    uint8_t redColor = rand()%255, greenColor = rand()%255, blueColor = rand()%255;
    int posOne=0, posTwo=-1, posThree=-3, posFour=-6, posFive=(-1*trailLength);
    
    // Move leds 
    for(int pixPos = 0; pixPos < (NUM_LEDS+trailLength); pixPos++)
    {
        // change pixel colors
        if(ValidPix(posOne))
        {
            leds[posOne] = CRGB(redColor, greenColor, blueColor);
        }
        if(ValidPix(posTwo))
        {
            leds[posTwo] = CRGB(redColor/2, greenColor/2, blueColor);
        }
        if(ValidPix(posThree))
        {
            leds[posThree] = CRGB(redColor/4, greenColor/4, blueColor/4);
        }
        if(ValidPix(posFour))
        {
            leds[posFour] = CRGB(redColor/16, greenColor/16, blueColor/8); 
        }
        if(ValidPix(posFive))
        {
            leds[posFive] = CRGB(0,0,0);
        }

        //set pixel postions
        posOne++;
        posTwo++;
        posThree++;
        posFour++;
        posFive++;
        
        FastLED.show();
        if(RXDelay(speed))break;
    }
}

/*
    Info:   Runs specific scripts depending on what day it is and what time, allowing for custimized
            information specific to a day
    PreReq: The time client must initialize properly. This means that the wifi must be working. Also, 
            the time server must be up and sending time info.
    Input:  None
    Output: None
*/
void Scheduler()
{
    Serial.print("Today's Day of the week: ");
    Serial.println(curDay);
    Serial.print("Today's Open Time: ");
    Serial.println(curOpenTime);
    Serial.print("Today's Close Time: ");
    Serial.println(curCloseTime);
    Serial.print("Current Time in Minutes: ");
    Serial.println(totalTime);

    if(totalTime > curCloseTime)
    {
        Serial.println(" Currently Closed For The Night ");
        RXDelay(1000);
    }
    else if(totalTime > curCloseTime - 30)
    {
        Serial.println(" Closing Soon ");
        RunScript(Closing);
        RunScript(Announcements);
    }
    else if(totalTime > curOpenTime)
    {
        Serial.println(" Currently Open ");
        RunScript(FargoClimbing);
        RunScript(ClimbTime);
        RunScript(Announcements);
    }
    else if(totalTime > curOpenTime -30)
    {
        Serial.println(" Opening Soon ");
        RunScript(Opening);
    }
    else
    {
        Serial.println(" Currently Closed For The Morning ");
        RXDelay(5000);
        RunScript(Closed);
    }
};

void Comp()
{
    Serial.print("Current Time in Minutes: ");
    Serial.println(totalTime);
    
    if(totalTime >= 1065) // Open Climb 5:45 - Close
    {
        Serial.println("Open Climb");
        WriteText("OPEN CLIMB", 0, 0, Green, ScrollLeft, 100, Blue, Bold);
    }
    else if(totalTime >= 1035) //Prizes and Raffles 5:15PM - 5:45PM
    {
        Serial.println("Prizes and Raffles");
        WriteText("PRIZES AND RAFFLES", 0, 0, Green, ScrollLeft, 100, DimWhite, Bold);
    }
    else if(totalTime >= 990) //Open Finals 4:30PM - 5:15PM
    {
        Serial.println("Open Finals");
        WriteText("OPEN FINALS 4:30 - 5:15", 0, 0, Blue, ScrollLeft, 100, DimBlue, Bold);
    }
    else if(totalTime >= 975) //Dyno Challenge 4:15PM - 4:30PM
    {
        Serial.println("Dyno Challenge");
        WriteText("DYNO CHALLENGE", 0, 0, Green, ScrollLeft, 200, Blue, Bold);
        WriteText("DYNO", 0, 0, Red, ScrollUp, 150, DimWhite, Normal);
        WriteText("DYNO", 0, 0, Blue, ScrollUp, 100, DimWhite, Normal);
        WriteText("DYNO", 0, 0, Random, ScrollUp, 75, DimWhite, Normal);
    }
    else if(totalTime >= 960) //Session 2 Over 4:00PM - 4:15PM
    {
        Serial.println("End Session 2 turn in scoresheets");
        WriteText("END SESSION TWO", 0, 0, Red, ScrollLeft, 100, DimBlue, Bold);
        WriteText("TURN IN SCORESHEETS!", 0, 0, Red, ScrollLeft, 100, DimBlue, Bold);
    }
    else if(totalTime >= 780) //Session 2 1:00PM - 4:00PM
    {
        Serial.println("Session 2 in progress");
        WriteText("SESSION TWO 1:00 - 4:00", 0, 0, BrightGreen, ScrollLeft, 100, DimBlue, Bold);
    }
    else if(totalTime >= 760) //Session 2 rules and questions 12:40PM-1:00PM
    {
        Serial.println("Session 2 rules and questions");
        WriteText("SESSION TWO RULES AND QUESTIONS", 0, 0, Orange, ScrollLeft, 100, DimBlue, Bold);
    }
    else if(totalTime >= 735) //Session 2 Check in 12:15PM - 12:40PM
    {
        Serial.println("Session 2 check in");
        WriteText("SESSION TWO CHECK IN", 0, 0, Green, ScrollLeft, 100, DimBlue, Bold);
    }
    else if(totalTime >= 720) //Session 1 Over 12:00PM - 12:15PM
    {
        Serial.println("End Session 1 turn in scoresheets");
        WriteText("END SESSION ONE", 0, 0, Red, ScrollLeft, 100, DimBlue, Bold);
        WriteText("TURN IN SCORESHEETS!", 0, 0, Red, ScrollLeft, 100, DimBlue, Bold);
    }
    else if(totalTime >= 560) //Session 1 8:40AM - 12:00PM
    {
        Serial.println("Session 1 in progress");
        WriteText("SESSION ONE 8:40 - 12:00", 0, 0, Green, ScrollLeft, 100, DimBlue, Bold);
    }
    else if(totalTime >= 520) //Session 1 rules and questions 8:00AM - 8:40AM
    {
        Serial.println("Session 1 rules and questions");
        WriteText("SESSION ONE RULES AND QUESTIONS", 0, 0, Orange, ScrollLeft, 100, DimBlue, Bold);
    }
    else if(totalTime >= 480) //Registration 8:00AM
    {
        Serial.println("Registration");
        WriteText("REGISTRATION", 0, 0, Orange, ScrollLeft, 100, DimBlue, Bold);
    }
    else
    {
        Serial.println("Announcements");
        RunScript(Announcements);
    };
    
    RunScript(Time);
};

void RunScript(Script script, Font font)
{  
    switch(script)
    {
        case Demo:
            // iterate over all possible char values
            for(char curChar = ' '; curChar < 126; curChar++)
            {
                DrawChar(curChar, 8, 0, Random, Unchanged, Normal);
                FastLED.show();
                if(RXDelay(500))break;
                FastLED.clear();
            };

            // iterate over all possible char values
            for(char curChar = ' '; curChar < 126; curChar++)
            {
                DrawChar(curChar, 6, 0, Random, Unchanged, Bold);
                FastLED.show();
                if(RXDelay(500))break;
                FastLED.clear();
            };
            WriteText("TEST", 0, 0, Random, ScrollUp, 200, Random, Normal);
            WriteText("test", 0, 0, Random, ScrollUp, 200, Random, Normal);
            WriteText("TEST", 0, 0, Random, ScrollUp, 200, Random, Bold);
            WriteText("test", 0, 0, Random, ScrollUp, 200, Random, Bold);
            SnakingComet();
            break;
        case Party:
            WriteText("PARTY", 0, 0, BrightYellow, Fixed, 2000, DimBlue, Normal);
            WriteText("TIME", 2, 0, Pink, Fixed, 2000, DimBlue, Normal);
            WriteText("TIME", 2, 0, Random, ScrollUp, 200, Random, Normal);
            break;
        case Open:
            WriteText("OPEN", 0, 0, Green, ScrollLeft, 200, Off, Bold);
            //WriteText("OPEN", 2, 0, Green, Fixed, 3000, Off, Normal);
            //WriteText("OPEN", 2, 0, Green, ScrollUp, 200, Off, Normal);
            break;
        case Closed:
            WriteText("CLOSED", 0, 0, Red, ScrollLeft, 150, Off, Bold);
            //WriteText("CLOSE", 0, 0, Red, Fixed, 3000, Off, Normal);
            //WriteText("CLOSE", 0, 0, Red, ScrollUp, 200, Off, Normal);
            break;
        case Time:
            Serial.println(timeStr);
            WriteText(timeStr, 0 , 0, SeafoamGreen, ScrollLeft, 120, Off, Bold);
            break;
        case FargoClimbing:
            WriteText("FARGO", 0, 0, Red, ScrollLeft, 200, DimBlue, Bold);
            WriteText("CLIMBING", 0, 0, DimBlue, ScrollRight, 200, Off, Bold);
            break;
        case Birthday:
            SnakingComet();
            WriteText("HAPPY BIRTHDAY", 0, 0, Green, ScrollLeft, 150, Blue, Bold);
            WriteText("", 0, 0, Random, ScrollUp, 200, Random, Normal);
            break;
        case Justus:
            SnakingComet();
            WriteText("Moonbaord: JUSTUS > CHRIS", 0, 0, SeafoamGreen, ScrollLeft, 200, DimBlue, Bold);
            SnakingComet();
            break;
        case Crew:
            SnakingComet();
            WriteText("HALL OF FAME: ", 0, 0, SkyBlue, ScrollLeft, 300, DimWhite, Bold);
            WriteText("BEN W", 0, 0, Random, ScrollLeft, 200, Off, Bold);
            WriteText("CHRIS D", 0, 0, Random, ScrollLeft, 200, Off, Bold);
            WriteText("PAUL K", 0, 0, Random, ScrollLeft, 200, Off, Bold);
            WriteText("ERIC O", 0, 0, Random, ScrollLeft, 200, Off, Bold);
            break;
        case Timer:
            StartTimer();
            break;
        case ClimbTime:
            WriteText("CLIMB", 0 , 0, SeafoamGreen, ScrollRight, 100, Indigo, Bold);
            WriteText("TIME", 0 , 0, Violet, ScrollLeft, 100, SeafoamGreen, Bold);
            break;
        case Opening:
            WriteText("OPENING SOON", 0 , 0, Green, ScrollLeft, 100, DimBlue, Bold);
            break;
        case Closing:
            WriteText("CLOSING SOON", 0 , 0, Red, ScrollLeft, 100, DimBlue, Bold);
            break;
        case DailySchedule: 
            Scheduler();
            break;
        case Competition:
            Comp();
            break;
        case CompResults:
            WriteText("WOOD CHIPPER RESULTS: ", 0, 0, Orange, ScrollLeft, 100, DimGreen, Bold);
            WriteText("1st OPEN: JOHN DOE, JANE DOE", 0, 0, BrightYellow, ScrollLeft, 75, SoftBlue, Bold);
            WriteText("2nd OPEN: BILL LOE, SARA LOE", 0, 0, White, ScrollLeft, 75, SoftBlue, Bold);
            WriteText("3rd OPEN: JOE BLOW, ANN BLOW", 0, 0, Orange, ScrollLeft, 75, SoftBlue, Bold);

            WriteText("1st ADVANCED: JOHN DOE, JANE DOE", 0, 0, BrightYellow, ScrollLeft, 75, SoftBlue, Bold);
            WriteText("2nd ADVANCED: BILL LOE, SARA LOE", 0, 0, White, ScrollLeft, 75, SoftBlue, Bold);
            WriteText("3rd ADVANCED: JOE BLOW, ANN BLOW", 0, 0, Orange, ScrollLeft, 75, SoftBlue, Bold);

            WriteText("1st INTERMEDIATE: JOHN DOE, JANE DOE", 0, 0, BrightYellow, ScrollLeft, 75, SoftBlue, Bold);
            WriteText("2nd INTERMEDIATE: BILL LOE, SARA LOE", 0, 0, White, ScrollLeft, 75, SoftBlue, Bold);
            WriteText("3rd INTERMEDIATE: JOE BLOW, ANN BLOW", 0, 0, Orange, ScrollLeft, 75, SoftBlue, Bold);

            WriteText("1st BEGINNER: JOHN DOE, JANE DOE", 0, 0, BrightYellow, ScrollLeft, 75, SoftBlue, Bold);
            WriteText("2nd BEGINNER: BILL LOE, SARA LOE", 0, 0, White, ScrollLeft, 75, SoftBlue, Bold);
            WriteText("3rd BEGINNER: JOE BLOW, ANN BLOW", 0, 0, Orange, ScrollLeft, 75, SoftBlue, Bold);

            WriteText("1st YOUTH: JOHN DOE, JANE DOE", 0, 0, BrightYellow, ScrollLeft, 75, SoftBlue, Bold);
            WriteText("2nd YOUTH: BILL LOE, SARA LOE", 0, 0, White, ScrollLeft, 75, SoftBlue, Bold);
            WriteText("3rd YOUTH: JOE BLOW, ANN BLOW", 0, 0, Orange, ScrollLeft, 75, SoftBlue, Bold);
            
            SnakingComet();
        case Announcements:
            RunScript(CompResults);
            RunScript(FargoClimbing);
            RunScript(ClimbTime);
            break;
        case None:

            break;
    };
}

void GetIRSignal()
{
    /*
        The button order is for a remote 3 buttons X 7 buttons

          [IR Blaster]
        ______\|/_______
        |(1 ) (2 ) (3 )|
        |(4 ) (5 ) (6 )|
        |(7 ) (8 ) (9 )|
        |(10) (11) (12)|
        |(13) (14) (15)|
        |(16) (17) (18)|
        ''''''''''''''''
    */
    if (irrecv.decode(&results))
    {
        switch(results.value)
        {
            case CHminus:   // 1
                buttonPress = CHminus;
                script = Demo;
                break;
            case CH:        // 2
                buttonPress = CH;
                script = FargoClimbing;
                break;
            case CHplus:    // 3
                buttonPress = CHplus;
                script = Party;
                break;
            case Previous:  // 4
                buttonPress = Previous;
                script = Birthday;
                break;
            case Next:      // 5
                buttonPress = Next;
                script = Open;
                break;
            case Play:      // 6
                buttonPress = Play;
                script = Closed;
                break;
            case Minus:     // 7
                buttonPress = Minus;
                script = Time;
                break;
            case Plus:      // 8
                buttonPress = Plus;
                script = Justus;
                break;
            case Equal:     // 9
                buttonPress = Equal;
                script = FargoClimbing;
                break;
            case Zero:      // 10
                buttonPress = Zero;
                script = Timer;
                break;
            case OneHund:   // 11
                buttonPress = OneHund;

                break;
            case TwoHund:   // 12
                buttonPress = TwoHund;

                break;
            case One:       // 13
                buttonPress = One;

                break;
            case Two:       // 14
                buttonPress = Two;

                break;
            case Three:     // 15
                buttonPress = Three;

                break;
            case Four:      // 16
                buttonPress = Four;

                break;
            case Five:      // 17
                buttonPress = Five;

                break;
            case Six:       // 18
                buttonPress = Six;

                break;
            case Seven:     // 19
                buttonPress = Seven;

                break;
            case Eight:     // 20
                buttonPress = Eight;

                break;
            case Nine:      // 21
                buttonPress = Nine;
                script = DailySchedule;
                break;
            case Hold:      // 22
            default:
                break;
        };

        irrecv.resume();
    };
}

/* 
    if(RXDelay(n))
    {
        break;
    }
*/
bool RXDelay(int time)
{
    Script tmpScript = script;
    for(int t=0; t<(time/10); t++)
    {
        GetIRSignal();
        delay(10);
        if(script != tmpScript)
        {
            return true;
        }
    };
    return false;
}


/*
  /////////////////////////////////////////////
 //     --- Program Initialization ---      //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
/*
    Info: 	This is the first function to be called and sets up everything needed for the
            program to run correctly
    PreReq:	None
    Input:	None
    Output:	None
*/
void setup() 
{
    uint16_t count = 0;
    const uint8_t *tmpColor = GetColor(Random);
       
    //Setup Serial
    Serial.begin(9600);
        
    //Setup NTP Client
    /*
    WiFi.begin(ssid, password);
    */
    
    //Setup IR Reciever
    irrecv.enableIRIn();

    //Setup LEDS
    if(LED_WIDTH * LED_HEIGHT > NUM_LEDS || LED_WIDTH * LED_HEIGHT < 0 || BRIGHTNESS > 255 || BRIGHTNESS < 0)
    {
        exit(0);
    }
    else
    {
        FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050); //TypicalPixelString);//correction types: TypicalLEDStrip, TypicalSMD5050, TypicalLEDStrip, TypicalPixelString
        FastLED.setMaxPowerInVoltsAndMilliamps(VOLTAGE, MAX_POWER_MILLIAMPS);
        FastLED.setBrightness(BRIGHTNESS );
    }

    /*
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print (".");
        leds[count % NUM_LEDS] = CRGB(tmpColor[0], tmpColor[1], tmpColor[2]);
        FastLED.show();
        count++;
        delay(100);
    }

    timeClient.begin();
    timeClient.setUpdateInterval(6000);
    */
}


/*
  /////////////////////////////////
 //    --- Main Loop ---        //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
/*
    Info: 	This function is continuously called while the device is powered and is where the main
            code goes
    PreReq:	None
    Input:	None
    Output:	None
*/
void loop() 
{
    /*
    while(!timeClient.update())
    {
        Fill(Random);
        SnakingComet(15);
    }

    curMinutes = timeClient.getMinutes();
    curHours = timeClient.getHours();
    curDay = timeClient.getDay();
    curOpenTime = openTimes[curDay];
    curCloseTime = closeTimes[curDay];

    totalTime = (curHours * 60) + curMinutes;
    timeStr =   daysOfTheWeek[curDay] + " " + timeClient.getFormattedTime();
    
    RXDelay(50);
    */

    if(script > -1)
    {
        //Scheduler();
        RunScript(Announcements);
    }
    else
    {
        Serial.println("Select a Script");
        FastLED.clear();
        WriteText("Select Script", 0, 0, BrightGreen, ScrollLeft, 100, Off, Bold);
    }
    
    
    RXDelay(50);
}
