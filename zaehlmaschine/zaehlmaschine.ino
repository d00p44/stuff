/*
  This code measures the speed of a motor connected to an Arduino Uno 
  using a speed sensor module.

  Board: Arduino Uno R4 (or R3)
  Component: Speed Sensor Module
*/

// Define the sensor and motor pins
const int sensorPin = 11;
const int motorB_1A = 9;
const int motorB_2A = 10;

// Define variables for measuring speed
unsigned long start_time = 0;
unsigned long end_time = 0;
int steps = 0;
float steps_old = 0;
float temp = 0;
float rps = 0;

void setup() {
  Serial.begin(9600);

  pinMode(sensorPin, INPUT);   // set sensor pin as input
pinMode(10, INPUT);   // set sensor pin as input
}

void loop() {
 

  // measure steps taken within 1 second

    if (digitalRead(sensorPin)) {
      steps = steps + 1;
      while (digitalRead(sensorPin))
        ;
    }
    if (digitalRead(10) == HIGH) {
      steps = 0;
        
    }
  

  // print the revolutions per second
  Serial.print("rps:");
  Serial.println(steps);
}