      [ HARDWARE ]
1. ESP8266 NodeMCU CP2102 ESP-12E
2. WS2811 LED Pixels 5V (50ct)
3. KeeYees 2pcs Expansion Board Kits GPIO 1 into 2 for ESP8266 ESP-12E NodeMCU Development Board
   (this is very nice for wiring and testing, but not necessary)
4. KOOBOOK 2Sets HX1838 NEC Infrared IR
5. 1000uF 6.3V and upwards capacitor
6. 200-400ohm resistor


      [ CONNECTIONS ]
-Power Supply-
1. VIN to "5V" power supply, preferrably 3A, but most wall usb adaptors can power 100LEDs at low brightness
2. GND to "0V" power supply, everthing should use a common ground
3. VIN to Capacitor +
4. GND to Capacitor -

-WS2811 LEDs-
1. VIN to "5V" red wire on lights (make sure they are not 12V lights)
	-If using many lights, over 50, you will probably have to inject power at splices
         unless you switch to 12V lights.
2. GND to "0V" black wire on lights
3. D1 to 200-500ohm resistor(470ohm Ideal)
4. resistor to "Data" green wire on lights
	-LEDs are diodes and are directional

-IR Reciever-
1. VCC to 3x3 to  on infrared reciever
2. GND to GND on infrared reciever
3. D5 to DO on infrared reciever


      [ SOFTWARE ]
*Note: WLED is more for festive decorations and offers a very nice UI with many features, just not making a scrolling marque or 
       drawing images. In the future, I may try to add my code into WLED's code

(Unused, but cool) https://github.com/Aircoookie/WLED (Requires ESPHome-Flasher-1.4.0 to put WLED_0.13.0-b7_ESP8266.bin on the device)

-Board Driver- "May not be needed"
1. ESP8266 NodeMCU CP2102 driver: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
	a. for windows machines download CP210x Windows driver
	b. open about pc to find system architecture. Then install the correct version, mine is x64
	
-IDE- "For transferring INO files to ESP8266"
2. Arduino IDE: https://www.arduino.cc/en/software
	-Board Setup-
	a. preferences->additional boards manager urls add https://arduino.esp8266.com/stable/package_esp8266com_index.json then ok
	b. tools->board manager-> search "esp8266" and install
	c. tools->boards->esp8266 Boards->NodeMCU 1.0(ESP-12E Module)
	d. tools->BuiltinLED->2
	e. tools->Upload->921600
	f. tools->CPU->80MHz
	g. tools->Flash->4MB(FS:3MB OTA~512KB)
	d. tools->port->"whatever port it is" mine was COM6

	-Libraries-
	a. tools->managelibraries search for "fastled" and install
	b. tools->managelibraries search for "IRremoteESP8266"
	c. tools->managelibraries search for "ESP8266WiFi"

	-Testing-
	a. file->examples->blink tests that everything works by blinking power indicator
	b. Upload to Node MCU. The indicator light should blink on the board

	-LEDMatrixText- "My code for display text on an LED matrix"

	*Note: Since multithreading isn't possible with the "pthread.h" library and I didn't create my own process scheduler
         I hacked together a way for the IR remote to interrupt scripts, which isn't the best. It does work and that is why you
         should always use the RXDelay() instead of using Delay() to cause pauses. The RXDelay() gives the IR remote a chance
         to interrupt the script where Delay() blocks code from executing.

	a. Move the folder LEDMatrixText into the "Arduino" folder that also has the "libraries" folder in it
	b. Open Arduino IDE
	c. file->sketchbook->LEDMatrixText
	d. configure the code to meet your criteria. If you're using the same number and type of LEDs, Board, and IR reciever do not change.
		-Constants-
		*LED Values "change values to your specific hardware
		*IR Values "I read the baud rate needs to be 74880 for this setup otherwise the ir signal is garbage"

		-Enums/Classes/Structs-
		*Font "If you made a custom font be sure to add it to the font enum"
			-must change function ChangeFont(Font) to change the font size
			-must change function DrawChar(...) to add a new case for the new font
		*Script "If you make any new scripts add the name to the enum"
			-must change function RunScript(...) to add new case for new script
		*TextEffect "If you add any special text effects add it to the enum"
			-must change WriteText(...) to add the text effect in case
		*Color "If you create more custom colors add them to the enum"
			-must change function GetColor(Color) to add new color values to case for new color
		*Button "These are the hex codes and names for each button on the IR remote"
			-must change function GetIRSignal() to add a new script to be ran when a button is pressed on remote

		-Function Declarations-
		*All new functions must be forward declared to ensure everything works properly
		 and the function signature must match the function definition.

		-Variables-
		*These do not need to be changed and are global variables

		-Functions-
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
		bool RXDelay(int time);
		void setup();
		void loop();


      [ TUTORIAL ]
1. Setting up esp8266: https://www.youtube.com/watch?v=AFUAMVFzpWw
2. Explain how to use: https://randomnerdtutorials.com/guide-for-ws2812b-addressable-rgb-led-strip-with-arduino/
3. Complete setup of 8266: https://www.youtube.com/watch?v=90n8cZJcFaU
