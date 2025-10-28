const int PIN_BUTTON = 2;
const int PIN_R = 9;   
const int PIN_G = 10;
const int PIN_B = 11;

const bool LED_ANODE = true;

int mood = 10;
unsigned long lastPress = 0;
unsigned long lastDecay = 0;

void setup() {
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  setLED(mood);
}

void loop() {
  unsigned long now = millis();

  if (digitalRead(PIN_BUTTON) == LOW) {
    mood = min(20, mood + 1);
    lastPress = now;
    setLED(mood);
    delay(200);
  }

  if (now - lastPress > 5000 && now - lastDecay > 1000 && mood > 0) {
    mood--;
    lastDecay = now;
    setLED(mood);
  }
}

void setLED(int m) {
  int r, g, b;

  if (m <= 10) { 
    r = map(m, 0, 10, 255, 0);
    g = map(m, 0, 10, 0, 255);
    b = 0;
  } else {       
    r = 0;
    g = map(m, 10, 20, 255, 0);
    b = map(m, 10, 20, 0, 255);
  }

  if (LED_ANODE) {
    r = 255 - r;
    g = 255 - g;
    b = 255 - b;
  }

  analogWrite(PIN_R, r);
  analogWrite(PIN_G, g);
  analogWrite(PIN_B, b);
}

