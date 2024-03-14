
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "Adafruit_SHTC3.h"
#include "Adafruit_SGP40.h"
#include <WiFi.h>
#include "time.h"
#include <Adafruit_NeoPixel.h>

// How many internal neopixels do we have? some boards have more than one!



#include "vars.h"

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -21600;
const int daylightOffset_sec = 3600;
#define NUMPIXELS        1
#define OLED_MOSI MOSI
#define OLED_CLK SCK
#define OLED_DC MISO
#define OLED_CS A3
#define OLED_RST A1

Adafruit_NeoPixel pixel(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// Create the OLED display
Adafruit_SH1106G oled = Adafruit_SH1106G(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RST, OLED_CS);

Adafruit_SGP40 mox;                      //metal oxide sensor
Adafruit_SHTC3 clim = Adafruit_SHTC3();  //environmental sensor (temp/humidity)

#include "func.h"


void setup() {
  // put your setup code here, to run once: 
  Wire1.setPins(SDA1, SCL1);
  Serial.begin(9600);
  pinMode(MIC_PIN, INPUT_PULLUP);
  pixel.begin();
 if (!clim.begin(&Wire1)) {
    //sensorsPlugged = false;
    Serial.println("Environmental sensors not detected. Please check your wiring if this is an accident.");
  } else {
    //sensorsPlugged = true;
    Serial.println("Sensors found! Do not disconnect while power is on, please.");
  }
  oled.begin(0, true);  //no i2c, use reset
  oled.display();
  delay(100);
  //connect to WiFi
  
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  //WiFi.disconnect(true);
  //WiFi.mode(WIFI_OFF);
  randomSeed(314159265358979323846472);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint32_t t;
  while (((t = micros()) - prevTime) < (1000000L / MAX_FPS))
    ;
  prevTime = t;
  if (screen != ScreenMode::Twinkles){
    pixel.clear();
    pixel.show();
  }
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(SH110X_WHITE);

  maincode();

  oled.display();
}
