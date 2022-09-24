//Author: Paul Kummer
//Date: 3/17/2022
//License: Open Source
//File: Font3x5.h


  /////////////////////////////////
 //		--- Information ---		//
/////////////////////////////////
/*
	This font is only 3 pixels wide and 5 pixels high
*/


  /////////////////////////////////
 //		--- Includes ---		//
/////////////////////////////////
//#include <map>
#include <bitset>


  /////////////////////////////////
 //		--- Constants ---		//
/////////////////////////////////
const int CHAR_WIDTH = 3;
const int CHAR_HEIGHT = 5;


  /////////////////////////////////
 //		--- Functions ---		//
/////////////////////////////////
// 
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

							charBits = std::bitset<15>(std::string("CBAFEDIHGLKJONM"));
	*/

	std::bitset<15> charBits;
	//std::map<char, binary>

	switch(makeChar)
	{
		  /////////////////////////////////////////////////////
		 //		--- SYMBOLS, OPERATORS, PUNCTUATION ---		//
		/////////////////////////////////////////////////////
		/*





		*/
		case ' ':
			charBits = std::bitset<15>(std::string("000000000000000")); // Hex: 0; Dec: 0
			break;
		/*
			  # 
			  # 
			  # 
			
			  # 
		*/
		case '!':
			charBits = std::bitset<15>(std::string("010010010000010"); // Hex: 2482; Dec: 9346
			break;
		/*
			  # 
			# # #
			  # 
			# # #
			  # 
		*/
		case '$':
			charBits = std::bitset<15>(std::string("010111010111010"); // Hex: 2EBA; Dec: 11962
			break;
		/*
			#   #
				#    
			  #   
			#	  
			#   #   
		*/
		case '%':
			charBits = std::bitset<15>(std::string("101100010001101"); // Hex: 588D; Dec: 22669
			break;
		/*
				
			  #  
			# # #
			  #  
				
		*/
		case '+':
			charBits = std::bitset<15>(std::string("000010111010000"); // Hex: 5D0; Dec: 1488
			break;
		/*
			
				
			# # #
			
			
		*/
		case '-':
			charBits = std::bitset<15>(std::string("000000111000000"); // Hex: 1C0; Dec: 448
			break;
		/*
			
			#   #
			  # 
			#   #
			
		*/
		case '*':
			charBits = std::bitset<15>(std::string("000101010101000"); // Hex: AA8; Dec: 2728
			break;
		/*
			
			
			
			
			# 
		*/
		case '.':
			charBits = std::bitset<15>(std::string("00000000000001"); // Hex: 1; Dec: 1
			break;
		/*
					
				#
			  # 
			#  
			
		*/
		case '/':
			charBits = std::bitset<15>(std::string("000100010001000"); // Hex: 888; Dec: 2184
			break;
		/*
			
			  # 
			
			  #
			
		*/
		case ':':
			charBits = std::bitset<15>(std::string("000010000010000"); // Hex: 410; Dec: 1040
			break;
		/*
				#
			  # 
			# 
			  # 
				#
		*/
		case '<':
			charBits = std::bitset<15>(std::string("100010001010100"); // Hex: 4454; Dec: 17492
			break;
		/*
			
			# # #
			
			# # #
			
		*/
		case '=':
			charBits = std::bitset<15>(std::string("000111000111000"); // Hex: E38; Dec: 3640
			break;
		/*
			# 
			  # 
				#
			  # 
			# 
		*/
		case '>':
			charBits = std::bitset<15>(std::string("001010100010001"); // Hex: 1511; Dec: 5393
			break;
		/*
			  # # 
				#
			  # 
				
			  # 
		*/
		case '?':
			charBits = std::bitset<15>(std::string("110100010000010"); // Hex: 6882; Dec: 26754
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
			charBits = std::bitset<15>(std::string("111101101101111"); // Hex: 7B6F; Dec: 31599
			break;
		/*
			  # 
			# # 
			  # 
			  # 
			# # #
		*/
		case '1':
			charBits = std::bitset<15>(std::string("010011010010111"); // Hex: 2697; Dec: 9879
			break;
		/*
			  # 
			#   #
			  # 
			#   
			# # #
		*/
		case '2':
			charBits = std::bitset<15>(std::string("010101010001111"); // Hex: 2A8F; Dec: 10895
			break;
		/*
			# # #
				#
			  # #
				#
			# # #
		*/
		case '3':
			charBits = std::bitset<15>(std::string("111100110100111"); // Hex: 79A7; Dec: 31143
			break;
		/*
			#   #
			#   #
			# # #
				#
				#
		*/
		case '4':
			charBits = std::bitset<15>(std::string("101101111100100"); // Hex: 5BE4; Dec: 23524
			break;
		/*
			# # #
			#    
			# # 
				#
			# # 
		*/
		case '5':
			charBits = std::bitset<15>(std::string("111001011100011"); // Hex: 72E3; Dec: 29411
			break;
		/*
			#
			# 
			# # #
			#   #
			# # #
		*/			
		case '6':
			charBits = std::bitset<15>(std::string("001001111101111"); // Hex: 13EF; Dec: 5103
			break;
		/*
			# # #
			    #
			  # 
			  #    
			  # 
		*/
		case '7':
			charBits = std::bitset<15>(std::string("111100010010010"); // Hex: 7892; Dec: 30866
			break;
		/*
			# # #
			#   #
			# # # 
			#   #
			# # # 
		*/
		case '8':
			charBits = std::bitset<15>(std::string("111101111101111"); // Hex: 7BEF; Dec: 31727
			break;
		/*
			# # #
			#   #
			# # #
				#
				#
		*/
		case '9':
			charBits = std::bitset<15>(std::string("111101111100100"); // Hex: 7BE4; Dec: 31716
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
			charBits = std::bitset<15>(std::string("010101111101101"); // Hex: 2BED; Dec: 11245
			break;
		/*
			# #
			#   #
			# # 
			#   #
			# # 
		*/
		case 'B':
			charBits = std::bitset<15>(std::string("011101011101011"); // Hex: 3AEB; Dec: 15083
			break;
		/*
			  # #
			#   
			#  
			#   
			  # #
		*/
		case 'C':
			charBits = std::bitset<15>(std::string("110001001001110"); // Hex: 624E; Dec: 25166
			break;
		/*
			# # 
			#   #
			#   #
			#   #
			# #
		*/
		case 'D':
			charBits = std::bitset<15>(std::string("011101101101011"); // Hex: 3B6B; Dec: 15211
			break;
		/*
			# # #
			#   
			# # #
			#   
			# # #
		*/
		case 'E':
			charBits = std::bitset<15>(std::string("111001111001111"); // Hex: 73CF; Dec: 29647
			break;
		/*
			# # #
			#   
			# # #
			#   
			#
		*/
		case 'F':
			charBits = std::bitset<15>(std::string("111001111001001"); // Hex: 73C9; Dec: 29641
			break;
		/*
			  # #
			#   
			#   #
			#   #
			  # #
		*/
		case 'G':
			charBits = std::bitset<15>(std::string("110001101101110"); // Hex: 636E; Dec: 25454
			break;
		/*
			#   #
			#   #
			# # #
			#   #
			#   #
		*/
		case 'H':
			charBits = std::bitset<15>(std::string("101101111101101"); // Hex: 5BED; Dec: 23533
			break;
		/*
			# # #
			  #  
			  #
			  #   
			# # #
		*/
		case 'I':
			charBits = std::bitset<15>(std::string("111010010010111"); // Hex: 7497; Dec: 29847
			break;
		/*
			  # #
				#
				#
			#   #
			  # 
		*/
		case 'J':
			charBits = std::bitset<15>(std::string("110100100101010"); // Hex: 692A; Dec: 26922
			break;
		/*
			#   #
			#   #
			# # 
			#   #
			#   #
		*/
		case 'K':
			charBits = std::bitset<15>(std::string("101101011101101"); // Hex: 5AED; Dec: 23277
			break;
		/*
			# 
			#   
			# 
			#   
			# # #
		*/
		case 'L':
			charBits = std::bitset<15>(std::string("001001001001111"); // Hex: 124F; Dec: 4687
			break;
		/*
			#   #
			# # #
			# # #
			#   #
			#   #
		*/
		case 'M':
			charBits = std::bitset<15>(std::string("101111111101101"); // Hex: 5FED; Dec: 24557
			break;
		/*
			#   #
			# # #
			# # # 
			# # #
			#   #
		*/
		case 'N':
			charBits = std::bitset<15>(std::string("101111111111101"); // Hex: 5FFD; Dec: 24573
			break;
		/*
			  # 
			#   #
			#   #
			#   #
			  # 
		*/
		case 'O':
			charBits = std::bitset<15>(std::string("010101101101010"); // Hex: 2B6A; Dec: 11114
			break;
		/*
			# # #
			#   #
			# # #
			#   
			#
		*/
		case 'P':
			charBits = std::bitset<15>(std::string("111101111001001"); // Hex: 7BC9; Dec: 31689
			break;
		/*
			  # 
			#   #
			#   #
			# # #
			  # #
		*/
		case 'Q':
			charBits = std::bitset<15>(std::string("010101101111110"); // Hex: 2B7E; Dec: 11134
			break;
		/*
			# # 
			#   #
			# #
			#   #
			#   #
		*/
		case 'R':
			charBits = std::bitset<15>(std::string("011101011101101"); // Hex: 3AED; Dec: 15085
			break;
		/*
			  # #
			#   
			  # 
				#
			# # 
		*/
		case 'S':
			charBits = std::bitset<15>(std::string("110001010100011"); // Hex: 62A3; Dec: 25251
			break;
		/*
			# # #
			  #
			  #
			  #   
			  #
		*/
		case 'T':
			charBits = std::bitset<15>(std::string("111010101010010"); // Hex: 7552; Dec: 30034
			break;
		/*
			#   #
			#   #
			#   #
			#   #
			# # #
		*/
		case 'U':
			charBits = std::bitset<15>(std::string("101101101101111"); // Hex: 5B6F; Dec: 23407
			break;
		/*
			#   #
			#   #
			#   #
			#   #
			  #  
		*/
		case 'V':
			charBits = std::bitset<15>(std::string("101101101101010"); // Hex: 5B6A; Dec: 23402
			break;
		/*
			#   #
			#   #
			# # #
			# # #
			#   #
		*/
		case 'W':
			charBits = std::bitset<15>(std::string("101101111111101"); // Hex: 5BFD; Dec: 23549
			break;
		/*
			#   #
			#   #  
			  # 
			#   #
			#   #
		*/
		case 'X':
			charBits = std::bitset<15>(std::string("101101010101101"); // Hex: 5AAD; Dec: 23213
			break;
		/*
			#   #
			#   #
			  # 
			  #   
			  # 
		*/
		case 'Y':
			charBits = std::bitset<15>(std::string("101101010010010"); // Hex: 5A92; Dec: 23186
			break;
		/*
			# # #
				#
			  # 
			#   
			# # #
		*/
		case 'Z':
			charBits = std::bitset<15>(std::string("111100010001111"); // Hex: 788F; Dec: 30863
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
			charBits = std::bitset<15>(std::string("000110101101110"); // Hex: D6E; Dec: 3438
			break;
		/*
			#  
			#  
			# # 
			#   #
			# # 
		*/
		case 'b':
			charBits = std::bitset<15>(std::string("001001011101011"); // Hex: 12EB; Dec: 4843
			break;
		/*
			
			  # #
			#  
			#  
			  # #
		*/
		case 'c':
			charBits = std::bitset<15>(std::string("000110001001110"); // Hex: C4E; Dec: 3150
			break;
		/*
				#
				#
			  # #
			#   #
			  # #
		*/
		case 'd':
			charBits = std::bitset<15>(std::string("100100110101110"); // Hex: 49AE; Dec: 18862
			break;
		/*
			  # 
			#   #
			# # #
			#   
			  # #
		*/
		case 'e':
			charBits = std::bitset<15>(std::string("010101111001110"); // Hex: 2BCE; Dec: 11214
			break;
		/*
			  # #
			  #  
			# # #
			  #  
			  # 
		*/
		case 'f':
			charBits = std::bitset<15>(std::string("110010111010010"); // Hex: 65D2; Dec: 26066
			break;
		/*
			  # #
			#   #
			  # #   
				#
			# # 
		*/
		case 'g':
			charBits = std::bitset<15>(std::string("110101110100011"); // Hex: 6BA3; Dec: 27555
			break;
		/*
			#  
			#  
			# #
			#   #
			#   #
		*/
		case 'h':
			charBits = std::bitset<15>(std::string("001001011101101"); // Hex: 12ED; Dec: 4845
			break;
		/*
			  # 
				
			  # 
			  # 
			  # 
		*/
		case 'i':
			charBits = std::bitset<15>(std::string("010000010010010"); // Hex: 2092; Dec: 8338
			break;
		/*
				#
			
				#
			#   #
			  # 
		*/
		case 'j':
			charBits = std::bitset<15>(std::string("100000100101010"); // Hex: 412A; Dec: 16682
			break;
		/*
			#   
			#   #
			# # 
			# #  
			#   #
		*/
		case 'k':
			charBits = std::bitset<15>(std::string("001101011011101"); // Hex: 1ADD; Dec: 6877
			break;
		/*
			  # 
			  # 
			  #  
			  #  
			  #  
		*/
		case 'l':
			charBits = std::bitset<15>(std::string("010010010010010"); // Hex: 2492; Dec: 9362
			break;
		/*
			
			# 
			# # #
			# # #
			#   #
		*/
		case 'm':
			charBits = std::bitset<15>(std::string("000001111111101"); // Hex: 3FD; Dec: 1021
			break;
		/*
				
			#  
			# # 
			#   #
			#   #
		*/
		case 'n':
			charBits = std::bitset<15>(std::string("000001011101101"); // Hex: 2ED; Dec: 749
			break;
		/*
				
			  # 
			#   #
			#   #
			  # 
		*/
		case 'o':
			charBits = std::bitset<15>(std::string("000010101101010"); // Hex: 56A; Dec: 1386
			break;
		/*
			# # 
			#  #
			# # 
			# 
			# 
		*/
		case 'p':
			charBits = std::bitset<15>(std::string("011101011001001"); // Hex: 3AC9; Dec: 15049
			break;
		/*
			  # #
			#   #
			  # #
				# 
				#
		*/
		case 'q':
			charBits = std::bitset<15>(std::string("110101110100100"); // Hex: 6BA4; Dec: 27556
			break;
		/*
			 
			#  
			# # #
			#   #  
			#  
		*/
		case 'r':
			charBits = std::bitset<15>(std::string("000001111101001"); // Hex: 3E9; Dec: 1001
			break;
		/*
			  # #
			#  
			  # 
				#
			# # 
		*/
		case 's':
			charBits = std::bitset<15>(std::string("110001010100011"); // Hex: 62A3; Dec: 25251
			break;
		/*
			
			  #  
			# # #
			  #  
			  # 
		*/
		case 't':
			charBits = std::bitset<15>(std::string("000010111010010"); // Hex: 5D2; Dec: 1490
			break;
		/*
			
			#   #
			#   #
			#   #
			# # #
		*/
		case 'u':
			charBits = std::bitset<15>(std::string("000101101101111"); // Hex: B6F; Dec: 2927
			break;
		/*
			
			#   #
			#   #
			#   #
			  # 
		*/
		case 'v':
			charBits = std::bitset<15>(std::string("000101101101010"); // Hex: B6A; Dec: 2922
			break;
		/*
			
			#   #
			# # #
			# # #
			# # #  
		*/
		case 'w':
			charBits = std::bitset<15>(std::string("000101111111111"); // Hex: BFF; Dec: 3071
			break;
		/*
			
			   
			#   #
			  #  
			#   #
		*/
		case 'x':
			charBits = std::bitset<15>(std::string("000000101010101"); // Hex: 155; Dec: 341
			break;
		/*
			
			#   #
			# # #
				#
			# #
		*/
		case 'y':
			charBits = std::bitset<15>(std::string("000101111100011"); // Hex: BE3; Dec: 3043
			break;
		/*
			
			# # #
			  # 
			#  
			# # #
		*/
		case 'z':
			charBits = std::bitset<15>(std::string("000111010001111"); // Hex: E8F; Dec: 3727
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
			charBits = std::bitset<15>(std::string("111111111111111"); // Hex: 7FFF; Dec: 32767
			break;
	}

	return charBits;
}





