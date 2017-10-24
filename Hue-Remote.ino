#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESPHue.h>
#include <Button.h>
#include "WiFi.h"

WiFiClient client;
ESPHue myHue = ESPHue(client, "29ocf3mMaJ1XAtbqeKM60A4dFen9tSc96u1JuQAi", "philips-hue", 80);

Button button(5); // D1

// modified version of ESPHue::getGroupState()
// instead of returning state of "on",
// it returns the state of "any_on"
// I want this because I want to toggle the lights off if any of them are on
int getGroupAnyOn(byte groupNum)
{
    int groupState = 0;
    String response = myHue.getGroupInfo(groupNum);

    if (response.indexOf("\"any_on\":false") != -1)
    {
      groupState = 0;
    }
    if (response.indexOf("\"any_on\":true") != -1)
    {
      groupState = 1;
    }
    return groupState;
}

void setup() {
  button.begin();
  
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  
}

void loop() {
  if (button.read() == Button::PRESSED)
  {
    Serial.println("Button Pressed, group state is");

    int groupState = myHue.getGroupState(1);
    Serial.print(groupState);

    // if on,
    if (groupState == 1){
      // turn off
      myHue.setGroupPower(1, myHue.OFF);
      Serial.println("off");
    }
    // if off,
    else {
      //turn on
      myHue.setGroupPower(1, myHue.ON);
      Serial.println("on");
    }
  }
}
