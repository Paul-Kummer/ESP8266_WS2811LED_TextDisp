/*
    Author: Paul Kummer
    Date: 9/24/2022
    License: Open Source
    File: prototypes.h
*/

#include <iostream>

/*
  /////////////////////////////////////////////
 //    --- Enums/Classes/Structs ---        //
/////////////////////////////////////////////
*/
enum Day
{
    Sunday, 
    Monday, 
    Tuesday, 
    Wednesday, 
    Thursday, 
    Friday,
    Saturday
};

enum Font
{
    Normal,		//3x5
    Bold		//6x5
};

enum Script
{
    Demo,
    Open,
    Closed,	
    FargoClimbing,
    Party,
    Birthday,
    Time,
    Justus,
    Crew,
    Timer,          //Not Complete
    ClimbTime,
    Opening,
    Closing,
    DailySchedule,
    Competition,
    CompResults,
    Announcements,
    None = -1
};

enum TextEffect
{
    Fixed,
    ScrollUp,
    ScrollDown,		//Not Made
    ScrollLeft,
    ScrollRight,
    Blink, 			//Not Made
    FadeIn, 		//Not Made
    FadeOut 		//Not Made
};

enum Color
{
    Unchanged,
    Off,
    Red,
    DimRed,
    Orange,
    Yellow,
    BrightYellow,
    Green,
    BrightGreen,
    SeafoamGreen,
    DimGreen,
    Blue,
    SkyBlue,
    SoftBlue,
    DimBlue,
    Indigo,
    Pink,
    Violet,
    White,
    MediumWhite,
    DimWhite,
    On,
    Random
};

enum Button
{
    CHminus 	= 0xFFA25D,
    CH 			= 0xFF629D,
    CHplus 		= 0xFFE21D,
    Previous 	= 0xFF22DD,
    Next 		= 0xFF02FD,
    Play 		= 0xFFC23D,
    Minus 		= 0xFFE01F,
    Plus 		= 0xFFA857,
    Equal		= 0xFF906F,
    Zero 		= 0xFF6897,
    OneHund 	= 0xFF9867,
    TwoHund 	= 0xFFB04F,
    One 		= 0xFF30CF,
    Two 		= 0xFF18E7,
    Three 		= 0xFF7A85,
    Four 		= 0xFF10EF,
    Five 		= 0xFF38C7,
    Six 		= 0xFF5AA5,
    Seven 		= 0xFF42BD,
    Eight 		= 0xFF4AB5,
    Nine 		= 0xFF52AD,
    Hold		= 0xFFFFFF
};


/*
  /////////////////////////////////////////////
 //    --- Function Declarations ---        //
/////////////////////////////////////////////
*/
void ChangeFont(Font newFont);
bool ValidPix(uint16_t number);
uint8_t* GetColor(Color col); 
uint16_t GetPixel(int16_t x, int16_t y);
String ReadFile();
void Fill(Color fillColor=Random);
void StartTimer();
void SnakingComet(uint16_t speed=10);
void Scheduler();
void Comp();
void DrawChar(char character, int16_t xStartPos=7, int16_t yStartPos=0, Color charColor=White, Color bgColor=Unchanged, Font=Normal);
void WriteText(String words, int16_t x=0, int16_t y=0, Color charColor=White, TextEffect effect=Fixed, uint16_t effectSpeed=500, Color bgColor=Unchanged, Font=Normal);
void RunScript(Script scriptNum=Demo, Font=Normal);
void GetIRSignal();
bool RXDelay(int time);
void setup();
void loop();
