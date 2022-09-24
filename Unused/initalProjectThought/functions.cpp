#include "constants.h"
#include "prototypes.h"
#include <iostream>
#include <fstream>
#include <string>


/*
	[ INDIVITUALLY ADDRESSABLE PIXEL STRING LAYOUT AS MATRIX ]

		(Symbol	: Description)
			# 	: Border Frame
			_ 	: Border Frame
			* 	: Individually Addressable LED Pixel
			-	: 3-wire LED connecting wires
			X	: Pixel is lit up

			COLUMNS| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10 |11 |12 |13 |14 |15 |16 |17 |18 |19
				_______________________________________________________________________________________
				#                                                         (NUMOFCOLUMNS, NUMOFROWS)   #				
	pixel 80	#    *---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*    # pixel 99	| 4
				#    |                                                                                #				|----
	pixel 79	#    *---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*    # pixel 60	| 3
				#                                                                                |    #				|----
	pixel 40	#    *---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*    # pixel 59	| 2
				#    |                                                                                #				|----
	pixel 39	#    *---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*    # pixel 20    | 1
				#                                                                                |    #				|----
	pixel 0		#----*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*    # pixel 19 	| 0
				#  (0,0)                                                                              #				|-----
				#_____________________________________________________________________________________#				|ROWS

	Each pixel is addressed incrementally on the string from the controllor starting at pixel 0.
	Therefore, pixel 0 in the matrix is at position (0,0). However, pixel 21 is at position (19, 1)
	because the string moves up to the next row from the end point of the previous row.
*/


/*
			Two approaches to printing the text
	A. 	write the characters as they are encountered
	B. 	put the characters into an array possibly bigger than the pixel array and use
		the actual display matrix like a window into the text matrix. This would be similar
		to intersecting the two arrays at a specified point.
*/


//parse the text into characters for an array
void TextToArr(int startX, int startY)
{
	std::string dispStr;
	std::ofstream dispText.open("DISPLAY.txt");

	dispText.close();
}

void Draw(int startX, int startY)
{
	int pixNum = 0; // the current pixel that we are at in the actual string
	Pixel curPixel; // the pixel in the matrix array
	int curRow; //y coord
	int curColumn; //x coord


	//Transform the linear pixel position into matrix position
	//Start by iterating over every pixel in the string
	for(int pixNum=0; curPixel < NUMOFPIXELS; pixNum++)
	{
		curRow = pixNum % NUMOFCOLUMNS;

		/*
			because the rows alternate back and forth with the wiring, the addressing needs
			matrix translation to compensate by chaning the pixel location base on 
			even or odd row number
		*/

		// Odd Rows: 	index is the total number of pixels up to the end of the next row then subract the pixNum plus one to move backwards. The plus one is for zero index
		// Even Rows: 	index is the current pixNum minus the number of previous pixels from other rows 
		curColumn = curRow % 2 == 0? pixNum - (curRow * NUMOFCOLUMNS): ((curRow + 1) * NUMOFCOLUMNS) - (pixNum + 1));
		
		// This is the pixel from the matrix that corresponds to the actual pixel in the actual string
		curPixel = PIXARR[curColumn][curRow];

		// Transfer the matrix pixel properties to the actual string pixel
		int red = curPixel.getRed();
		int green = curPixel.getGreen();
		int blue = curPixel.getBlue();

		//ledPix actualPixel = LEDString[pixNum];
		//actualPixel.red = red;
		//actualPixel.green = green;
		//actualPixel.blue = blue;
		//actualPixel.show();

	}
}