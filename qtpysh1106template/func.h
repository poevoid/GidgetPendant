#pragma once
#include "vars.h"



void animate() {  //just animates
  if (tape.currentframe <= tape.lastframe) {
    tape.currentframe++;
  } else {
    tape.currentframe = tape.firstframe;
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixel.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixel.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixel.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
void rainbow(uint8_t wait) {
  if(pixelInterval != wait)
    pixelInterval = wait;                   
  for(uint16_t i=0; i < pixelNumber; i++) {
    pixel.setPixelColor(i, Wheel((i + pixelCycle) & 255)); //  Update delay time  
  }
  pixel.show();                             //  Update strip to match
  pixelCycle++;                             //  Advance current cycle
  if(pixelCycle >= 256)
    pixelCycle = 0;                         //  Loop the cycle back to the begining
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< pixel.numPixels(); i++) {
      pixel.setPixelColor(i, Wheel(((i * 256 / pixel.numPixels()) + j) & 255));
    }
    pixel.show();
    delay(wait);
  }
}
void initializeTwinkles(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];

  // initialize
  for (uint8_t f = 0; f < NUMFLAKES; f++) {
    icons[f][XPOS] = random(oled.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;
    /*
  Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);*/
  }
  while (screen == ScreenMode::Twinkles) {
    // draw each icon
    rainbow(1);
    for (uint8_t f = 0; f < NUMFLAKES; f++) {
      oled.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SH110X_WHITE);
    }
    oled.display();
    delay(200);

    // then erase it + move it
    for (uint8_t f = 0; f < NUMFLAKES; f++) {
      oled.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SH110X_BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > oled.height()) {
        icons[f][XPOS] = random(oled.width());
        icons[f][YPOS] = 0;
        icons[f][DELTAY] = random(5) + 1;
      }
    }

    if (crudedebounce > 0) { crudedebounce--; }
    //oled.setCursor(0, 0);
    //oled.print("twinkle twinkle, bitch");

    righttouchvalue = touchRead(T7);
    Serial.println(righttouchvalue);
    if (righttouchvalue > threshold && crudedebounce <= 0) {
      crudedebounce = bouncedefault;
      screen = ScreenMode::Waveform;
    }
  }
}
void handleEnvironment() {
  sensors_event_t humidity, temp;
  //int32_t voc_index;
  clim.getEvent(&humidity, &temp);  // populate temp and humidity objects with fresh data
  //voc_index = mox.measureVocIndex(temp.temperature, humidity.relative_humidity);
  oled.setCursor(0, 0);
  oled.print("temp:");
  oled.println(temp.temperature*1.8 + 32);
  oled.print("%rH");
  oled.println(humidity.relative_humidity);
  //oled.print("VOC:");
  //oled.println(voc_index);


  if (crudedebounce > 0) { crudedebounce--; }

  righttouchvalue = touchRead(T7);
  Serial.println(righttouchvalue);
  if (righttouchvalue > threshold && crudedebounce <= 0) {
    crudedebounce = bouncedefault;
    screen = ScreenMode::Twinkles;
  }
}
void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  //int h = timeinfo.H;
  oled.print(&timeinfo, "%H:%M");
}
void maincode() {

  switch (screen) {

    case ScreenMode::Waveform:
      {
        //oled.setCursor(0, 0);

        //printLocalTime();
        for (wave.x = 0; wave.x < 128; wave.x++) {
          int sample = analogRead(MIC_PIN);
          int newy = sample / 64;
          wave.y = newy;

          oled.drawLine(wave.x, lastsample, wave.x, wave.y, SH110X_WHITE);
          oled.display();
          lastsample = newy;
        }



        if (crudedebounce > 0) { crudedebounce--; }

        righttouchvalue = touchRead(T7);
        Serial.println(righttouchvalue);
        if (righttouchvalue > threshold && crudedebounce <= 0) {
          crudedebounce = bouncedefault;
          screen = ScreenMode::Watch;
        }
        Serial.print(righttouchvalue);
        break;
      }

    case ScreenMode::Watch:
      {

        if (crudedebounce > 0) { crudedebounce--; }
        oled.setCursor(cursorx, cursory);
        if (textboxleft) {
          cursorx--;
        } else {
          cursorx++;
        }
        if (textboxup) {
          cursory--;
        } else {
          cursory++;
        }

        if (cursory == 0) {
          textboxup = false;
        }
        if (cursorx == 0) {
          textboxleft = false;
        }
        if (cursorx + TEXT_WIDTH == 128) {
          textboxleft = true;
        }
        if (cursory + TEXT_HEIGHT == 64) {
          textboxup = true;
        }
        printLocalTime();
        righttouchvalue = touchRead(T7);
        Serial.print(righttouchvalue);
        if (righttouchvalue > threshold && crudedebounce <= 0) {
          crudedebounce = bouncedefault;

          screen = ScreenMode::Probe;
        }
        break;
      }
    case ScreenMode::Probe:
      {
        handleEnvironment();

        break;
      }
    case ScreenMode::Twinkles:
      {
        //oled.drawBitmap(5, 5, twinkleArray[2], 5, 5, SH110X_WHITE);test draw bitmap
      // Serial.print(righttouchvalue);
        //Serial.println(lefttouchvalue);
        initializeTwinkles(twinkleArray[0], TWINKLE_WIDTH, TWINKLE_HEIGHT);
        //oled.drawBitmap(0, 0, twinkle1, 5, 5, WHITE);
        // tape.currentframe++;
        break;
      }
  }


  //oled.print(h);oled.print(":");oled.print(m);
}