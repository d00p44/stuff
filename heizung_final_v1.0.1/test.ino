#define BUTTON_PIN 8     // PB0
#define LED_PIN 2        // PB2
#define PWM_PIN 5        // PB5
#define TEMP_PIN A1      // PB1

#define PWM_OFF 0
#define PWM_25 64        // 25% of 255
#define PWM_50 128       // 50% of 255
#define PWM_75 192       // 75% of 255
#define PWM_100 255      // 100% of 255

int pwmLevels[] = {PWM_OFF, PWM_25, PWM_50, PWM_75, PWM_100};
int currentLevel = 0;
unsigned long lastPressTime = 0;
unsigned long buttonPressDuration = 0;
unsigned long lastBlinkTime = 0;
unsigned long lastTempCheckTime = 0;
bool buttonState = LOW;
bool lastButtonState = LOW;

void setup() {
  Serial.begin(9600);
  currentLevel = 0;
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);
  analogWrite(PWM_PIN, pwmLevels[currentLevel]);
  }

void loop() {
  unsigned long currentTime = millis();
  
  // Button handling
  buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW && lastButtonState == HIGH) { // Button pressed
    lastPressTime = currentTime;
    buttonPressDuration = 0;
  } else if (buttonState == LOW) { // Button held down
    buttonPressDuration = currentTime - lastPressTime;
  } else if (buttonState == HIGH && lastButtonState == LOW) { // Button released
    if (buttonPressDuration < 2000) {
      currentLevel = (currentLevel + 1);
      if (currentLevel > 4) {currentLevel = 0;}
      analogWrite(PWM_PIN, pwmLevels[currentLevel]);
    } else {
      currentLevel = 0;
      analogWrite(PWM_PIN, pwmLevels[currentLevel]);
    }
  }
  lastButtonState = buttonState;
  
  // LED Blink handling
  if (currentTime - lastBlinkTime >= 5000) {
    lastBlinkTime = currentTime;
    for (int i = 0; i < currentLevel; i++) {
      digitalWrite(LED_PIN, LOW);
      delay(200);
      digitalWrite(LED_PIN, HIGH);
      delay(200);
    }
  }
  
  // Temperature handling
  if (currentTime - lastTempCheckTime >= 5000) {
    lastTempCheckTime = currentTime;
    int sensorValue = analogRead(TEMP_PIN);
    float voltage = sensorValue * (5.0 / 1023.0);
    float resistance = (5.0 - voltage) * 10000 / voltage;
    float temperature = 1.0 / (log(resistance / 10000) / 3435 + 1.0 / 298.15) - 273.15;
    Serial.println(temperature);
    Serial.println(currentLevel);
    if (temperature > 95.0) {
      currentLevel = 0;
      analogWrite(PWM_PIN, pwmLevels[currentLevel]);
    }
  }
}
