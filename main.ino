// Adafruit IO Digital Output Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-digital-output
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

// DASHBOARD LINK: https://io.adafruit.com/jpwall/dashboards/session2

#include "config.h"

// The green LED is connected to pin 32
#define LED_PIN 32
// The red LED is connected to pin 33
#define LED_PIN_RED 33

// set up the feed for 'Session2'
AdafruitIO_Feed *digital = io.feed("Session2");
// set up the feed for 'Session2Red'
AdafruitIO_Feed *red = io.feed("Session2Red");

void setup() {
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_RED, OUTPUT);
  
  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the feeds.
  
  // The below handler interprets the green toggles
  digital->onMessage(handleMessage);
  // The below handler interprets the red toggles
  red->onMessage(handleMessage);

  // NOTE: Yes, they both go to the same place

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  digital->get();
  red->get();

}

void loop() {
  // keep client connected to io.adafruit.com
  io.run();
}

// Function to handle data from the dashboard
// for turning on or off the LEDs
void handleMessage(AdafruitIO_Data *data) {

  // Store the sent value from dashboard as an int
  int val = data->toInt();

  // The below if / else if statements are the
  // conditions for turning on or off each LED.
  // First digit is the LED, and second is the
  // desired state.
  if (val == 11) {
    // 11: LED 1 (green) state 1 (ON)
    digitalWrite(LED_PIN, HIGH);
    Serial.println("G ON");
  } else if (val == 10) {
    // 10: LED 1 (green) state 0 (OFF)
    digitalWrite(LED_PIN, LOW);
    Serial.println("G OFF");
  } else if (val == 21) {
    // 21: LED 2 (red) state 1 (ON)
    digitalWrite(LED_PIN_RED, HIGH);
    Serial.println("R ON");
  } else if (val == 20) {
    // 20: LED 2 (red) state 0 (OFF)
    digitalWrite(LED_PIN_RED, LOW);
    Serial.println("R OFF");
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(LED_PIN_RED, LOW);
  }
}
