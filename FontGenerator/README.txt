Author: Paul Kummer
File: FontGenerator.cpp

	[ Description ]
This C++ file, once compiled, will create an executable that will read a template font text 
document and create a header file that can be used with the "WriteText.INO" file so that the
newly created font can be used for displaying text on an LED matrix.

	[ How to Use ]
1. Modify the FontTemplate.txt file to design each character in there. Additional characters 
   can be added if desired. The template must follow the critera for the program to work:
	a) For each new character, the first line must be the character being created
	b) Immediately after the character being designed there will be a textual matrix
	   that represents the LED matrix that will be lit up when the character is made.
	   The characters making the matrix must be the exact size of what you declared
	   the character width and height to be.
	c) There must be a empty line between each new character design
	d) Some characters, other than ' and /, may not work if they involve the / or ' character.
	e) The space character ' ' will be added automatically, so you do not need to add this.
	f) To add an empty row place "~!" in the row. See example below


	-Example- (character width 3, character height 5)
A
 X 
X X
XXX
X X
X X

B
XXX
X X
XXX
X X
XXX

-
~!
~!
 XXXX
~!
~!
	-End Example-


2. If you haven't already compiled the FontGenerator.cpp, do it now
	IE: g++ -o MakeFont.exe .\FontGenerator.cpp

3. Execute the executable. If you followed the step above it will be MakeFont.exe.
   Please note, if your font size is 6 wide by 5 high, the output file will be 
   "Font6x5.h". If that file already exists, it will be OVERWRITTEN WITHOUT WARNING!


	-Example-
>>.\MakeFont.exe
>>What is the fileName of the font design? (include extentsion)
>>FontTemplate.txt
>>How wide are the characters
>>6
>>How high are the characters
>>5
>>
>>        *Opening the file: (FontTemplate.txt)
>>        *The font size is: (6x5)
>>        *charRow is: (000000)
>>        *File is Open
>><adding character>: A
>>111111
>>111111
>>111111
>>111111
>>111111
>><concatenating string>: 1073741823
>><adding character>: B
>>111111
>>111111
>>111111
>>111111
>>111111
>><concatenating string>: 1073741823
>>        *File is Closed
>><concatenating string>: 1073741823
>>        --- Success ---
>>
>>Hit the <Enter> key to quit
	-End Example-


4. Place the new font header file into the directory of the "WriteText.INO". This way the compiler
   will be able to locate the file when "WriteText.INO" is compiled and then transfered to the
   micro computer like a Raspberry Pi or Aurdino.

5. In the "LEDMatrixText.INO" file, include the newly created header file at the top of the code with other
   include statements.


	-Example- (This is in the "LEDMatrixText.INO" file)
/*
	  /////////////////////////////////
	 //     --- Includes ---	//
	/////////////////////////////////
*/
#include <FastLED.h>
#include <string>
#include <fstream>
#include <iostream>
#include "Font3x5.h"
	-End Example-


6. Compile and transfer the "LEDMatrixText.INO" file to the micro computer.
	*Note: Look into Aurduino IDE if you don't know how to do this.

		