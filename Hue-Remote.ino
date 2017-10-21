#include <ESP8266WiFi.h>
#include <restclient.h>
#include "wifi.h"

// Global variables
#define ESP8266_BTN 16 // D0

// Hue Configuration
const char HUE_IP[] = "philips-hue";
const  int HUE_PORT = 80;
restclient hue(HUE_IP,HUE_PORT);

const char LIGHTS_ON[] = "{\"on\":true}";
const char LIGHTS_OFF[] = "{\"on\":false}";

// App Configuration
bool btn = false;
int duration = 0;
int button_press = 0;

void blinkLED(int dlay, int count = 1)
{
  for (int c=0; c < count; c++) {
    delay(dlay);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(dlay);
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ESP8266_BTN, INPUT_PULLUP);
  // Set WiFi mode to station (client)
  WiFi.mode(WIFI_STA);

  // Initiate connection with SSID and PSK
  WiFi.begin(WIFI_SSID, WIFI_PSK);

  // Blink LED while we wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) blinkLED(100);
  if (WiFi.status() != WL_CONNECTED) while(1) blinkLED(1000);
}

void loop()
{
  btn = (digitalRead(ESP8266_BTN) == LOW);
  duration = 1;
  button_press = 0;
  analogWrite(LED_BUILTIN, 0);

  while (btn) {
    analogWrite(LED_BUILTIN, duration * 100);
    if (btn) button_press = 1;
    duration = (duration > 9) ? 10 : ++duration;
    btn = (digitalRead(ESP8266_BTN) == LOW);
    delay(75);
  }

  if (1 < duration && duration < 10) { // short press
    if (button_press == 1)
      hue.put("/api/29ocf3mMaJ1XAtbqeKM60A4dFen9tSc96u1JuQAi/groups/1/action",LIGHTS_OFF);  // All off
  }
  else if (duration >= 10) { // long press
    if (button_press == 1)
      hue.put("/api/29ocf3mMaJ1XAtbqeKM60A4dFen9tSc96u1JuQAi/groups/1/action",LIGHTS_ON);  // All on
  }
}
