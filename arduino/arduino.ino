/*
I2C: PCF8574T
Address: 0x27 
SCL D7
SDA D6
*/

#include "PCF8574.h"

String serial = "00001";

PCF8574 pcf8574(0x27);





void setup() {
  // put your setup code here, to run once:

  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);

  Serial.begin(230400);
  delay(100);
  // pinMode(5, INPUT);
  Serial.println("connected");
  pcf8574.pinMode(P0, INPUT_PULLUP);
  pcf8574.pinMode(P1, INPUT_PULLUP);
  pcf8574.pinMode(P2, INPUT_PULLUP);

  Serial.println("initialising I2C");
  if (pcf8574.begin()){
    Serial.println("Expander OK");
  } else {
    Serial.println("Failed");
  }

}

void loop() {

  int switch_0 = digitalRead(3);
  int switch_1 = digitalRead(4);
  int switch_2 = digitalRead(5);
  int switch_3 = digitalRead(6);
  int rb = pcf8574.digitalRead(P0);  // outputs serial number on request, used for connection over com. 
  
  String ser_cmd = Serial.readString();
  // String ser_cmd = Serial.readString();
  Serial.println(ser_cmd);


  if (ser_cmd == "serial"){
    Serial.println(serial);
  }

  // reading switches and outputting to com
  if (switch_0) {
    Serial.println("s0");
  }
  
  if (switch_1) {
    Serial.println("s1");
  } 
  
  if (switch_2) {
    Serial.println("s2");
  }

  if (switch_3) {
    Serial.println("s3");
  }

  if (rb) { // rotary encoder push button
    Serial.println("rb");
  }

}
