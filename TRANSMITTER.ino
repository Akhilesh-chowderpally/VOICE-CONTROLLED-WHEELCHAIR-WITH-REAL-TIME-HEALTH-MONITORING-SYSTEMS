#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

// THE ABOVE LIBARIES ARE FOR SPI COMMUNICATION AND NRF(NRF24L01) COMMUNICATION

#include "DFRobot_DF2301Q.h"   //Libaries for voice recognition module


const int buttonPin = 2; // Pin where the push button is connected
bool currentState = LOW;  // State of the button
bool lastState = LOW;     // Stores the last state of the button
bool toggleState = false; // Flag to toggle between functions

const int xPin = A0;  // Joystick X-axis
const int yPin = A1;  // Joystick Y-axis


DFRobot_DF2301Q_I2C DF2301Q;

RF24 radio(7,8);   // declaring CE and CSN pins of NRF module
const byte address[] = "robot"; 



void setup() {

  pinMode(buttonPin, INPUT_PULLUP); // Button pin as input with internal pull-up
  //pinMode(13,OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  Serial.begin(115200);

    while( !( DF2301Q.begin() ) ) {
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");
  DF2301Q.setVolume(15);
  DF2301Q.setMuteMode(0);
  DF2301Q.setWakeTime(15);
  
  // DF2301Q.playByCMDID(1);   // Wake-up command
  
  DF2301Q.playByCMDID(23);   // Common word ID

     //THE BELOW CODE BELONGS TO NRF COMMUNICATION
     
  radio.begin();           // initializes the operations of the chip
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

}


void loop() {
  currentState = digitalRead(buttonPin);

  if (currentState == LOW && lastState == HIGH) {
    toggleState = !toggleState; 
    delay(200);                 
  }
  lastState = currentState; 


  if (toggleState) {
    voice_control();
  } else {
    joystick_control();
  }
}


void voice_control() {
//digitalWrite(13,1);

  digitalWrite(10,1);
  digitalWrite(9,0);

  uint8_t CMDID = 1;
  CMDID = DF2301Q.getCMDID();
  
  //radio.write(&CMDID, sizeof(CMDID));

  if(CMDID == 5) {
    radio.write(&CMDID, sizeof(CMDID));
    Serial.print("CMDID = 5 - ");
    Serial.println("FORWARD");
  }
  else if(CMDID == 6){
    radio.write(&CMDID, sizeof(CMDID));
    Serial.print("CMDID = 6 - ");
    Serial.println("BACK");
    }
  else if(CMDID == 7){
    radio.write(&CMDID, sizeof(CMDID));
    Serial.print("CMDID = 7 - ");
    Serial.println("RIGHT");
    }
  else if(CMDID == 8){
    radio.write(&CMDID, sizeof(CMDID));
    Serial.print("CMDID = 8 - ");
    Serial.println("LEFT");
    }
  else if(CMDID == 9){
    radio.write(&CMDID, sizeof(CMDID));
    Serial.print("CMDID = 9 - ");
    Serial.println("stop");
    }
  delay(100);
}


void joystick_control() {
  //digitalWrite(13,0);

  digitalWrite(10,0);
  digitalWrite(9,1);

  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);

  uint8_t CMDID = 0;                            

  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" | Y: ");
  Serial.println(yValue);

if (xValue >= 1000 ) {
    CMDID = 12;
    radio.write(&CMDID, sizeof(CMDID));
  } 
  else if (xValue <= 10) {
    CMDID = 13;
    radio.write(&CMDID, sizeof(CMDID));
  } 
  else if (yValue >= 1000) {
    CMDID = 10;
    radio.write(&CMDID, sizeof(CMDID));
  } 
  else if (yValue <= 10) {
    CMDID = 11;
    radio.write(&CMDID, sizeof(CMDID));
  } 
  else {
    CMDID = 0;
    radio.write(&CMDID, sizeof(CMDID));
  }

  delay(100);  // Small delay for stability 

  Serial.println("joystick control");
}
