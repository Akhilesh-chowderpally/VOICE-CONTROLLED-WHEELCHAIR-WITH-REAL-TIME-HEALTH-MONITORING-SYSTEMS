#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8);          // NRF24L01 CE and CSN pins
const byte address[] = "robot";  // NRF24L01 address

int in1=10;      
int in2=5;
int in3=6;
int in4=9;

void setup() {
  Serial.begin(115200);

  pinMode(in1,OUTPUT);   
  pinMode(in2,OUTPUT);   
  pinMode(in3,OUTPUT);   
  pinMode(in4,OUTPUT);
   
  pinMode(4, INPUT); // input declaration for ir sensor
  

  // Initialize NRF24L01
  radio.begin();
  radio.openReadingPipe(0, address); // Open the reading pipe with the same address
  radio.setPALevel(RF24_PA_MIN);     // Set RF24 power level to minimum
  radio.startListening();            // Start listening for commands
}

void loop() {
  if (radio.available()) {  // Check if a command is received
    uint8_t CMDID;
    radio.read(&CMDID, sizeof(CMDID));  // Read the command ID
    Serial.print("Received CMDID: ");
    Serial.println(CMDID);

    int f = digitalRead(4);
    int b = digitalRead(3);
    
    // Control robot movements based on CMDID
    if (CMDID == 5 && f == 1) {       // Command for "Forward"
      moveForward1();
    } else if (CMDID == 6 && b == 1) { // Command for "Backward"
      moveBackward1();
    }
    if (CMDID == 12 && f == 1) {       // Command for joystick "Forward"
      moveForward();
    } else if (CMDID == 13 && b == 1) { // Command for joystick "Backward"
      moveBackward();
    }
      else if (CMDID == 7) { // Command for "Turn Right"
      turnRight1();
    } else if (CMDID == 8) { // Command for "Turn Left"
      turnLeft1();
    } else if (CMDID == 10) { // Command for "joystick right"
      turnRight();
    } else if (CMDID == 11) { // Command for "joystick left"
      turnLeft();
    } else if (CMDID == 9 ) {
      stopRobot();           // Default to stop if unknown command is received
    } else if (CMDID == 0 ) {
      stopRobot();           // Default to stop if unknown command is received
    }
  }
}

// Robot movement functions

void moveForward1() {
  
// Set motor control using analogWrite (PWM)
    analogWrite(in1, 0);   
    analogWrite(in2, 90); 
    analogWrite(in3, 90);
    analogWrite(in4, 0); 
    delay(2000);
    stopRobot(); 
        
    Serial.println("Moving Forward");

}

void moveBackward1() {
  
    analogWrite(in1, 90);   
    analogWrite(in2, 0); 
    analogWrite(in3, 0); 
    analogWrite(in4, 90);   
    delay(2000);
    stopRobot(); 
    
  Serial.println("Moving Backward");
}

void moveForward() {
  
// Set motor control using analogWrite (PWM)
    analogWrite(in1, 0);   
    analogWrite(in2, 90); 
    analogWrite(in3, 90);
    analogWrite(in4, 0); 


    
    Serial.println("Moving Forward");

}

void moveBackward() {
  
    analogWrite(in1, 90);   
    analogWrite(in2, 0); 
    analogWrite(in3, 0); 
    analogWrite(in4, 90);   


  
  Serial.println("Moving Backward");
}

void turnRight() {

    analogWrite(in1, 100);   
    analogWrite(in2, 0); 
    analogWrite(in3, 100); 
    analogWrite(in4, 0); 
     
  Serial.println("Turning Right");
}

void turnLeft() {

    analogWrite(in1, 0);   
    analogWrite(in2, 100); 
    analogWrite(in3, 0); 
    analogWrite(in4, 100); 
    
  Serial.println("Turning Left");
}

void stopRobot() {
  
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);  
  
  Serial.println("Stopping Robot");
}



void turnRight1() {

    analogWrite(in1, 100);   
    analogWrite(in2, 0); 
    analogWrite(in3, 100); 
    analogWrite(in4, 0); 
    delay(500);
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);  
  
  Serial.println("Turning Right1");
}

void turnLeft1() {


    analogWrite(in1, 0);   
    analogWrite(in2, 100); 
    analogWrite(in3, 0); 
    analogWrite(in4, 100);
    delay(500);
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW); 
    
  Serial.println("Turning Left1");
}
