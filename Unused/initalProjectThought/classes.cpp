#include "prototypes.h"
#include "constants.h"



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

class Pixel
{
    public:
        //enforce that colors are in a valid range
        int validateColorVal(int value)
        {
            return (value % 256);
        };
		//derive rgb value from color
		void setColors(Color pColor)
		{
			switch(pColor)
			{
				case Color.off:
					this->red = 0; this->green = 0; this->blue = 0;
					break;
				case Color.red:
					this->red = 255; this->green = 0; this->blue = 0;
					break;
				case Color.orange:
					this->red = 255; this->green = 200; this->blue = 0;
					break;
				case Color.yellow:
					this->red = 255; this->green = 255; this->blue = 0;
					break;
				case Color.green:
					this->red = 0; this->green = 255; this->blue = 0;
					break;
				case Color.blue:
					this->red = 0; this->green = 0; this->blue = 255;
					break;
				case Color.indigo:
					this->red = 85; this->green = 0; this->blue = 125;
					break;
				case Color.violet:
					this->red = 128; this->green = 0; this->blue = 255;
					break;
				case Color.white:
					this->red = 255; this->green = 255; this->blue = 255;
					break;
			};
		};
        //Default Constructor
        Pixel()	:red(0),    	green(0),		blue(0){};
        //Parameter Constructor
        Pixel(  int rVal,		int gVal,	  	int bVal)
            	:red(rVal),		green(gVal),	blue(bVal){};
        //Overloaded Parameter Constructor
        Pixel(  int rVal,    	int gVal,  		int bVal,  		int aVal)
                :red(rVal),  	green(gVal), 	blue(bVal), 	alpha(aVal){};
		//Overloaded Paramter Constructor
		Pixel(int pixelAsInt)
		{
			size_t bytesPerInt = sizeof(int);
			for (int i = 0; i < bytesPerInt; i++)
			{
				size_t shift = 8 * (bytesPerInt - 1 - i);
				switch(i)
				{
					case 0: //0-7 bits are alpha
						this->alpha = (pixelAsInt >> shift) & 0xff;
					break;
					case 1: //8-15 bits are red
						this->red = (pixelAsInt >> shift) & 0xff;
					break;
					case 2: //16-23 bits are green
						this->green = (pixelAsInt >> shift) & 0xff;
					break;
					case 3: //24-31 bits are blue
						this->blue = (pixelAsInt >> shift) & 0xff;
					break;
				}
			}
		};
		Pixel(Color pColor)
		{
			setColors(pColor);
		};
		Pixel operator=(Pixel otherPix)
		{
			this->setRGB(otherPix.getRed(),otherPix.getGreen(), otherPix.getBlue()); return *this;
		};
        int getRed()                   				{return (this->red * (this->brightness/100));};
        int getGreen()                 				{return (this->green * (this->brightness/100));};
        int getBlue()                  				{return (this->blue * (this->brightness/100));};
        int getAlpha()                 				{return (this->alpha * (this->brightness/100));};
		int getBrightness()							{return this->brightness;};
		bool isOn()									{return this->state;};
		void setRGB(int newR, int newG, int newB)	{red=validateColorVal(newR);green=validateColorVal(newG);blue=validateColorVal(newB);};
        void setRed(int newRed)        				{this->red=validateColorVal(newRed);};
        void setGreen(int newGreen)    				{this->green=validateColorVal(newGreen);};
        void setBlue(int newBlue)      				{this->blue=validateColorVal(newBlue);};
        void setAlpha(int newAlpha)    				{this->alpha=validateColorVal(newAlpha);};
		void setBrightness(int val)					{this->brightness = val%101;};
		void on()									{this->state = true;};
		void off()									{this->state = false;};
        void setPixelSize(int newSize)  			{this->pixelSize=newSize;};
		
    private:
        //values range from 0-255. 0 is absence of color 255 is saturated with color
        //char is used because they are all limited to 8bits, which is the max value of a color
		bool state = false;
		int brightness = 100;
        int alpha = 255;
        int red;
        int green;
        int blue;
        int pixelSize = 3; //color values per pixel IE: 3 is red, green, blue and 4 is alpha, red, green, blue
};