      [ HARDWARE ]
1. ESP8266 NodeMCU CP2102 ESP-12E
2. WS2811 LED Pixels 5V (50ct)

      [ SOFTWARE ]
1. ESP8266 NodeMCU CP2102 driver: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
	a. for windows machines download CP210x Windows driver
	b. open about pc to find system architecture. Then install the correct version, mine is x64 
2. Arduino IDE
	a. preferences->additional boards manager urls add https://arduino.esp8266.com/stable/package_esp8266com_index.json then ok
	b. tools->board manager-> search "esp8266" and install
	c. file->examples->blink tests that everything works by blinking power indicator
	d. select the 8266 from tools->boards
3. FastLED:

      [ TUTORIAL ]
1. Setting up esp8266: https://www.youtube.com/watch?v=AFUAMVFzpWw
2. Explain how to use: https://randomnerdtutorials.com/guide-for-ws2812b-addressable-rgb-led-strip-with-arduino/
3. Complete setup of 8266: https://www.youtube.com/watch?v=90n8cZJcFaU
