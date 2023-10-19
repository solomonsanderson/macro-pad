#include "Adafruit_NeoKey_1x4.h"
#include <Adafruit_NeoPixel.h>
#include <Adafruit_PCF8591.h>
#include <ArduinoJson.h>

#define LED_STRIP 2

#define CLK 12
#define DT 13
#define SW 14

Adafruit_NeoPixel led_strip = Adafruit_NeoPixel(8, LED_STRIP, NEO_GRB + NEO_KHZ800);
Adafruit_PCF8591 adc = Adafruit_PCF8591();
Adafruit_NeoKey_1x4 neokey;

uint32_t full_blue =  0x0000FF;
uint16_t key = 1;


int slide_0;
int slide_1;

int red = 3;
int green = 252;
int blue = 232;

int rot_count = 0;
int curr_clk;
int prev_clk;

int rot_sw;

int keys_index;

StaticJsonDocument<200> doc;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  led_strip.begin();
  led_strip.show();
  if (!adc.begin()){
    Serial.println("ADC failed to start");
  }

  if (!neokey.begin(0x30)) {
    Serial.println("neokey failed to start");
  }

  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);
      
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t keys = neokey.read();
  neokey.pixels.setPixelColor(key, full_blue);
  // Serial.println(keys);

  int key_nums[] = {1, 2, 4, 8, 3, 5, 9, 6, 10, 12, 7, 14, 13, 11, 15};
  String num_vals[] = {"A", "B", "C", "D", "AB", "AC", "AD", "BC", "BD", "CD", "ABC", "BCD", "ACD", "ABD", "ABCD"};


  for (int i=0; i<sizeof(key_nums); i++) {
   if (keys == key_nums[i]) {
     keys_index = i;
     break;
    }
  } 
  if (String(num_vals[keys_index]) == ""){
    doc["keys"] = "None";
  } else {
    doc["keys"] = String(num_vals[keys_index]);
  }

  // Serial.println(keys_index);
  
  // reading slide pots
  slide_0 = adc.analogRead(0);  
  slide_1 = adc.analogRead(1);

  doc["slide_0"] = slide_0;
  doc["slide_1"] = slide_0;

  // set led strip color
  for (int pixel = 0; pixel < 9; pixel++){
    led_strip.setPixelColor(pixel, led_strip.Color(red, green, blue));
    led_strip.show();
    }

  
  curr_clk = digitalRead(CLK);

  if (curr_clk != prev_clk && curr_clk == 1){
    if (digitalRead(DT) != curr_clk){
      rot_count --;
    }
    else{
      rot_count ++; 
    }
  }
  prev_clk = curr_clk;

  doc["rot_count"] = rot_count;
  rot_sw = digitalRead(SW);
  doc["rot_sw"] = rot_sw;


  // Serial.print("{\"keys\":");
  // Serial.print(num_vals[keys_index]);
  // Serial.print(",\"slide_0\":");
  // Serial.print(slide_0);
  // Serial.print(",\"slide_1\":");
  // Serial.print(slide_1);
  // Serial.print(",\"rot_count\":");
  // Serial.print(rot_count);
  // Serial.print(",\"rot_sw\":");
  // Serial.print(rot_sw);
  // Serial.println("}");
  // delay(1000);
  serializeJsonPretty(doc, Serial);
}
