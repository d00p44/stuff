
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Adafruit_NeoPixel.h>
#include <math.h>
#include <Wire.h>
#include "RTClib.h"

#define PIN 13
#define anzahl_leds 13 
RTC_DS3231 rtc;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(13, anzahl_leds, NEO_GRB + NEO_KHZ800);

 
void setup () {

  Serial.begin(9600);
  delay(1000); // wait for console opening
   if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
 
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  //Strip starten.  
  strip.begin();
  strip.setBrightness(60);
  strip.show(); // Initialize all pixels to 'off'
}
 
void loop () {
    DateTime now = rtc.now();

    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);

    //Alle Aus machen (die passenden LEDs machen wir im code unten an).
  for(int i=0;i<13;i++){
    strip.setPixelColor(i, 0, 0, 0);
  }
  
  int stunden = now.hour(); //Holen uns die Stunden vom timeClient (von der RTC)
  int minuten = now.minute(); //Holen uns die Minuten vom timeClient  (von der RTC)

  //Stundeneinstellung. Wenn es 12 Uhr ist, muss vorne ne 1 Leuchten, bei 23 Uhr die 2. Erstmal unterscheiden wir. Die Zehner sind dran.
  if(stunden >= 10) {
    if(stunden >=20) {
      // strip.setPixelColor(INDEX der LED, Red-Wert, Green-Wert, Blue-Wert);
      strip.setPixelColor(0, 100, 120, 100);      //Wie auf den Bild zu sehen, die "2 " von der Uhrzeit 23 hat den index 0

      //Hier haben wir die lampe für 2 Angemacht und für 1 Ausgemacht.
    } else {
      strip.setPixelColor(1, 100, 120, 100);
    }  
  }
  //jetzt kümmern wir und um die anderen lampen. für 12:34 haben wir erst die erste 1. X2:34 fehlen noch.
  int stundenrechnung = stunden;
  //wir ziehen die erste stelle ab. daraus wird aus Stunde 12 -> (12 -10 = 2) oder aus 23 Uhr -> (23 - 20 = 3).
  if(stunden > 10){
    if(stunden >20) {
      stundenrechnung = stundenrechnung -20;
      } else {
        stundenrechnung = stundenrechnung -10;
       }
    }

   // nun schauen wir, welchen wert wir haben und machen die lampen pasend an.
   switch(stundenrechnung){
    case 0:
      //0 Lassen wir die lampe einfach aus.
    break;
    case 1:
      // wenn der 2te wert 1 ist, sind wir nun hier angekommen. Aus 11 uhr haben wir oben schon (11 - 10 = 1) auf die zweite Stelle reduziert. Jetzt müssen wir die Passende LED noch anmachen. Index 2
       strip.setPixelColor(2, 100, 120, 100); //LED mit den Index 2 an. 
    break;
    case 2:
      strip.setPixelColor(3, 100, 120, 100); //LED mit den Index 3
    break;
    case 3:
      strip.setPixelColor(2, 100, 120, 100); //LED mit den Index 2 an. 
      strip.setPixelColor(3, 100, 120, 100); //LED mit den Index 3 an.  (Index 2 ist Uhrzeit 1 und Index 2 ist Uhrzeit 2. 2+1 = 3)
    break;
    case 4:
      strip.setPixelColor(4, 100, 120, 100); //LED mit den Index 4 an.  
    break;

    case 5:
      strip.setPixelColor(4, 100, 120, 100); //LED mit den Index 4 an.
      strip.setPixelColor(2, 100, 120, 100); //LED mit den Index 2 an. 
    break;

    case 6:
      strip.setPixelColor(4, 100, 120, 100); //LED mit den Index 4 an. 
      strip.setPixelColor(3, 100, 120, 100); //LED mit den Index 3 an. 
    break;

    case 7:
      strip.setPixelColor(4, 100, 120, 100); //LED mit den Index 4 an.       
      strip.setPixelColor(3, 100, 120, 100); //LED mit den Index 3 an.      
      strip.setPixelColor(2, 100, 120, 100); //LED mit den Index 2 an.       
                                             //                              ____________________________
                                             //                                                       7 (für 17 Uhr die 7)
    break;

    case 8:
      strip.setPixelColor(5, 100, 120, 100); //LED mit den Index 5 an. 
    break;

    case 9:
      strip.setPixelColor(5, 100, 120, 100); //LED mit den Index 5 an. 
      strip.setPixelColor(2, 100, 120, 100); //LED mit den Index 2 an. 
    break;
    }

    //Damit haben wir die Stunden schon programmiert. Mann könnte es auch ganz anders lösen, aber ich habe diesen weg genommen, da es sehr einfach zu verstehen ist. Natürlich hätte ich auch mit ein Algohritmus oder Modulo arbeiten können.
    //Die Minuten sind im Prinzip das selbe wie oben die Stunden. Wir schauen und erst die erste Stelle der Minuten an und dann die zweite.
    //Diesmal, mache ich es mit einer anderen Methode, wir wollen ja auch was lernen. 
    //Diesmal gehen wir ein anderen weg. Wir schauen diesmal, ob die LED ansein muss (Oben haben wir nach der Uhrzeit geschaut, jetzt testen wir es mal anders)

    int minutenvorne =  floor(minuten / 10); //floor rundet die Zahlen ab. d.h. wenn es nun 17 Uhr ist und ich 17 / 10 = 1,7 rausbekomme, bekomme ich dennoch nur die 1. die 7 wäre übrings das Modulo (kommt unten noch)
    
    if(minutenvorne == 1 || minutenvorne == 3 || minutenvorne == 5) {
      // 12:10 | 12:30 | 12:50
       strip.setPixelColor(8, 100, 120, 100); //LED mit den Index 8 an. 
    }
    if(minutenvorne == 2 || minutenvorne == 3) { // bei der 2 oder 3 vorne bei den minuten muss die 2 Leuchten.
      // 12:20 || 12:30
       strip.setPixelColor(7, 100, 120, 100); //LED mit den Index 7 an. 
    }
    if(minutenvorne == 4 || minutenvorne == 5) { // bei der 2 oder 3 vorne bei den minuten muss die 2 Leuchten.
      // 12:40 | 12:50
       strip.setPixelColor(6, 100, 120, 100); //LED mit den Index 6 an. 
    }

    //Der Code ist dadurch schon deutlich kleiner geworden. Das ganze können wir nun auch mit Minuten machen.
    
    int moduloMinuten = minuten % 10; // Modulo beispiel: 23 % 10 = 3 
    if(moduloMinuten == 1 || moduloMinuten == 3 || moduloMinuten == 5 || moduloMinuten == 7 || moduloMinuten == 9 ) { //z.b. 00:01 | 00:03 | 00:05 | 00:07 | 00:09 Uhr muss die LED an sein. -> Geht immer um die letzte Stelle.
      strip.setPixelColor(9, 100, 120, 100); //LED mit den Index 9 an. 
    }
    if(moduloMinuten == 2 || moduloMinuten == 3 || moduloMinuten == 6 || moduloMinuten == 7) { // z.b. 00:02 | 00:03 | 00:06  | 00:07
      strip.setPixelColor(10, 100, 120, 100); //LED mit den Index 10 an. 
    }
    if(moduloMinuten == 4 || moduloMinuten == 5 || moduloMinuten == 6 || moduloMinuten == 7) { // z.b. 00:04 | 00:05
      strip.setPixelColor(11, 100, 120, 100); //LED mit den Index 11 an. 
    }
    if(moduloMinuten == 8 || moduloMinuten == 9) { // z.b. 00:08 | 00:09
      strip.setPixelColor(12, 100, 120, 100); //LED mit den Index 12 an. 
    }

  //Anzeige der Lampe
  strip.show();

  delay(1000);
}







