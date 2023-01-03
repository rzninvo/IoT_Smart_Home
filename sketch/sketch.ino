/*************************************************************
  

  This sketch shows how to read values from Virtual Pins

  App project setup:
    Slider widget (0...100) on Virtual Pin V1
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID           "TMPLnAQbWiZl"
#define BLYNK_DEVICE_NAME           "SmartHome"
#define BLYNK_AUTH_TOKEN            "TAU19G5mGf0XXZ_yETWc-Kw-dc1HJz3t"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial1
#define temp_pin  A0
#define water_led 24


#include <BlynkSimpleStream.h>
#include <Servo.h>

char auth[] = BLYNK_AUTH_TOKEN;
Servo temperature_slider;
int temperature_set = 0;
int temperature_diff = 5;
int TempValue = 0;

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, TempValue);
}

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  temperature_slider.write(pinValue + 90);
  temperature_set = pinValue;
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial2.begin(9600);
  Blynk.begin(Serial2, auth);
  timer.setInterval(1000L, myTimerEvent);
  temperature_slider.attach(12,1000,2000);
  temperature_slider.write(90);
  pinMode(water_led, OUTPUT);
}

void loop()
{
  Blynk.run();
  timer.run();
  TempValue = analogRead(temp_pin);
  TempValue = ( TempValue/1024.0)*500;
  if (abs(TempValue - temperature_set) >= 5)
    digitalWrite(water_led, HIGH);
  else
    digitalWrite(water_led, LOW);
}
