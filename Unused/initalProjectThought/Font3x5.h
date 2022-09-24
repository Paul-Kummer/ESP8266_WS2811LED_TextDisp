#include <bitset>
//#include <FastLED.h>

const int CHARWIDTH = 3;
const int CHARHEIGHT = 5;

extern const uint8_t LED_WIDTH;
extern const uint8_t LED_HEIGHT;
extern uint8_t NUM_LEDS;
extern CRGB leds[];

extern uint16_t GetPixel(uint8_t x, uint8_t y);
void DrawChar(std::bitset<15> charBits);


/*
								[ INDIVITUALLY ADDRESSABLE PIXEL STRING LAYOUT AS MATRIX ]

		(Symbol	: Description)
			# 	: Border Frame
			_ 	: Border Frame
			* 	: Individually Addressable LED Pixel
			-	: 3-wire LED connecting wires

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



enum TextEffect
{
	scrollOff 	= 0,
	scrollLoop 	= 1,
	blink		= 2,
	fadeIn		= 3,
	fadeOut		= 4,
	zoomIn		= 5,
	zoomOut		= 6
};


enum Color
{
	off			= 0,
	red			= 1,
	orange		= 2,
	yellow		= 3,
	green		= 4,
	blue		= 5,
	indigo		= 6,
	violet		= 7,
	white		= 8
};


uint8_t* GetRGB(Color col)
{
	uint8_t rgb[3] = {};
	uint8_t red, green, blue;

	switch(col)
	{
		case Color.off:
			red = 0;	green = 0; 		blue = 0;
			break;
		case Color.red:
			red = 255;	green = 0; 		blue = 0;
			break;
		case Color.orange:
			red = 255;	green = 200; 	blue = 0;
			break;
		case Color.yellow:
			red = 255;	green = 255; 	blue = 0;
			break;
		case Color.green:
			red = 0;	green = 255; 	blue = 0;
			break;
		case Color.blue:
			red = 0;	green = 0; 		blue = 255;
			break;
		case Color.indigo:
			red = 85;	green = 0; 		blue = 125;
			break;
		case Color.violet:
			red = 128;	green = 0;		blue = 255;
			break;
		case Color.white:
			red = 255;	green = 255;	blue = 255;
			break;
	};

	rgb[0] = red;
	rgb[1] = green;
	rgb[2] = blue;

	return rgb;
}


// This font is only 3 pixels wide and 5 pixels high
// Note:	If the Hex or Decimal values are used instead of the bitset, 
//			the values will have to be padded to make the binary 15 in length
std::bitset<15>* GetChar (char makeChar, int16_t startX, int16_t startY)
{
	/* 
							[ CHARBITS POSITIONS ]

		The pixels illuminated will be bit "1" and off is "0". The
		letters denote positions only, and must be replaced with a "1" or "0".
		Positions are backwards because index zero is the last character.

									<--------
								A		B		C 
							|	D		E		F
							|	G		H		I
							V	J		K		L
								M		N		O

							charBits = "CBAFEDIHGLKJONM";
	*/

	std::bitset<15> charBits;

	switch(makeChar)
	{
		  /////////////////////////////////////////////////////
		 //		--- SYMBOLS, OPERATORS, PUNCTUATION ---		//
		/////////////////////////////////////////////////////
		/*





		*/
		case ' ':
			charBits = "000000000000000";
			break;
		/*
			  # 
			  # 
			  # 
			
			  # 
		*/
		case '!':
			charBits = "010010010000010"; // Hex: 2482; Dec: 9346
			break;
		/*
			  # 
			# # #
			  # 
			# # #
			  # 
		*/
		case '$':
			charBits = "010111010111010"; // Hex: 2EBA; Dec: 11962
			break;
		/*
			#   #
				#    
			  #   
			#	  
			#   #   
		*/
		case '%':
			charBits = "101100010001101"; // Hex: 588D; Dec: 22669
			break;
		/*
				
			  #  
			# # #
			  #  
				
		*/
		case '+':
			charBits = "000010111010000"; // Hex: 5D0; Dec: 1488
			break;
		/*
			
				
			# # #
			
			
		*/
		case '-':
			charBits = "000000111000000"; // Hex: 1C0; Dec: 448
			break;
		/*
			
			#   #
			  # 
			#   #
			
		*/
		case '*':
			charBits = "000101010101000"; // Hex: AA8; Dec: 2728
			break;
		/*
			
			
			
			
			# 
		*/
		case '.':
			charBits = "00000000000001"; // Hex: 1; Dec: 1
			break;
		/*
					
				#
			  # 
			#  
			
		*/
		case '/':
			charBits = "000100010001000"; // Hex: 888; Dec: 2184
			break;
		/*
			
			  # 
			
			  #
			
		*/
		case ':':
			charBits = "000010000010000"; // Hex: 410; Dec: 1040
			break;
		/*
				#
			  # 
			# 
			  # 
				#
		*/
		case '<':
			charBits = "100010001010100"; // Hex: 4454; Dec: 17492
			break;
		/*
			
			# # #
			
			# # #
			
		*/
		case '=':
			charBits = "000111000111000"; // Hex: E38; Dec: 3640
			break;
		/*
			# 
			  # 
				#
			  # 
			# 
		*/
		case '>':
			charBits = "001010100010001"; // Hex: 1511; Dec: 5393
			break;
		/*
			  # # 
				#
			  # 
				
			  # 
		*/
		case '?':
			charBits = "110100010000010"; // Hex: 6882; Dec: 26754
			break;


		//NUMBERS
		/*
			# # #
			#   #
			#   #
			#   #
			# # #
		*/
		case '0':
			charBits = "111101101101111"; // Hex: 7B6F; Dec: 31599
			break;
		/*
			  # 
			# # 
			  # 
			  # 
			# # #
		*/
		case '1':
			charBits = "010011010010111"; // Hex: 2697; Dec: 9879
			break;
		/*
			  # 
			#   #
			  # 
			#   
			# # #
		*/
		case '2':
			charBits = "010101010001111"; // Hex: 2A8F; Dec: 10895
			break;
		/*
			# # #
				#
			  # #
				#
			# # #
		*/
		case '3':
			charBits = "111100110100111"; // Hex: 79A7; Dec: 31143
			break;
		/*
			#   #
			#   #
			# # #
				#
				#
		*/
		case '4':
			charBits = "101101111100100"; // Hex: 5BE4; Dec: 23524
			break;
		/*
			# # #
			#    
			# # 
				#
			# # 
		*/
		case '5':
			charBits = "111001011100011"; // Hex: 72E3; Dec: 29411
			break;
		/*
			#
			# 
			# # #
			#   #
			# # #
		*/			
		case '6':
			charBits = "001001111101111"; // Hex: 13EF; Dec: 5103
			break;
		/*
			# # #
			    #
			  # 
			  #    
			  # 
		*/
		case '7':
			charBits = "111100010010010"; // Hex: 7892; Dec: 30866
			break;
		/*
			# # #
			#   #
			# # # 
			#   #
			# # # 
		*/
		case '8':
			charBits = "111101111101111"; // Hex: 7BEF; Dec: 31727
			break;
		/*
			# # #
			#   #
			# # #
				#
				#
		*/
		case '9':
			charBits = "111101111100100"; // Hex: 7BE4; Dec: 31716
			break;


		  /////////////////////////////////////////
		 //		--- UPPERCASE LETTERS ---		//
		/////////////////////////////////////////	
		/*
			  #
			#   #
			# # #
			#   #
			#   #
		*/
		case 'A':
			charBits = "010101111101101"; // Hex: 2BED; Dec: 11245
			break;
		/*
			# #
			#   #
			# # 
			#   #
			# # 
		*/
		case 'B':
			charBits = "011101011101011"; // Hex: 3AEB; Dec: 15083
			break;
		/*
			  # #
			#   
			#  
			#   
			  # #
		*/
		case 'C':
			charBits = "110001001001110"; // Hex: 624E; Dec: 25166
			break;
		/*
			# # 
			#   #
			#   #
			#   #
			# #
		*/
		case 'D':
			charBits = "011101101101011"; // Hex: 3B6B; Dec: 15211
			break;
		/*
			# # #
			#   
			# # #
			#   
			# # #
		*/
		case 'E':
			charBits = "111001111001111"; // Hex: 73CF; Dec: 29647
			break;
		/*
			# # #
			#   
			# # #
			#   
			#
		*/
		case 'F':
			charBits = "111001111001001"; // Hex: 73C9; Dec: 29641
			break;
		/*
			  # #
			#   
			#   #
			#   #
			  # #
		*/
		case 'G':
			charBits = "110001101101110"; // Hex: 636E; Dec: 25454
			break;
		/*
			#   #
			#   #
			# # #
			#   #
			#   #
		*/
		case 'H':
			charBits = "101101111101101"; // Hex: 5BED; Dec: 23533
			break;
		/*
			# # #
			  #  
			  #
			  #   
			# # #
		*/
		case 'I':
			charBits = "111010010010111"; // Hex: 7497; Dec: 29847
			break;
		/*
			  # #
				#
				#
			#   #
			  # 
		*/
		case 'J':
			charBits = "110100100101010"; // Hex: 692A; Dec: 26922
			break;
		/*
			#   #
			#   #
			# # 
			#   #
			#   #
		*/
		case 'K':
			charBits = "101101011101101"; // Hex: 5AED; Dec: 23277
			break;
		/*
			# 
			#   
			# 
			#   
			# # #
		*/
		case 'L':
			charBits = "001001001001111"; // Hex: 124F; Dec: 4687
			break;
		/*
			#   #
			# # #
			# # #
			#   #
			#   #
		*/
		case 'M':
			charBits = "101111111101101"; // Hex: 5FED; Dec: 24557
			break;
		/*
			#   #
			# # #
			# # # 
			# # #
			#   #
		*/
		case 'N':
			charBits = "101111111111101"; // Hex: 5FFD; Dec: 24573
			break;
		/*
			  # 
			#   #
			#   #
			#   #
			  # 
		*/
		case 'O':
			charBits = "010101101101010"; // Hex: 2B6A; Dec: 11114
			break;
		/*
			# # #
			#   #
			# # #
			#   
			#
		*/
		case 'P':
			charBits = "111101111001001"; // Hex: 7BC9; Dec: 31689
			break;
		/*
			  # 
			#   #
			#   #
			# # #
			  # #
		*/
		case 'Q':
			charBits = "010101101111110"; // Hex: 2B7E; Dec: 11134
			break;
		/*
			# # 
			#   #
			# #
			#   #
			#   #
		*/
		case 'R':
			charBits = "011101011101101"; // Hex: 3AED; Dec: 15085
			break;
		/*
			  # #
			#   
			  # 
				#
			# # 
		*/
		case 'S':
			charBits = "110001010100011"; // Hex: 62A3; Dec: 25251
			break;
		/*
			# # #
			  #
			  #
			  #   
			  #
		*/
		case 'T':
			charBits = "111010101010010"; // Hex: 7552; Dec: 30034
			break;
		/*
			#   #
			#   #
			#   #
			#   #
			# # #
		*/
		case 'U':
			charBits = "101101101101111"; // Hex: 5B6F; Dec: 23407
			break;
		/*
			#   #
			#   #
			#   #
			#   #
			  #  
		*/
		case 'V':
			charBits = "101101101101010"; // Hex: 5B6A; Dec: 23402
			break;
		/*
			#   #
			#   #
			# # #
			# # #
			#   #
		*/
		case 'W':
			charBits = "101101111111101"; // Hex: 5BFD; Dec: 23549
			break;
		/*
			#   #
			#   #  
			  # 
			#   #
			#   #
		*/
		case 'X':
			charBits = "101101010101101"; // Hex: 5AAD; Dec: 23213
			break;
		/*
			#   #
			#   #
			  # 
			  #   
			  # 
		*/
		case 'Y':
			charBits = "101101010010010"; // Hex: 5A92; Dec: 23186
			break;
		/*
			# # #
				#
			  # 
			#   
			# # #
		*/
		case 'Z':
			charBits = "111100010001111"; // Hex: 788F; Dec: 30863
			break;


		  /////////////////////////////////////////
		 //		--- LOWERCASE LETTERS ---		//
		/////////////////////////////////////////
		/*
				
			  # #
			#   #
			#   #
			  # #
		*/
		case 'a':
			charBits = "000110101101110"; // Hex: D6E; Dec: 3438
			break;
		/*
			#  
			#  
			# # 
			#   #
			# # 
		*/
		case 'b':
			charBits = "001001011101011"; // Hex: 12EB; Dec: 4843
			break;
		/*
			
			  # #
			#  
			#  
			  # #
		*/
		case 'c':
			charBits = "000110001001110"; // Hex: C4E; Dec: 3150
			break;
		/*
				#
				#
			  # #
			#   #
			  # #
		*/
		case 'd':
			charBits = "100100110101110"; // Hex: 49AE; Dec: 18862
			break;
		/*
			  # 
			#   #
			# # #
			#   
			  # #
		*/
		case 'e':
			charBits = "010101111001110"; // Hex: 2BCE; Dec: 11214
			break;
		/*
			  # #
			  #  
			# # #
			  #  
			  # 
		*/
		case 'f':
			charBits = "110010111010010"; // Hex: 65D2; Dec: 26066
			break;
		/*
			  # #
			#   #
			  # #   
				#
			# # 
		*/
		case 'g':
			charBits = "110101110100011"; // Hex: 6BA3; Dec: 27555
			break;
		/*
			#  
			#  
			# #
			#   #
			#   #
		*/
		case 'h':
			charBits = "001001011101101"; // Hex: 12ED; Dec: 4845
			break;
		/*
			  # 
				
			  # 
			  # 
			  # 
		*/
		case 'i':
			charBits = "010000010010010"; // Hex: 2092; Dec: 8338
			break;
		/*
				#
			
				#
			#   #
			  # 
		*/
		case 'j':
			charBits = "100000100101010"; // Hex: 412A; Dec: 16682
			break;
		/*
			#   
			#   #
			# # 
			# #  
			#   #
		*/
		case 'k':
			charBits = "001101011011101"; // Hex: 1ADD; Dec: 6877
			break;
		/*
			  # 
			  # 
			  #  
			  #  
			  #  
		*/
		case 'l':
			charBits = "010010010010010"; // Hex: 2492; Dec: 9362
			break;
		/*
			
			# 
			# # #
			# # #
			#   #
		*/
		case 'm':
			charBits = "000001111111101"; // Hex: 3FD; Dec: 1021
			break;
		/*
				
			#  
			# # 
			#   #
			#   #
		*/
		case 'n':
			charBits = "000001011101101"; // Hex: 2ED; Dec: 749
			break;
		/*
				
			  # 
			#   #
			#   #
			  # 
		*/
		case 'o':
			charBits = "000010101101010"; // Hex: 56A; Dec: 1386
			break;
		/*
			# # 
			#  #
			# # 
			# 
			# 
		*/
		case 'p':
			charBits = "011101011001001"; // Hex: 3AC9; Dec: 15049
			break;
		/*
			  # #
			#   #
			  # #
				# 
				#
		*/
		case 'q':
			charBits = "110101110100100"; // Hex: 6BA4; Dec: 27556
			break;
		/*
			 
			#  
			# # #
			#   #  
			#  
		*/
		case 'r':
			charBits = "000001111101001"; // Hex: 3E9; Dec: 1001
			break;
		/*
			  # #
			#  
			  # 
				#
			# # 
		*/
		case 's':
			charBits = "110001010100011"; // Hex: 62A3; Dec: 25251
			break;
		/*
			
			  #  
			# # #
			  #  
			  # 
		*/
		case 't':
			charBits = "000010111010010"; // Hex: 5D2; Dec: 1490
			break;
		/*
			
			#   #
			#   #
			#   #
			# # #
		*/
		case 'u':
			charBits = "000101101101111"; // Hex: B6F; Dec: 2927
			break;
		/*
			
			#   #
			#   #
			#   #
			  # 
		*/
		case 'v':
			charBits = "000101101101010"; // Hex: B6A; Dec: 2922
			break;
		/*
			
			#   #
			# # #
			# # #
			# # #  
		*/
		case 'w':
			charBits = "000101111111111"; // Hex: BFF; Dec: 3071
			break;
		/*
			
			   
			#   #
			  #  
			#   #
		*/
		case 'x':
			charBits = "000000101010101"; // Hex: 155; Dec: 341
			break;
		/*
			
			#   #
			# # #
				#
			# #
		*/
		case 'y':
			charBits = "000101111100011"; // Hex: BE3; Dec: 3043
			break;
		/*
			
			# # #
			  # 
			#  
			# # #
		*/
		case 'z':
			charBits = "000111010001111"; // Hex: E8F; Dec: 3727
			break;


		  /////////////////////////////
		 //		--- DEFAULT ---		//
		/////////////////////////////
		/*
			# # # 
			# # #
			# # # 
			# # # 
			# # #
		*/
		default:
			charBits = "111111111111111"; // Hex: 7FFF; Dec: 32767
			break;
	}

	return charBits;
}


