#include "constants.h"
#include "prototypes.h"


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


//This font is only 3 pixels wide and 5 pixels heigh
void MakeChar (char makeChar, int startX, int startY, Color pCol, Pixel[][] pixArr)
{
	//Validate row and column number. Wrap them around if they go over. WARNING: negative numbers are bad, and I'm too lazy to correct them!
	int rowZero = (startY+0)%(NUMOFROWS+1), rowOne = (startY+1)%(NUMOFROWS+1), rowTwo = (startY+2)%(NUMOFROWS+1), rowThree = (startY+3)%(NUMOFROWS+1), rowFour = (startY+4)%(NUMOFROWS+1);
	int colZero = (startX+0)%(NUMOFCOLUMNS+1), colOne = (startX+1)%(NUMOFCOLUMNS+1), colTwo = (startX+2)%(NUMOFCOLUMNS+1);

	//Get Pixel points for making characters from the maxtrix
	Pixel	pZeroFour  = pixArr[colZero][rowFour],		pOneFour  = pixArr[colOne][rowFour],		pTwoFour  = pixArr[colTwo][rowFour],
			pZeroThree = pixArr[colZero][rowThree], 	pOneThree = pixArr[colOne][rowThree],		pTwoThree = pixArr[colTwo][rowThree],
			pZeroTwo   = pixArr[colZero][rowTwo],		pOneTwo   = pixArr[colOne][rowTwo],			pTwoTwo   = pixArr[colTwo][rowTwo],
			pZeroOne   = pixArr[colZero][rowOne],		pOneOne   = pixArr[colOne][rowOne],			pTwoOne   = pixArr[colTwo][rowOne],
			pZeroZero  = pixArr[colZero][rowZero],		pOneZero  = pixArr[colOne][rowZero],		pTwoZero  = pixArr[colTwo][rowZero];

	//Change the pixel colors
	pZeroFour.setColors(pCol);		pOneFour.setColors(pCol);		pTwoFour.setColors(pCol);
	pZeroThree.setColors(pCol);		pOneThree.setColors(pCol);		pTwoThree.setColors(pCol);
	pZeroTwo.setColors(pCol);		pOneTwo.setColors(pCol);		pTwoTwo.setColors(pCol);
	pZeroOne.setColors(pCol);		pOneOne.setColors(pCol);		pTwoOne.setColors(pCol);
	pZeroZero.setColors(pCol);		pOneZero.setColors(pCol);		pTwoZero.setColors(pCol);

	switch(makeChar)
	{
		//SYMBOLS, OPERATORS, PUNCTUATION
		/*





		*/
		case ' ':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.off();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.off();		pOneTwo.off();		pTwoTwo.off();
			pZeroOne.off();		pOneOne.off();		pTwoOne.off();
			pZeroZero.off();	pOneZero.off();		pTwoZero.off();
			break;
		/*
			  # 
			  # 
			  # 
			
			  # 
		*/
		case '!':
			pZeroFour.off();	pOneFour.on();		pTwoFour.off();
			pZeroThree.off();	pOneThree.on();		pTwoThree.off();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.off();		pOneOne.off();		pTwoOne.off();
			pZeroZero.off();	pOneZero.on();		pTwoZero.off();
			break;
		/*
			  # 
			# # #
			  # 
			# # #
			  # 
		*/
		case '$':
			pZeroFour.off();	pOneFour.on();		pTwoFour.off();
			pZeroThree.on();	pOneThree.on();		pTwoThree.on();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.on();		pTwoOne.on();
			pZeroZero.off();	pOneZero.on();		pTwoZero.off();
			break;
		/*
			#   #
				#    
			  #   
			#	  
			#   #   
		*/
		case '%':
			pZeroFour.on();		pOneFour.off();		pTwoFour.on();
			pZeroThree.off();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.off();		pTwoOne.off();
			pZeroZero.on();		pOneZero.off();		pTwoZero.on();
			break;
		/*
				
			  #  
			# # #
			  #  
				
		*/
		case '+':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.off();	pOneThree.on();		pTwoThree.off();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.off();		pOneOne.on();		pTwoOne.off();
			pZeroZero.off();	pOneZero.off();		pTwoZero.off();
			break;
		/*
			
				
			# # #
			
			
		*/
		case '-':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.off();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.off();		pOneOne.off();		pTwoOne.off();
			pZeroZero.off();	pOneZero.off();		pTwoZero.off();
			break;
		/*
			
			#   #
			  # 
			#   #
			
		*/
		case '*':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.off();	pOneZero.off();		pTwoZero.off();
			break;
		/*
			
			
			
			
			# 
		*/
		case '.':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.off();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.off();		pOneTwo.off();		pTwoTwo.off();
			pZeroOne.off();		pOneOne.off();		pTwoOne.off();
			pZeroZero.on();		pOneZero.off();		pTwoZero.off();
			break;
		/*
					
				#
			  # 
			#  
			
		*/
		case '/':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.off();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.off();		pTwoOne.off();
			pZeroZero.off();	pOneZero.off();		pTwoZero.off();
			break;
		/*
			
			  # 
			
			  #
			
		*/
		case ':':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.off();	pOneThree.on();		pTwoThree.off();
			pZeroTwo.off();		pOneTwo.off();		pTwoTwo.off();
			pZeroOne.off();		pOneOne.on();		pTwoOne.off();
			pZeroZero.off();	pOneZero.off();		pTwoZero.off();
			break;
		/*
				#
			  # 
			# 
			  # 
				#
		*/
		case '<':
			pZeroFour.off();	pOneFour.off();		pTwoFour.on();
			pZeroThree.off();	pOneThree.on();		pTwoThree.off();
			pZeroTwo.on();		pOneTwo.off();		pTwoTwo.off();
			pZeroOne.off();		pOneOne.on();		pTwoOne.off();
			pZeroZero.off();	pOneZero.off();		pTwoZero.on();
			break;
		/*
			
			# # #
			
			# # #
			
		*/
		case '=':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.on();	pOneThree.on();		pTwoThree.on();
			pZeroTwo.off();		pOneTwo.off();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.on();		pTwoOne.on();
			pZeroZero.off();	pOneZero.off();		pTwoZero.off();
			break;
		/*
			# 
			  # 
				#
			  # 
			# 
		*/
		case '>':
			pZeroFour.on();		pOneFour.off();		pTwoFour.off();
			pZeroThree.off();	pOneThree.on();		pTwoThree.off();
			pZeroTwo.off();		pOneTwo.off();		pTwoTwo.on();
			pZeroOne.off();		pOneOne.on();		pTwoOne.off();
			pZeroZero.on();		pOneZero.off();		pTwoZero.off();
			break;
		/*
			  # # 
				#
			  # 
				
			  # 
		*/
		case '?':
			pZeroFour.off();	pOneFour.on();		pTwoFour.on();
			pZeroThree.off();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.off();		pOneOne.off();		pTwoOne.off();
			pZeroZero.off();	pOneZero.on();		pTwoZero.off();
			break;


		//NUMBERS
		/*
			  # 
			#   #
			#   #
			#   #
			  #  
		*/
		case '0':
			pZeroFour.off();	pOneFour.on();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.off();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.off();	pOneZero.on();		pTwoZero.off();
			break;
		/*
			  # 
			# # 
			  # 
			  # 
			# # #
		*/
		case '1':
			pZeroFour.off();	pOneFour.on();		pTwoFour.off();
			pZeroThree.on();	pOneThree.on();	pTwoThree.off();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.off();		pOneOne.on();		pTwoOne.off();
			pZeroZero.on();		pOneZero.on();		pTwoZero.on();
			break;
		/*
			  # 
			#   #
			  # 
			#   
			# # #
		*/
		case '2':
			pZeroFour.off();	pOneFour.on();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.off();		pTwoOne.off();
			pZeroZero.on();		pOneZero.on();		pTwoZero.on();
			break;
		/*
			# # #
				#
			  # #
				#
			# # #
		*/
		case '3':
			pZeroFour.on();		pOneFour.on();		pTwoFour.on();
			pZeroThree.off();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.off();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.on();		pTwoZero.on();
			break;
		/*
			#   #
			#   #
			# # #
				#
				#
		*/
		case '4':
			pZeroFour.on();		pOneFour.off();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.off();		pOneOne.off();		pTwoOne.on();
			pZeroZero.off();	pOneZero.off();		pTwoZero.on();
			break;
		/*
			# # #
			#    
			# # 
				#
			# # 
		*/
		case '5':
			pZeroFour.on();		pOneFour.on();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.off();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.on();		pTwoZero.off();
			break;
		/*
			#
			# 
			# # #
			#   #
			# # #
		*/			
		case '6':
			pZeroFour.on();		pOneFour.off();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.on();		pTwoZero.on();
			break;
		/*
			# # #
			    #
			  # 
			  #    
			  # 
		*/
		case '7':
			pZeroFour.on();		pOneFour.on();		pTwoFour.on();
			pZeroThree.off();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.off();		pOneOne.on();		pTwoOne.off();
			pZeroZero.off();	pOneZero.on();		pTwoZero.off();
			break;
		/*
			# # #
			#   #
			# # # 
			#   #
			# # # 
		*/
		case '8':
			pZeroFour.on();		pOneFour.on();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.on();		pTwoZero.on();
			break;
		/*
			# # #
			#   #
			# # #
				#
				#
		*/
		case '9':
			pZeroFour.on();		pOneFour.on();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.off();		pOneOne.off();		pTwoOne.on();
			pZeroZero.off();	pOneZero.off();		pTwoZero.on();
			break;


		//UPPERCASE LETTERS
		/*
			  #
			#   #
			# # #
			#   #
			#   #
		*/
		case 'A':
			pZeroFour.off();	pOneFour.on();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.off();		pTwoZero.on();
			break;
		/*
			# #
			#   #
			# # 
			#   #
			# # 
		*/
		case 'B':
			pZeroFour.on();		pOneFour.on();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.on();		pTwoZero.off();
			break;
		/*
			  # #
			#   
			#  
			#   
			  # #
		*/
		case 'C':
			pZeroFour.off();	pOneFour.on();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.on();		pOneTwo.off();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.off();		pTwoOne.off();
			pZeroZero.off();	pOneZero.on();		pTwoZero.on();
			break;
		/*
			# # 
			#   #
			#   #
			#   #
			# #
		*/
		case 'D':
			pZeroFour.on();		pOneFour.on();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.off();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.on();		pTwoZero.off();
			break;
		/*
			# # #
			#   
			# # #
			#   
			# # #
		*/
		case 'E':
			pZeroFour.on();		pOneFour.on();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.off();
			pZeroZero.on();		pOneZero.on();		pTwoZero.on();
			break;
		/*
			# # #
			#   
			# # #
			#   
			#
		*/
		case 'F':
			pZeroFour.on();		pOneFour.on();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.off();
			pZeroZero.on();		pOneZero.off();		pTwoZero.off();
			break;
		/*
			  # #
			#   
			#   #
			#   #
			  # #
		*/
		case 'G':
			pZeroFour.off();	pOneFour.on();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.on();		pOneTwo.off();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.off();	pOneZero.on();		pTwoZero.on();
			break;
		/*
			#   #
			#   #
			# # #
			#   #
			#   #
		*/
		case 'H':
			pZeroFour.on();		pOneFour.off();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.off();		pTwoZero.on();
			break;
		/*
			# # #
			  #  
			  #
			  #   
			# # #
		*/
		case 'I':
			pZeroFour.on();		pOneFour.on();		pTwoFour.on();
			pZeroThree.off();	pOneThree.on();	pTwoThree.off();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.off();		pOneOne.on();		pTwoOne.off();
			pZeroZero.on();		pOneZero.on();		pTwoZero.on();
			break;
		/*
			  # #
				#
				#
			#   #
			  # 
		*/
		case 'J':
			pZeroFour.off();	pOneFour.on();		pTwoFour.on();
			pZeroThree.off();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.off();		pOneTwo.off();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.off();	pOneZero.on();		pTwoZero.off();
			break;
		/*
			#   #
			#   #
			# # 
			#   #
			#   #
		*/
		case 'K':
			pZeroFour.on();		pOneFour.off();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.off();		pTwoZero.on();
			break;
		/*
			# 
			#   
			# 
			#   
			# # #
		*/
		case 'L':
			pZeroFour.on();		pOneFour.off();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.on();		pOneTwo.off();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.off();		pTwoOne.off();
			pZeroZero.on();		pOneZero.on();		pTwoZero.on();
			break;
		/*
			#   #
			# # #
			# # #
			#   #
			#   #
		*/
		case 'M':
			pZeroFour.on();		pOneFour.off();		pTwoFour.on();
			pZeroThree.on();	pOneThree.on();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.off();		pTwoZero.on();
			break;
		/*
			#   #
			# # #
			# # # 
			# # #
			#   #
		*/
		case 'N':
			pZeroFour.on();		pOneFour.off();		pTwoFour.on();
			pZeroThree.on();	pOneThree.on();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.on();		pTwoOne.on();
			pZeroZero.on();		pOneZero.off();		pTwoZero.on();
			break;
		/*
			  # 
			#   #
			#   #
			#   #
			  # 
		*/
		case 'O':
			pZeroFour.off();	pOneFour.on();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.off();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.off();	pOneZero.on();		pTwoZero.off();
			break;
		/*
			# # #
			#   #
			# # #
			#   
			#
		*/
		case 'P':
			pZeroFour.on();		pOneFour.on();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.off();
			pZeroZero.on();		pOneZero.off();		pTwoZero.off();
			break;
		/*
			  # 
			#   #
			#   #
			# # #
			  # #
		*/
		case 'Q':
			pZeroFour.off();	pOneFour.on();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.off();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.on();		pTwoOne.on();
			pZeroZero.off();	pOneZero.on();		pTwoZero.on();
			break;
		/*
			# # 
			#   #
			# #
			#   #
			#   #
		*/
		case 'R':
			pZeroFour.on();		pOneFour.on();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.off();		pTwoZero.on();
			break;
		/*
			  # #
			#   
			  # 
				#
			# # 
		*/
		case 'S':
			pZeroFour.off();	pOneFour.on();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.off();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.on();		pTwoZero.off();
			break;
		/*
			# # #
			  #
			  #
			  #   
			  #
		*/
		case 'T':
			pZeroFour.on();		pOneFour.on();		pTwoFour.on();
			pZeroThree.off();	pOneThree.on();	pTwoThree.off();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.off();		pOneOne.on();		pTwoOne.off();
			pZeroZero.off();	pOneZero.on();		pTwoZero.off();
			break;
		/*
			#   #
			#   #
			#   #
			#   #
			# # #
		*/
		case 'U':
			pZeroFour.on();		pOneFour.off();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.off();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.on();		pTwoZero.on();
			break;
		/*
			#   #
			#   #
			#   #
			#   #
			  #  
		*/
		case 'V':
			pZeroFour.on();		pOneFour.off();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.off();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.off();	pOneZero.on();		pTwoZero.off();
			break;
		/*
			#   #
			#   #
			# # #
			# # #
			#   #
		*/
		case 'W':
			pZeroFour.on();		pOneFour.off();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.on();		pTwoOne.on();
			pZeroZero.on();		pOneZero.off();		pTwoZero.on();
			break;
		/*
			#   #
			#   #  
			  # 
			#   #
			#   #
		*/
		case 'X':
			pZeroFour.on();		pOneFour.off();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.off();		pTwoZero.on();
			break;
		/*
			#   #
			#   #
			  # 
			  #   
			  # 
		*/
		case 'Y':
			pZeroFour.on();		pOneFour.off();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.off();		pOneOne.on();		pTwoOne.off();
			pZeroZero.off();	pOneZero.on();		pTwoZero.off();
			break;
		/*
			# # #
				#
			  # 
			#   
			# # #
		*/
		case 'Z':
			pZeroFour.on();		pOneFour.on();		pTwoFour.on();
			pZeroThree.off();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.off();		pTwoOne.off();
			pZeroZero.on();		pOneZero.on();		pTwoZero.on();
			break;


		//LOWERCASE LETTERS
		/*
				
			  # #
			#   #
			#   #
			  # #
		*/
		case 'a':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.off();	pOneThree.on();		pTwoThree.on();
			pZeroTwo.on();		pOneTwo.off();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.off();	pOneZero.on();		pTwoZero.on();
			break;
		/*
			#  
			#  
			# # 
			#   #
			# # 
		*/
		case 'b':
			pZeroFour.on();		pOneFour.off();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.on();		pTwoZero.off();
			break;
		/*
			
			  # #
			#  
			#  
			  # #
		*/
		case 'c':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.off();	pOneThree.on();		pTwoThree.on();
			pZeroTwo.on();		pOneTwo.off();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.off();		pTwoOne.off();
			pZeroZero.off();	pOneZero.on();		pTwoZero.on();
			break;
		/*
				#
				#
			  # #
			#   #
			  # #
		*/
		case 'd':
			pZeroFour.off();	pOneFour.off();		pTwoFour.on();
			pZeroThree.off();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.off();	pOneZero.on();		pTwoZero.on();
			break;
		/*
			  # 
			#   #
			# # #
			#   
			  # #
		*/
		case 'e':
			pZeroFour.off();	pOneFour.on();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.off();
			pZeroZero.off();	pOneZero.on();		pTwoZero.on();
			break;
		/*
			  # #
			  #  
			# # #
			  #  
			  # 
		*/
		case 'f':
			pZeroFour.off();	pOneFour.on();		pTwoFour.on();
			pZeroThree.off();	pOneThree.on();		pTwoThree.off();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.off();		pOneOne.on();		pTwoOne.off();
			pZeroZero.off();	pOneZero.on();		pTwoZero.off();
			break;
		/*
			  # #
			#   #
			  # #   
				#
			# # 
		*/
		case 'g':
			pZeroFour.off();	pOneFour.on();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.off();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();	pOneZero.on();		pTwoZero.off();
			break;
		/*
			#  
			#  
			# #
			#   #
			#   #
		*/
		case 'h':
			pZeroFour.on();		pOneFour.off();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.off();		pTwoZero.on();
			break;
		/*
			  # 
				
			  # 
			  # 
			  # 
		*/
		case 'i':
			pZeroFour.off();	pOneFour.on();		pTwoFour.off();
			pZeroThree.off();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.off();		pOneOne.on();		pTwoOne.off();
			pZeroZero.off();	pOneZero.on();		pTwoZero.off();
			break;
		/*
				#
			
				#
			#   #
			  # 
		*/
		case 'j':
			pZeroFour.off();	pOneFour.off();		pTwoFour.on();
			pZeroThree.off();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.off();		pOneTwo.off();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.off();	pOneZero.on();		pTwoZero.off();
			break;
		/*
			#   
			#   #
			# # 
			# #  
			#   #
		*/
		case 'k':
			pZeroFour.on();		pOneFour.off();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.on();		pTwoOne.off();
			pZeroZero.on();		pOneZero.off();		pTwoZero.on();
			break;
		/*
			  # 
			  # 
			  #  
			  #  
			  #  
		*/
		case 'l':
			pZeroFour.off();	pOneFour.on();		pTwoFour.off();
			pZeroThree.off();	pOneThree.on();		pTwoThree.off();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.off();		pOneOne.on();		pTwoOne.off();
			pZeroZero.off();	pOneZero.on();		pTwoZero.off();
			break;
		/*
			
			# 
			# # #
			# # #
			#   #
		*/
		case 'm':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.on();		pTwoOne.on();
			pZeroZero.on();		pOneZero.off();		pTwoZero.on();
			break;
		/*
				
			#  
			# # 
			#   #
			#   #
		*/
		case 'n':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.off();		pTwoZero.on();
			break;
		/*
				
			  # 
			#   #
			#   #
			  # 
		*/
		case 'o':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.off();	pOneThree.on();		pTwoThree.off();
			pZeroTwo.on();		pOneTwo.off();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.off();	pOneZero.on();		pTwoZero.off();
			break;
		/*
			# # 
			#  #
			# # 
			# 
			# 
		*/
		case 'p':
			pZeroFour.on();		pOneFour.on();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.off();		pTwoOne.off();
			pZeroZero.on();		pOneZero.off();		pTwoZero.off();
			break;
		/*
			  # #
			#   #
			  # #
				# 
				#
		*/
		case 'q':
			pZeroFour.off();	pOneFour.on();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.off();		pOneOne.off();		pTwoOne.on();
			pZeroZero.off();	pOneZero.off();		pTwoZero.on();
			break;
		/*
			 
			#  
			# # #
			#   #  
			#  
		*/
		case 'r':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.off();		pTwoZero.off();
			break;
		/*
			  # #
			#  
			  # 
				#
			# # 
		*/
		case 's':
			pZeroFour.off();	pOneFour.on();		pTwoFour.on();
			pZeroThree.on();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.off();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.on();		pTwoZero.off();
			break;
		/*
			
			  #  
			# # #
			  #  
			  # 
		*/
		case 't':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.off();	pOneThree.on();		pTwoThree.off();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.off();		pOneOne.on();		pTwoOne.off();
			pZeroZero.off();	pOneZero.on();		pTwoZero.off();
			break;
		/*
			
			#   #
			#   #
			#   #
			# # #
		*/
		case 'u':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.off();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.on();		pTwoZero.on();
			break;
		/*
			
			#   #
			#   #
			#   #
			  # 
		*/
		case 'v':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.off();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.off();		pTwoOne.on();
			pZeroZero.off();	pOneZero.on();		pTwoZero.off();
			break;
		/*
			
			#   #
			# # #
			# # #
			# # #  
		*/
		case 'w':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.on();		pTwoOne.on();
			pZeroZero.on();		pOneZero.on();		pTwoZero.on();
			break;
		/*
			
			   
			#   #
			  #  
			#   #
		*/
		case 'x':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.off();	pOneThree.off();	pTwoThree.off();
			pZeroTwo.on();		pOneTwo.off();		pTwoTwo.on();
			pZeroOne.off();		pOneOne.on();		pTwoOne.off();
			pZeroZero.on();		pOneZero.off();		pTwoZero.on();
			break;
		/*
			
			#   #
			# # #
				#
			# #
		*/
		case 'y':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.on();	pOneThree.off();	pTwoThree.on();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.off();		pOneOne.off();		pTwoOne.on();
			pZeroZero.on();		pOneZero.on();		pTwoZero.off();
			break;
		/*
			
			# # #
			  # 
			#  
			# # #
		*/
		case 'z':
			pZeroFour.off();	pOneFour.off();		pTwoFour.off();
			pZeroThree.on();	pOneThree.on();		pTwoThree.on();
			pZeroTwo.off();		pOneTwo.on();		pTwoTwo.off();
			pZeroOne.on();		pOneOne.off();		pTwoOne.off();
			pZeroZero.on();		pOneZero.on();		pTwoZero.on();
			break;
		/*
			# # # 
			# # #
			# # # 
			# # # 
			# # #
		*/
		default:
			pZeroFour.on();		pOneFour.on();		pTwoFour.on();
			pZeroThree.on();	pOneThree.on();		pTwoThree.on();
			pZeroTwo.on();		pOneTwo.on();		pTwoTwo.on();
			pZeroOne.on();		pOneOne.on();		pTwoOne.on();
			pZeroZero.on();		pOneZero.on();		pTwoZero.on();
	}
}