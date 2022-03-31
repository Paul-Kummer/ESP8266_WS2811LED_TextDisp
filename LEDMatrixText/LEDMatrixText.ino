/*
	Author: Paul Kummer
	Date: 3/20/2022
	License: Open Source
	File: WriteText.ino
*/


/*
	Notes:	1) Should maybe add or find a fill background function instead of having write char do it
			2) 

	  /////////////////////////////////
	 //		--- Information ---		//
	/////////////////////////////////

				[ INDIVIDUALLY ADDRESSABLE PIXEL STRING LAYOUT AS MATRIX ]

	(Symbol : Description)
	#   : Border Frame
	_   : Border Frame
	*   : Individually Addressable LED Pixel
	- : 3-wire LED connecting wires

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
	 //		--- Includes ---		//
	/////////////////////////////////
*/
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
#include "Font3x5.h"
#include "Font6x5.h"


/*
	  /////////////////////////////////
	 //		--- Constants ---		//
	/////////////////////////////////
*/
//LED Values
#define LED_TYPE            WS2811
#define DATA_PIN            2
#define COLOR_ORDER         RGB
#define NUM_LEDS            100
#define BRIGHTNESS          250
#define VOLTAGE             5
#define MAX_POWER_MILLIAMPS 2000 //3000 is max for my PSU
#define LED_WIDTH			19
#define LED_HEIGHT			5

//IR Values
const uint16_t kRecvPin = 14;
const uint32_t kBaudRate = 74880; //74880 115200


/*
	  /////////////////////////////////////////////
	 //		--- Enums/Classes/Structs ---		//
	/////////////////////////////////////////////
*/
enum Font //not used yet
{
	Normal,		//3x5
	Bold		//6x5
};

