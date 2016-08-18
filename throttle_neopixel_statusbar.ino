//This will sketch will read all 8 channels of a RC reciever and input the values via serial monitor.
//Programed for the Arduino MEGA 2560!!!

// Define Variables:
const int chA=3;  //Constant variables relating to pin locations
const int ledPIN = 9;
int ch1;  //Varibles to store and display the values of each channel
int maxvalue=0;
int minvalue=2000;

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 8
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  // Set input pins
  pinMode(chA, INPUT);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void colorProgress(uint8_t r, uint8_t g, uint8_t b, uint8_t percent) {
  int value;
  for(uint8_t i=0; i<strip.numPixels(); i++) {
    value=(percent-(i)*(255/8))/(255/8)*255;

    if (value<0) {
      value=0;
    }

    strip.setPixelColor(i, value,g,b);
    
  }
  //strip.setPixelColor(0, 1200,g,b);
  strip.show();
}



//Main Program
void loop() {
  float relValue;
  int PWM1;
  // read the input channels
  ch1 = pulseIn (chA,HIGH);  //Read and store channel 1
  Serial.print ("Ch1:");  //Display text string on Serial Monitor to distinguish variables
  Serial.print (ch1);     //Print in the value of channel 1
  Serial.print ("|");

  if ( ch1 < minvalue ) {
    minvalue=ch1;
  }

  if ( ch1 > maxvalue ) {
    maxvalue = ch1;
  }

  //relValue=(ch1-minvalue)/(maxvalue-minvalue);
  analogWrite(ledPIN, 0);
  relValue=(ch1-1150)/2.9;
  if (relValue>255) {
    relValue=255;
    analogWrite(ledPIN, 255);
  }
  if (relValue<0) {
    relValue=0;
    analogWrite(ledPIN, 255);
  } 
  PWM1=relValue;

  colorProgress(255, 0, 0, PWM1); // Green
  
  
}