void DrawChar(char character, int16_t startX, int16_t startY, Color pColor)
{
	std::bitset<15> charBits = GetChar(character, startX, startY);
	uint8_t rgb[3] = GetRGB(pColor);
	int16_t x = 0, y = 0;

	for(int ct = 0; ct < 15; ct++)
	{
		x = ct%3;
		y = (ct%3==0 && ct!=0)? y++: y;

		if(charBits[ct] == true)
		{
			leds[GetPixel(uint8_t x, uint8_t y)] = CRGB(rgb[0], rgb[1], rgb[2]);
		}
	}
}

/*
	// A
																	leds[GetPixel(1,4)] = CRGB(rColor,gColor,bColor);
	leds[GetPixel(0,3)] = CRGB(rColor,gColor,bColor);                                                                           	leds[GetPixel(2,3)] = CRGB(rColor,gColor,bColor);
	leds[GetPixel(0,2)] = CRGB(rColor,gColor,bColor);               leds[GetPixel(1,2)] = CRGB(rColor,gColor,bColor);           	leds[GetPixel(2,2)] = CRGB(rColor,gColor,bColor);
	leds[GetPixel(0,1)] = CRGB(rColor,gColor,bColor);                                                                           	leds[GetPixel(2,1)] = CRGB(rColor,gColor,bColor);
	leds[GetPixel(0,0)] = CRGB(rColor,gColor,bColor);                                                                           	leds[GetPixel(2,0)] = CRGB(rColor,gColor,bColor);

	// D 
	leds[GetPixel(4,4)] = CRGB(rColor,gColor,bColor);               leds[GetPixel(5,4)] = CRGB(rColor,gColor,bColor);           
	leds[GetPixel(4,3)] = CRGB(rColor,gColor,bColor);                                                                           	leds[GetPixel(6,3)] = CRGB(rColor,gColor,bColor);
	leds[GetPixel(4,2)] = CRGB(rColor,gColor,bColor);                                                                           	leds[GetPixel(6,2)] = CRGB(rColor,gColor,bColor);
	leds[GetPixel(4,1)] = CRGB(rColor,gColor,bColor);                                                                          	 	leds[GetPixel(6,1)] = CRGB(rColor,gColor,bColor);
	leds[GetPixel(4,0)] = CRGB(rColor,gColor,bColor);               leds[GetPixel(5,0)] = CRGB(rColor,gColor,bColor);           


	// E
	leds[GetPixel(8,4)] = CRGB(rColor,gColor,bColor);               leds[GetPixel(9,4)] = CRGB(rColor,gColor,bColor);           	leds[GetPixel(10,4)] = CRGB(rColor,gColor,bColor);
	leds[GetPixel(8,3)] = CRGB(rColor,gColor,bColor);                                      
	leds[GetPixel(8,2)] = CRGB(rColor,gColor,bColor);               leds[GetPixel(9,2)] = CRGB(rColor,gColor,bColor);           
	leds[GetPixel(8,1)] = CRGB(rColor,gColor,bColor);                                       
	leds[GetPixel(8,0)] = CRGB(rColor,gColor,bColor);               leds[GetPixel(9,0)] = CRGB(rColor,gColor,bColor);           	leds[GetPixel(10,0)] = CRGB(rColor,gColor,bColor);

	// L
	leds[GetPixel(12,4)] = CRGB(rColor,gColor,bColor);               
	leds[GetPixel(12,3)] = CRGB(rColor,gColor,bColor);               
	leds[GetPixel(12,2)] = CRGB(rColor,gColor,bColor);               
	leds[GetPixel(12,1)] = CRGB(rColor,gColor,bColor);               
	leds[GetPixel(12,0)] = CRGB(rColor,gColor,bColor);              leds[GetPixel(13,0)] = CRGB(rColor,gColor,bColor);         		 leds[GetPixel(14,0)] = CRGB(rColor,gColor,bColor);


	// A
																	leds[GetPixel(17,4)] = CRGB(rColor,gColor,bColor);
	leds[GetPixel(16,3)] = CRGB(rColor,gColor,bColor);                                                                          	leds[GetPixel(18,3)] = CRGB(rColor,gColor,bColor);
	leds[GetPixel(16,2)] = CRGB(rColor,gColor,bColor);              leds[GetPixel(17,2)] = CRGB(rColor,gColor,bColor);          	leds[GetPixel(18,2)] = CRGB(rColor,gColor,bColor);
	leds[GetPixel(16,1)] = CRGB(rColor,gColor,bColor);                                                                          	leds[GetPixel(18,1)] = CRGB(rColor,gColor,bColor);
	leds[GetPixel(16,0)] = CRGB(rColor,gColor,bColor);
*/