#include <WiFiClient.h>
#include <ESPHue.h>
#include <Button.h>
// WiFi and Hue settings:
// (refer to credentials-example.h for assistance)
#include "credentials.h"

// Connect to Hue over Wifi
WiFiClient client;
ESPHue myHue = ESPHue(client, HUE_API_KEY, HUE_HOST, 80);

// Set up button and LED pins
Button button(5); // D1

#define R_led 4   // D2
#define G_led 0   // D3
#define B_led 2   // D4

// modified version of ESPHue::getGroupState()
// instead of returning state of "on",
// it returns the state of "any_on"
// I want this because I want to toggle the lights off if *any* of them are on
int getGroupAnyOn(byte groupNum)
{
    int groupState = 0;
    String response = myHue.getGroupInfo(groupNum);

    // if any of them are on (response found)
    if (response.indexOf("\"any_on\":true") > 0)
    {
        // set state as on
        groupState = 1;
    }
    else
    {
        // else, they're all off
        groupState = 0;
    }
    return groupState;
}

// Slowly fade the green LED from full brightness to off
void fadeGreenOff(void)
{
    int brightness = 255;

    while (brightness >= 0)
    {
        //Serial.println(brightness);
        analogWrite(G_led, brightness);
        brightness -= 5;
        delay(20);
    }
}

void setup()
{
    // set LEDs are outputs
    pinMode(R_led, OUTPUT);
    pinMode(G_led, OUTPUT);
    pinMode(B_led, OUTPUT);

    // start the button detection
    button.begin();

    // Start the Serial communication
    //Serial.begin(115200);
    //Serial.println();
    //Serial.print("Connecting to ");
    //Serial.println(SSID);

    // signify that we're starting to connect to WiFi
    digitalWrite(R_led, HIGH);

    // connect to WiFi
    WiFi.begin(SSID, PASSWORD);

    // wait until we're connected
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        //Serial.print(".");
    }

    // print connection status and IP address
    //Serial.println("");
    //Serial.println("WiFi connected");
    //Serial.println("IP address: ");
    //Serial.println(WiFi.localIP());

    // Connected to WiFi; turn off red LED
    digitalWrite(R_led, LOW);
}

void loop()
{
    // when button is pressed...
    if (button.read() == Button::PRESSED)
    {
        // turn green LED on
        analogWrite(G_led, 255);

        //Serial.print("Button Pressed, group state is ");

        // my bulbs are on group 1
        // get their status
        int groupState = myHue.getGroupState(1);
        //Serial.print(groupState);

        // if on,
        if (groupState == 1)
        {
            // turn off
            myHue.setGroupPower(1, myHue.OFF);
            //Serial.println("... off");
        }
        // if off,
        else
        {
            //turn on
            myHue.setGroupPower(1, myHue.ON);
            //Serial.println("... on");
        }

        // Lights switched, fade the green LED off
        fadeGreenOff();
    }

    // if WiFi disconnects...
    if (WiFi.status() != WL_CONNECTED)
    {
        // red LED on
        digitalWrite(R_led, HIGH);

        while (WiFi.begin(SSID, PASSWORD) != WL_CONNECTED)
        {
            // unsuccessful, retry in 4 seconds
            //Serial.print("failed ... ");
            delay(4000);
            //Serial.print("retrying ... ");
            // could try ESP.reset(); if it doesn't reconnect after a few loops
        }

        // red LED off
        digitalWrite(R_led, LOW);
    }
}
