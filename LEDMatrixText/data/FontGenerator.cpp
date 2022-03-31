
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;
// "C:\Users\pakum\Desktop\LED_Project\Paul Code\FastLEDTextExtension\Text"


//prompt the user for filename and design size, returns filename
void promptUser(int *charWidth, int *charHeight, string *fileName)
{
	string tempWidth;
	string tempHeight;
	cout << "What is the fileName of the font design? (include extentsion)" << endl;
	getline(cin, *fileName);
	cout << "How wide are the characters" << endl;
	getline(cin, tempWidth);
	cout << "How high are the characters" << endl;
	getline(cin, tempHeight);
	*charWidth = stoi(tempWidth);
	*charHeight = stoi(tempHeight);
}

int main(int argc, char *argv[]) //arg[0]: the program, arg[1]: read file name, arg[2]: character width, arg[3]: character height
{
	string fileName;
	string outFile = "Font";
	string *filePtr = &fileName;
	int charWidth;
	int charHeight;
	int arrayLength;
	int returnVal = 1;
	string charRow; //may use this and index it to prevent out of bounds index while making the bitArrStr
	string nameExt;

	if(argc == 4)
	{
		fileName = string(argv[1]);
		charWidth = atoi(argv[2]);
		charHeight = atoi(argv[3]);	
	}
	else
	{
		promptUser(&charWidth, &charHeight, filePtr);
	}

	charRow = string(charWidth, '0');
	arrayLength = charWidth * charHeight;
	nameExt = to_string(charWidth) + "x" + to_string(charHeight);
	outFile += nameExt + ".h";

	cout << "\n\t*Opening the file: (" << fileName << ")" << endl;
	cout << "\t*The font size is: (" << charWidth << "x" << charHeight << ")" << endl;
	cout << "\t*charRow is: (" << charRow << ")" << endl;

	ifstream textFile (fileName);

	string outText = "#include <map>\n#include <bitset>\n\n";
	string bitSetStr = "std::bitset<" + to_string(arrayLength) + ">";
	string mapStr = "static std::map<char, " + bitSetStr + "> charMap" + nameExt + " = {\n";
	mapStr += "\t{' ', " + bitSetStr + "(0)},\n"; //{' ', std::bitset<15>(0)}
	string bitArrayStr = "";

	char character;
	string word;
	int createdChar;
	int wordLength;
	


	if(textFile.is_open())
	{
		cout << "\t*File is Open" << endl;

		char bitVal;
		bool charFinished = true;

		while(getline(textFile, word) && !textFile.eof())
		{	
			wordLength = word.length();
			string oneRow = charRow;

			if(wordLength == 1 && charFinished) //This is the character being created
			{
				character = word[0];

				cout << "<adding character>: " << character << endl;

				if(character == '\\' || character == '\'')
				{
					mapStr = mapStr + "\t{'\\" + character + "', " + bitSetStr + "(";
				}
				else
				{
					mapStr = mapStr + "\t{'" + character + "', " + bitSetStr + "(";
				}

				charFinished = false;
			}
			else if(wordLength > 0) //this is the binary conversion of the char design
			{
				oneRow = charRow;

				if(word != "~!")
				{
					for(int i = 0; i < wordLength; i++)
					{
						bitVal = word[i] == ' '? '0': '1';
						//cout << bitVal;
						oneRow[(charWidth-1)-i] = bitVal;
					}
				}
				
				//cout << endl;
				cout << oneRow << endl;

				bitArrayStr += oneRow;
			}
			else //concatenate the product on newline only
			{
				createdChar = stoi(bitArrayStr, nullptr, 2);

				cout << "<concatenating string>: " << createdChar << endl;

				mapStr = mapStr + to_string(createdChar) + ")},\n";
				bitArrayStr = "";
				
				charFinished = true;
			}
		}
		textFile.close();
		cout << "\t*File is Closed" << endl;

		//Add last character
		createdChar = stoi(bitArrayStr, nullptr, 2);
		mapStr = mapStr + to_string(createdChar) + ")}\n};";

		cout << "<concatenating string>: " << createdChar << endl;

		outText += mapStr;
		//End last character

		//write header file
		ofstream outfile(outFile);
		outfile << outText << endl;
		outfile.close();
		//end write header file

		cout << "\t--- Success ---\n" << endl;

		returnVal = 0;
	}
	else
	{
		cout << "Error: Unable to open the file, make sure the file exists and is spelled correctly" << endl;
	}

	string temp;
	
	cout << "Hit the <Enter> key to quit" << endl;
	getline(cin, temp);

	return returnVal;
}