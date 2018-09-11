# Hue-Remote
Switchmate-styled remote to switch Philips Hue lightbulbs

First, install these libraries into the Arduino IDE:
* [The ESP8266 core](https://github.com/esp8266/Arduino#installing-with-boards-manager)
  * Remember to select NodeMCU 1.0 (ESP-12E Module) as the board after installing
* [The ESP_Hue library](https://github.com/circuitsforfun/ESP_Hue)
* [The Button library](https://playground.arduino.cc/Code/Button)
  * Search for "button tiny simple" in the [Arduino Library Manager](https://learn.sparkfun.com/tutorials/installing-an-arduino-library#using-the-library-manager) to find the correct library by Michael Adams

Then, rename `credentials-example.h` to `credentials.h` and fill in your WiFi SSID and password and Philips Hue API Key and IP address to communicate with your device.

## Enclosure files
The exported `.stl` files are located in the `models` directory and additional source files can be found on [Thingiverse](https://www.thingiverse.com/thing:2633426).

## License
This work is licensed under a Creative Commons Attribution 3.0 Unported License.
