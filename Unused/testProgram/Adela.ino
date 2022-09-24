#include <FastLED.h>

//#define CLK_PIN           4
#define LED_TYPE            WS2812
#define DATA_PIN            2
#define COLOR_ORDER         RGB
#define NUM_LEDS            100
#define BRIGHTNESS          255
#define VOLTAGE             5
#define MAX_POWER_MILLIAMPS 120

const uint8_t LED_WIDTH = 20;
const uint8_t LED_HEIGHT = 5;

//initialize an array for storing LED pixels
CRGB leds[NUM_LEDS];

/*
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


//FUNCTIONS
uint16_t GetPixel( uint8_t x, uint8_t y) //gets a pixel from x, y coordinate in matrix
{
  uint16_t i;
  
  if( y & 0x01) // Odd rows run backwards
  {
    uint8_t reverseX = (LED_WIDTH - 1) - x;
    i = (y * LED_WIDTH) + reverseX;
  } 
  else // Even rows run forwards
  {
    i = (y * LED_WIDTH) + x;
  }
 
  return i;
}



void DrawOneFrame()
{
  uint8_t reductionVal = 10;
  uint8_t rColor = rand()%255, gColor = rand()%255, bColor = rand()%255;

  for( uint8_t y = 0; y < LED_HEIGHT; y++) 
  {
    for( uint8_t x = 0; x < LED_WIDTH; x++) 
    {
      leds[ GetPixel(x, y)]  = CRGB(rColor/reductionVal,gColor/reductionVal,bColor/reductionVal);
    }
  }
  
  /* A */
                                                                  leds[GetPixel(1,4)] = CRGB(rColor,gColor,bColor);
  leds[GetPixel(0,3)] = CRGB(rColor,gColor,bColor);                                                                           leds[GetPixel(2,3)] = CRGB(rColor,gColor,bColor);
  leds[GetPixel(0,2)] = CRGB(rColor,gColor,bColor);               leds[GetPixel(1,2)] = CRGB(rColor,gColor,bColor);           leds[GetPixel(2,2)] = CRGB(rColor,gColor,bColor);
  leds[GetPixel(0,1)] = CRGB(rColor,gColor,bColor);                                                                           leds[GetPixel(2,1)] = CRGB(rColor,gColor,bColor);
  leds[GetPixel(0,0)] = CRGB(rColor,gColor,bColor);                                                                           leds[GetPixel(2,0)] = CRGB(rColor,gColor,bColor);

  /* D */
  leds[GetPixel(4,4)] = CRGB(rColor,gColor,bColor);               leds[GetPixel(5,4)] = CRGB(rColor,gColor,bColor);           
  leds[GetPixel(4,3)] = CRGB(rColor,gColor,bColor);                                                                           leds[GetPixel(6,3)] = CRGB(rColor,gColor,bColor);
  leds[GetPixel(4,2)] = CRGB(rColor,gColor,bColor);                                                                           leds[GetPixel(6,2)] = CRGB(rColor,gColor,bColor);
  leds[GetPixel(4,1)] = CRGB(rColor,gColor,bColor);                                                                           leds[GetPixel(6,1)] = CRGB(rColor,gColor,bColor);
  leds[GetPixel(4,0)] = CRGB(rColor,gColor,bColor);               leds[GetPixel(5,0)] = CRGB(rColor,gColor,bColor);           


  /* E */
  leds[GetPixel(8,4)] = CRGB(rColor,gColor,bColor);               leds[GetPixel(9,4)] = CRGB(rColor,gColor,bColor);           leds[GetPixel(10,4)] = CRGB(rColor,gColor,bColor);
  leds[GetPixel(8,3)] = CRGB(rColor,gColor,bColor);                                      
  leds[GetPixel(8,2)] = CRGB(rColor,gColor,bColor);               leds[GetPixel(9,2)] = CRGB(rColor,gColor,bColor);           
  leds[GetPixel(8,1)] = CRGB(rColor,gColor,bColor);                                       
  leds[GetPixel(8,0)] = CRGB(rColor,gColor,bColor);               leds[GetPixel(9,0)] = CRGB(rColor,gColor,bColor);           leds[GetPixel(10,0)] = CRGB(rColor,gColor,bColor);

  /* L */
  leds[GetPixel(12,4)] = CRGB(rColor,gColor,bColor);               
  leds[GetPixel(12,3)] = CRGB(rColor,gColor,bColor);               
  leds[GetPixel(12,2)] = CRGB(rColor,gColor,bColor);               
  leds[GetPixel(12,1)] = CRGB(rColor,gColor,bColor);               
  leds[GetPixel(12,0)] = CRGB(rColor,gColor,bColor);              leds[GetPixel(13,0)] = CRGB(rColor,gColor,bColor);          leds[GetPixel(14,0)] = CRGB(rColor,gColor,bColor);


  /* A */
                                                                  leds[GetPixel(17,4)] = CRGB(rColor,gColor,bColor);
  leds[GetPixel(16,3)] = CRGB(rColor,gColor,bColor);                                                                          leds[GetPixel(18,3)] = CRGB(rColor,gColor,bColor);
  leds[GetPixel(16,2)] = CRGB(rColor,gColor,bColor);              leds[GetPixel(17,2)] = CRGB(rColor,gColor,bColor);          leds[GetPixel(18,2)] = CRGB(rColor,gColor,bColor);
  leds[GetPixel(16,1)] = CRGB(rColor,gColor,bColor);                                                                          leds[GetPixel(18,1)] = CRGB(rColor,gColor,bColor);
  leds[GetPixel(16,0)] = CRGB(rColor,gColor,bColor);                                                                          leds[GetPixel(18,0)] = CRGB(rColor,gColor,bColor);
}