enum Script
{
	Demo,
	Open,
	Closed,	
	NowOpen,
	Party,
	Birthday,
	Time,			//Not Made
	Justus,
	Crew,
	None
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
	 //		--- Function Declarations ---		//
	/////////////////////////////////////////////
*/
void ChangeFont(Font newFont);
bool ValidPix(uint16_t number);
uint8_t* GetColor(Color col); 
uint16_t GetPixel(int16_t x, int16_t y);
void Fill(Color fillColor=Random);
void SnakingComet(uint16_t speed=10);
void Fireworks(); //Not Finished
void Launch(int16_t numOfCannons); //Helper for Fireworks
void Explode(int16_t numOfCannons, int16_t explodeHeight); //Helper for Fireworks, Not Finished
void DrawChar(char character, int16_t xStartPos=7, int16_t yStartPos=0, Color charColor=White, Color bgColor=Unchanged, Font = Normal);
void WriteText(std::string words, int16_t x=0, int16_t y=0, Color charColor=White, TextEffect effect=Fixed, uint16_t effectSpeed=500, Color bgColor=Unchanged, Font=Normal);
void RunScript(Script scriptNum=Demo, Font=Normal);
void GetIRSignal();
void setup();
void loop();


/*
	  /////////////////////////////////
	 //		--- Variables ---		//
	/////////////////////////////////
*/
//LEDS
CRGB leds[NUM_LEDS];

//IR
IRrecv irrecv(kRecvPin);
decode_results results;

//Fonts
int8_t CHAR_WIDTH   = 3; //num of pixels wide each character is.
int8_t CHAR_HEIGHT  = 5; //num of fixels high each character is.

//Script
Button buttonPress	= Hold;
Script script		= Open;


/*
	  /////////////////////////////////
	 //		--- Functions ---		//
	/////////////////////////////////
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
	Info: 	Displays fireworks effect launched from a specified amount of cannons
	PreReq:	Color enum must be defined
	Input:	None
	Output:	None
*/
void Fireworks()
{
	int16_t numOfCannons = 3, explodeHeight = LED_HEIGHT-1;

	Launch(numOfCannons);

	//Explode(numOfCannons, explodeHeight);
}

//Fireworks helper
void Launch(int16_t numOfCannons)
{
	int16_t travelSpeed = 100;
	int16_t cannonSpacing = (LED_WIDTH / (numOfCannons+1));
	int16_t x = 0, y = 0;

	//comet trail
	for(; y < LED_HEIGHT+3; y++)
	{
		FastLED.clear();
		for(int16_t cannon = 0; cannon < numOfCannons; cannon++)
		{
			int16_t ballY = y > LED_HEIGHT? LED_HEIGHT - (y % LED_HEIGHT): y; // allows the comet to drop down
			int16_t trailY = (y-1) > LED_HEIGHT? LED_HEIGHT - ((y-1) % LED_HEIGHT): y-1;
			x += (cannonSpacing+1);

			if(y==0) //initial blast
			{
				leds[GetPixel(x-1, y+1)] = CRGB(200, 0, 0); 	//Top Left
				leds[GetPixel(x, y+1)] = CRGB(255, 255, 240); 	//Top Mid
				leds[GetPixel(x+1, y+1)] = CRGB(200, 0, 0); 	//Top Right
				leds[GetPixel(x-1, y)] = CRGB(200, 0, 0); 		//Bottom Left
				leds[GetPixel(x, y)] = CRGB(255, 255, 255); 	//Cannon Location
				leds[GetPixel(x+1, y)] = CRGB(200, 0, 0); 		//Bottom Right

				FastLED.show();
				if(RXDelay(10))break;
			}
			
			leds[GetPixel(x, ballY)] = CRGB(255, 190, 0);
			leds[GetPixel(x, trailY)] = CRGB(200, 100, 0);
		}
		x = 0;
		
		FastLED.show();
		if(RXDelay(travelSpeed))break;
		travelSpeed += 200;
	}
}

//EXPLOSION NOT WORKING
//Fireworks helper
void Explode(int16_t numOfCannons, int16_t explodeHeight)
{
	int16_t blastBox = 0;
	int16_t explodeFrames = 5;
	int16_t cannonSpacing = (LED_WIDTH / (numOfCannons+1));
	int16_t x = 0, y = 0;

	for(int16_t frame = 0; frame<explodeFrames; frame++)
	{
		blastBox = blastBox==4? 4: blastBox++;

		for(int16_t cannon = 0; cannon < numOfCannons; cannon++)
		{
			x += (cannonSpacing+1);

			for(int16_t growX = 0; growX<blastBox; growX++)
			{
				for(int16_t growY = 0; growY<blastBox; growY++)
				{
					uint8_t *blastColor;

					switch(frame)
					{
						case 0:
							blastColor = GetColor(Yellow);
							leds[GetPixel(x, y)] = CRGB(blastColor[0], blastColor[1], blastColor[2]);
							break;
						case 1:
						case 2:
						case 3:
							blastColor = GetColor(Blue);
							break;
						case 4:
						case 5:
							blastColor = GetColor(Random);
							break;
						default:
							blastColor = GetColor(Off);
							break;
					}

					leds[GetPixel(x-growX, y-growY)] = CRGB(blastColor[0], blastColor[1], blastColor[2]);
				}
			}
		}
		x = 0;

		FastLED.show();
		if(RXDelay(200))break;
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
	int16_t count = 0, actualX=xStartPos, actualY=yStartPos;

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
void WriteText(std::string words, int16_t x, int16_t y, Color charColor, TextEffect effect, uint16_t effectSpeed, Color bgColor, Font font)
{
	ChangeFont(font);

	int16_t xStartPos = x, yStartPos = y;
	int16_t space = 1;
	int16_t xAdvance = CHAR_WIDTH + space;
	int16_t wordsWidth = (words.length()*xAdvance);
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
			Fireworks();
			break;
		case Party:
			FastLED.clear();
			WriteText("PARTY", 0, 0, BrightYellow, Fixed, 2000, DimBlue, Normal);
			WriteText("TIME", 2, 0, Pink, Fixed, 2000, DimBlue, Normal);
			WriteText("TIME", 2, 0, Random, ScrollUp, 200, Random, Normal);
			FastLED.clear();
			break;
		case Open:
			FastLED.clear();
			WriteText("OPEN", 0, 0, Green, ScrollLeft, 200, Blue, Bold);
			WriteText("OPEN", 2, 0, Green, Fixed, 3000, Blue, Normal);
			WriteText("OPEN", 2, 0, Green, ScrollUp, 200, DimBlue, Normal);
			FastLED.clear();
			break;
		case Closed:
			FastLED.clear();
			WriteText("CLOSED", 0, 0, Red, ScrollLeft, 200, Blue, Bold);
			WriteText("CLOSE", 0, 0, Red, Fixed, 3000, Blue, Normal);
			WriteText("CLOSE", 0, 0, Red, ScrollUp, 200, DimBlue, Normal);
			FastLED.clear();
			break;
		case Time:
			FastLED.clear();
			WriteText("TIME",2 , 0, Violet, ScrollUp, 750, Off, Normal);
			FastLED.clear();
			WriteText("CLIMB", 0 , 0, Red, ScrollRight, 100, DimBlue, Bold);
			WriteText("TIME", 0 , 0, Blue, ScrollLeft, 100, Off, Bold);
			FastLED.clear();
			break;
		case NowOpen:
			SnakingComet();
			WriteText("FARGO CLIMBING", 0, 0, Red, ScrollLeft, 200, DimBlue, Bold);
			WriteText("OPEN", 2, 0, Green, ScrollUp, 400, DimBlue, Normal);
			FastLED.clear();
			break;
		case Birthday:
			SnakingComet();
			WriteText("HAPPY BIRTHDAY", 0, 0, Green, ScrollLeft, 150, Blue, Bold);
			WriteText("", 0, 0, Random, ScrollUp, 200, Random, Normal);
			break;
		case Justus:
			SnakingComet();
			WriteText("JUSTUS SUCKS AT MOONBOARDING!", 0, 0, SeafoamGreen, ScrollLeft, 125, DimBlue, Bold);
			SnakingComet();
			break;
		case Crew:
			SnakingComet();
			WriteText("The", 0, 0, SkyBlue, ScrollUp, 500, DimWhite, Bold);
			WriteText("OGs", 0, 0, SkyBlue, ScrollUp, 500, DimWhite, Bold);
			WriteText("PAUL", 0, 0, Random, ScrollLeft, 200, Off, Bold);
			WriteText("ERIC", 0, 0, Random, ScrollLeft, 200, Off, Bold);
			WriteText("CHRIS", 0, 0, Random, ScrollLeft, 200, Off, Bold);
			WriteText("BEN", 0, 0, Random, ScrollLeft, 200, Off, Bold);
			WriteText("SEPEHR", 0, 0, Random, ScrollLeft, 200, Off, Bold);
			break;			
		case None:
		default:
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
			case CHminus:
				buttonPress = CHminus;
				script = Demo;
				break;
			case CH:
				buttonPress = CH;
				script = NowOpen;
				break;
			case CHplus:
				buttonPress = CHplus;
				script = Party;
				break;
			case Previous:
				buttonPress = Previous;
				script = Birthday;
				break;
			case Next:
				buttonPress = Next;
				script = Open;
				break;
			case Play:
				buttonPress = Play;
				script = Closed;
				break;
			case Minus:
				buttonPress = Minus;
				script = Time;
				break;
			case Plus:
				buttonPress = Plus;
				script = Justus;
				break;
			case Equal:
				buttonPress = Equal;
				script = Crew;
				break;
			case Zero:
				buttonPress = Zero;

				break;
			case OneHund:
				buttonPress = OneHund;

				break;
			case TwoHund:
				buttonPress = TwoHund;

				break;
			case One:
				buttonPress = One;

				break;
			case Two:
				buttonPress = Two;

				break;
			case Three:
				buttonPress = Three;

				break;
			case Four:
				buttonPress = Four;

				break;
			case Five:
				buttonPress = Five;

				break;
			case Six:
				buttonPress = Six;

				break;
			case Seven:
				buttonPress = Seven;

				break;
			case Eight:
				buttonPress = Eight;

				break;
			case Nine:
				buttonPress = Nine;

				break;
			case Hold:
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
	 //		--- Program Initialization ---		//
	/////////////////////////////////////////////
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
	//Setup IR Reciever
	irrecv.enableIRIn();

	//Setup LEDS
	if(LED_WIDTH * LED_HEIGHT > NUM_LEDS || LED_WIDTH * LED_HEIGHT < 0 || BRIGHTNESS > 255 || BRIGHTNESS < 0)
	{
		exit(0);
	}
	else
	{
		FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalPixelString);//correction types: TypicalLEDStrip, TypicalSMD5050, TypicalLEDStrip, TypicalPixelString
		FastLED.setMaxPowerInVoltsAndMilliamps(VOLTAGE, MAX_POWER_MILLIAMPS);
		FastLED.setBrightness(BRIGHTNESS );
	}
}


/*
	  /////////////////////////////////
	 //		--- Main Loop ---		//
	/////////////////////////////////
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
	RXDelay(10);
	RunScript(script, Normal);
}
