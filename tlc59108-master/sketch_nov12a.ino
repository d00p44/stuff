#include <Wire.h>
#include "TLC59108.h"
#include <RV-3028-C7.h>

#define HW_RESET_PIN 2
#define ALLCALL 0x48 //TLC59108::I2C_ADDR::ALLCALL
#define I2C_ADDR0 0x40 
#define I2C_ADDR1 0x41 
#define I2C_ADDR2 0x42
#define I2C_ADDR3 0x43

RV3028 rtc;
TLC59108  leds(I2C_ADDR0);
TLC59108  leds1(I2C_ADDR1);
TLC59108  leds2(I2C_ADDR2);
TLC59108  leds3(I2C_ADDR3);
void setup() {
  setup_rtc();
  setup_leds();
  }

void loop(){
  rtc_time();
  sweep();
  
}

void set_digit(TLC59108 &leds, uint8_t digit) // Zuordnung 7-Segment-Anzeige LPv1
{
     leds.setAllBrightness((uint8_t)0x00);
   switch(digit){
    case 0:
      leds.setBrightness(0, 0x44); 
      leds.setBrightness(5, 0x44); 
      leds.setBrightness(6, 0x44); 
      leds.setBrightness(3, 0x44); 
      leds.setBrightness(2, 0x44); 
      leds.setBrightness(7, 0x44); 
      break;
    case 1:
      leds.setBrightness(3, 0x44); 
      leds.setBrightness(6, 0x44); 
      break;
    case 2:
      leds.setBrightness(5, 0x44); 
      leds.setBrightness(6, 0x44); 
      leds.setBrightness(1, 0x44); 
      leds.setBrightness(7, 0x44); 
      leds.setBrightness(2, 0x44); 
     break;
     case 3:
      leds.setBrightness(5, 0x44); 
      leds.setBrightness(6, 0x44); 
      leds.setBrightness(1, 0x44); 
      leds.setBrightness(3, 0x44); 
      leds.setBrightness(2, 0x44); 
      break;
    case 4:
      leds.setBrightness(0, 0x44); 
      leds.setBrightness(1, 0x44); 
      leds.setBrightness(6, 0x44); 
      leds.setBrightness(3, 0x44); 
      break;
    case 5:
      leds.setBrightness(5, 0x44); 
      leds.setBrightness(0, 0x44); 
      leds.setBrightness(1, 0x44); 
      leds.setBrightness(3, 0x44); 
      leds.setBrightness(2, 0x44); 
      break;

    case 6:
      leds.setBrightness(5, 0x44); 
      leds.setBrightness(0, 0x44); 
      leds.setBrightness(1, 0x44); 
      leds.setBrightness(7, 0x44); 
      leds.setBrightness(2, 0x44); 
      leds.setBrightness(3, 0x44); 
      break;

    case 7:
      leds.setBrightness(5, 0x44); 
      leds.setBrightness(6, 0x44); 
      leds.setBrightness(3, 0x44);
      break;

    case 8:
      leds.setBrightness(0, 0x44); 
      leds.setBrightness(1, 0x44); 
      leds.setBrightness(2, 0x44); 
      leds.setBrightness(3, 0x44); 
      leds.setBrightness(5, 0x44); 
      leds.setBrightness(6, 0x44); 
      break;

    case 9:
      leds.setBrightness(0, 0x44); 
      leds.setBrightness(1, 0x44); 
      leds.setBrightness(2, 0x44); 
      leds.setBrightness(3, 0x44); 
      leds.setBrightness(5, 0x44); 
      leds.setBrightness(6, 0x44); 
      break;
    default:
      break;
    }

}

//Initialisierung Leds
void setup_leds()
  {
    leds.init(HW_RESET_PIN);
    leds1.init(HW_RESET_PIN);
    leds2.init(HW_RESET_PIN);
    leds3.init(HW_RESET_PIN);
    delay(500);
    leds.setLedOutputMode(TLC59108::LED_MODE::PWM_IND);
    leds1.setLedOutputMode(TLC59108::LED_MODE::PWM_IND);
    leds2.setLedOutputMode(TLC59108::LED_MODE::PWM_IND);
    leds3.setLedOutputMode(TLC59108::LED_MODE::PWM_IND);
 } 


//RTC Konfiguration
 
void setup_rtc() {
Serial.begin(115200);
  while (!Serial);
  Serial.println("Read/Write Time - RTC Example");

  Wire.begin();
  if (rtc.begin() == false) {
    Serial.println("Something went wrong, check wiring");
    while (1);
  }
  else
    Serial.println("RTC online!");
  delay(1000);
  }

void rtc_time(){
   //PRINT TIME
  if (rtc.updateTime() == false) //Updates the time variables from RTC
  {
    Serial.print("RTC failed to update");
  } else {
    String currentTime = rtc.stringTimeStamp();
    Serial.println(currentTime + "     \'s\' = set time     \'1\' = 12 hours format     \'2\' = 24 hours format");
  }
  //SET TIME?
  if (Serial.available()) {
    switch (Serial.read()) {
      case 's':
        //Use the time from the Arduino compiler (build time) to set the RTC
        //Keep in mind that Arduino does not get the new compiler time every time it compiles. to ensure the proper time is loaded, open up a fresh version of the IDE and load the sketch.
        if (rtc.setToCompilerTime() == false) {
          Serial.println("Something went wrong setting the time");
        }
        //Uncomment the below code to set the RTC to your own time
        /*if (rtc.setTime(sec, minute, hour, day, date, month, year) == false) {
          Serial.println("Something went wrong setting the time");
          }*/
        break;
      case '1':
        rtc.set12Hour();
        break;

      case '2':
        rtc.set24Hour();
        break;
    }
  }
}
//Anzeigen der Segmente (Uhrzeit)
void sweep() {
  
  int stunden = rtc.getHours();
  int minuten = rtc.getMinutes();
  
  set_digit(leds, stunden / 10);
  set_digit(leds1, stunden % 10);
  set_digit(leds2, floor(minuten / 10));
  set_digit(leds3, minuten % 10);
  leds1.setBrightness(4, 0x44); //Segment 4 ist der Punkt -> 1s ein > 1s aus
    delay(1000);
  leds1.setBrightness(4, 0x00);
    delay(1000);
}
