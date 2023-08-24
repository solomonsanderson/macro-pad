#include <Adafruit_NeoPixel.h>
#include <Adafruit_PCF8591.h>


#define PIN            15
#define NUMPIXELS      8
#define ADC_REFERENCE_VOLTAGE 5.0



Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_PCF8591 pcf = Adafruit_PCF8591();

int red_pot_val, grn_pot_val;

void setup() {
  Serial.begin(115200);
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.show();
  if (!pcf.begin()){
    Serial.print("your ADC is facked!");
  }
 }


void loop() {
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  for(int i=0;i<NUMPIXELS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    // red_pot_val = pcf.analogRead(0);
    // grn_pot_val = pcf.analogRead(1);
    Serial.print("red");
    Serial.println(red_pot_val);
    Serial.print("green");
    Serial.println(grn_pot_val);
    pixels.setPixelColor(i, pixels.Color(red_pot_val, 0, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(100); // Delay for a peri vod of time (in milliseconds).
  }
}
 
float int_to_volts(uint16_t dac_value, uint8_t bits, float logic_level) {
  return (((float)dac_value / ((1 << bits) - 1)) * logic_level);
}
