#include <string>

String in = "none";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

String read_serial() {
  in = Serial.readString();
  return in;
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // if (in != NULL) {
  //   Serial.print("out");
  //   Serial.print(in);
  //   Serial.println("\r");
  
  // }else{
  //   Serial.println("enter string");
  // }
  String ret_str = read_serial();
  Serial.println(ret_str);
  delay(1000);
  Serial.println("yoyoyoyo");
  }