void setup() 
{
  if(LED_WIDTH * LED_HEIGHT != NUM_LEDS || BRIGHTNESS > 255 || BRIGHTNESS < 0)
  {
    exit(0);
  }
  else
  {
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalPixelString);//correction types: TypicalLEDStrip, TypicalSMD5050, TypicalLEDStrip, TypicalPixelString
    FastLED.setMaxPowerInVoltsAndMilliamps( VOLTAGE, MAX_POWER_MILLIAMPS);
    FastLED.setBrightness( BRIGHTNESS );
  }
}

void loop() 
{
    uint8_t redColor = rand()%255, greenColor = rand()%255, blueColor = rand()%255;
    int posOne=0, posTwo=-1, posThree=-3, posFour=-6, posFive=-10;
    
     // Move leds 
    for(int pixPos = 0; pixPos < (NUM_LEDS+10); pixPos++)
    {
      // change pixel colors
      if(posOne >= 0 && posOne < NUM_LEDS)
      {
        leds[posOne] = CRGB(redColor, greenColor, blueColor);
      }
      if(posTwo >= 0 && posTwo < NUM_LEDS)
      {
        leds[posTwo] = CRGB(redColor/2, greenColor/2, blueColor);
      }
      if(posThree >= 0 && posThree < NUM_LEDS)
      {
        leds[posThree] = CRGB(redColor/4, greenColor/4, blueColor/4);
      }
      if(posFour >= 0 && posFour < NUM_LEDS)
      {
       leds[posFour] = CRGB(redColor/16, greenColor/16, blueColor/8); 
      }
      if(posFive >= 0 && posFive < NUM_LEDS)
      {
        leds[posFive] = CRGB(0,0,0);
      }

      //set pixel postions
      posOne++;
      posTwo++;
      posThree++;
      posFour++;
      posFive++;
      
      // Show the leds (only one of which is set to white, from above)
      FastLED.show();

      // Wait a little bit
      delay(30);
   }

  DrawOneFrame();
  
  // Show the leds (only one of which is set to white, from above)
  FastLED.show();

  // Wait a little bit
  delay(5000);

  FastLED.clear();
  FastLED.show();
 
}
