#include <SoftwareSerial.h>
#include "Arduino.h"
#define kontroll_led 2 // Ausgang zur Kontroll-LED
#define ntc 3 // NTC-Wert
//#define mosfet_out 1; // Spannungsüberwachung
#define taster 0 // Taster Eingabe
#define mosfet_gate 4 // Gate Mosfet Heizdecke

//Variablen des Zwischenspeichers:
int buttonPushCounter = 0;   //Zählt Tastendrücke
int buttonState = 0;         //Aktueller Tastenstatus
int lastButtonState = 0;     //Vorheriger Tastenstatus
unsigned long previousMillis = 0; //Speichert vergangene Zeit
const long interval = 1000; //Intervall wo Tasterdrücke registriert wurden

//long button
const int LONG_PRESS_TIME  = 1000; // 1000 milliseconds

// Variables will change:
int lastState = LOW;  // the previous state from the input pin
int currentState;     // the current reading from the input pin
unsigned long pressedTime  = 0;
bool isPressing = false;
bool isLongDetected = false;


int R = 100000;                                             // Spannungsteiler, fester Widerstand
float Rn = 100000;                                         // gemessen (Ohm)
float Tn = 25;                                            // gemessen (°C)
float B = 4450;

void setup() {
  Serial.begin(9600);
  pinMode(kontroll_led, OUTPUT); 
  pinMode(ntc, INPUT_PULLUP); 
  pinMode(taster, INPUT_PULLUP);
 // pinMode(mosfet_out, INPUT); 
  pinMode(mosfet_gate, OUTPUT); 
 analogWrite(mosfet_gate, 0); // Aus
}

void loop() {
    // read the state of the switch/button:
  currentState = digitalRead(taster);

 

  if(lastState == HIGH && currentState == LOW) {        // button is pressed
    pressedTime = millis();
    isPressing = true;
    isLongDetected = false;
  } else if(lastState == LOW && currentState == HIGH) { // button is released
    isPressing = false;
  }

  if(isPressing == true && isLongDetected == false) {
    long pressDuration = millis() - pressedTime;

    if( pressDuration > LONG_PRESS_TIME ) {
      digitalWrite(kontroll_led, LOW);
	    analogWrite(mosfet_gate, 0); // aus
      isLongDetected = true;
    }
  }

  // save the the last state
  lastState = currentState;

  // save the the last state
  lastState = currentState; 
  unsigned long currentMillis = millis(); //Zählt Millisekunden
  buttonState = digitalRead(taster); //Taster an buttonPin wird gelesen und in Zwischenspeicher buttonState gespeichert
 
  if (buttonState != lastButtonState) { //Wenn buttonState nicht gleich lastButtonState, dann...
    
    if (buttonState == LOW) { //Wenn buttonState gleich gedrückt, dann...
      buttonPushCounter ++; //buttonPushCounter +1
      lastButtonState = buttonState; //Speichert buttonState in lastButtonState
      previousMillis = currentMillis; //Speichere jetzige Millisekunden in previousMillis
      delay(50);
    }
  else {
      lastButtonState = buttonState;
    }
  }

  if (currentMillis - previousMillis >= interval && buttonState == lastButtonState) { //Wenn gezählte Millisekunden minus vorherige Millisekunden (gespeicherte, vergangene Zeit) grösser/gleich interval ist und buttonState gleich lastButtonState ist, dann...
   
    
    switch (buttonPushCounter) {
  case 1:
      digitalWrite(kontroll_led, HIGH); //Schalte kontroll_led an
      delay(200);
      digitalWrite(kontroll_led, LOW);
	    analogWrite(mosfet_gate, 65); // Stufe 1
    break;
  case 2:
      digitalWrite(kontroll_led, HIGH); //Schalte kontroll_led an
      delay(200);
      digitalWrite(kontroll_led, LOW);
      delay(200);
      digitalWrite(kontroll_led, HIGH);
      delay(200);
      digitalWrite(kontroll_led, LOW);
	    analogWrite(mosfet_gate, 130); // Stufe 2
    break;
    case 3:
      digitalWrite(kontroll_led, HIGH); //Schalte kontroll_led an
      delay(200);
      digitalWrite(kontroll_led, LOW);
      delay(200);
      digitalWrite(kontroll_led, HIGH);
      delay(200);
      digitalWrite(kontroll_led, LOW);
      delay(200);
      digitalWrite(kontroll_led, HIGH);
      delay(200);
      digitalWrite(kontroll_led, LOW);
	    analogWrite(mosfet_gate, 200); // Stufe 3
    break;
    case 4:
      digitalWrite(kontroll_led, HIGH); //Schalte kontroll_led an
      delay(200);
      digitalWrite(kontroll_led, LOW);
      delay(200);
      digitalWrite(kontroll_led, HIGH);
      delay(200);
      digitalWrite(kontroll_led, LOW);
      delay(200);
      digitalWrite(kontroll_led, HIGH);
      delay(200);
      digitalWrite(kontroll_led, LOW);
      delay(200);
      digitalWrite(kontroll_led, HIGH);
      delay(200);
      digitalWrite(kontroll_led, LOW);
	    analogWrite(mosfet_gate, 255); // Stufe 4
    break;
  default:
    float Analog_Wert = (float)analogRead(ntc);           // analogen Wert A0 auslesen               
    float U_ntc = (5.0 * Analog_Wert) / 1023;             // Spannung
    float R_ntc = (U_ntc * Rn) / (3.3 - U_ntc);           // Widerstand
                                                          // Temperatur-Berechnung
        // Rt = Rn * e hoch B*(1/T - 1/Tn)                // Ausgangsformel
        // T = 1 / [(log(Rt/Rn)/B + 1/Tn] - 273,15        // umgestellt in °K
        // Tnk = 26,2 + 273,15                            // °K
    float A1 = log(R_ntc / Rn) / B;
    float A2 = A1 + 1 / (Tn + 273.15);
    float T = (1 / A2) - 273.15;
    //Serial.println(R_ntc); 
    //Serial.println(U_ntc); 
    //Serial.println(Analog_Wert); 
    Serial.println(T);
    delay(100);
    break;
}
   buttonPushCounter = 0; //Setze buttonPushCounter auf 0


  }
  
 // val = analogRead(analogPin); // Liest den Wert vom Pin ein
 // analogWrite(kontroll_led, val / 4); // analogRead: Werte von 0 bis 1023, analogWrite: Werte von 0 bis 255
}
