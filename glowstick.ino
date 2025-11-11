int pinR = 11;
int pinG = 10;
int pinB = 9;
int button = 2;

int mode = 0; 
int colorIndex = 0;

unsigned long buttonTime = 0;
bool buttonPressed = false;
unsigned long lastChange = 0;
bool ledOn = true;


int brightness = 0;
int step = 3;               
bool increasing = true;
unsigned long lastBreathUpdate = 0; 
const unsigned long breathInterval = 20; 


int colors[][3] = {
  {255,255,255},
  {255,0,0},
  {0,255,0},
  {0,0,255},
  {255,0,255},
  {255,255,0}
};
int colorCount = 6;

void setup() {
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  setColor(colors[colorIndex]);
}

void loop() {
  unsigned long now = millis();
  bool reading = digitalRead(button);


  if (reading == LOW && !buttonPressed) {
    buttonPressed = true;
    buttonTime = now;
  }
  if (reading == HIGH && buttonPressed) {
    unsigned long pressLength = now - buttonTime;
    buttonPressed = false;

    if (pressLength > 800) {
      mode = (mode + 1) % 3; 
      Serial.print("Mode: "); Serial.println(mode);
    } else {
      colorIndex = (colorIndex + 1) % colorCount;
      Serial.print("Color: "); Serial.println(colorIndex);
    }
  }

  if (mode == 0) {
    setColor(colors[colorIndex]);
  }
  else if (mode == 1) {
    // blink
    if (now - lastChange > 500) {
      lastChange = now;
      ledOn = !ledOn;
    }
    if (ledOn) setColor(colors[colorIndex]);
    else setColorOff();
  }
  else if (mode == 2) {
    if (now - lastBreathUpdate > breathInterval) {
      lastBreathUpdate = now;

      if (increasing) brightness += step;
      else brightness -= step;

      if (brightness >= 255) increasing = false;
      if (brightness <= 0) increasing = true;

      int r = colors[colorIndex][0] * brightness / 255;
      int g = colors[colorIndex][1] * brightness / 255;
      int b = colors[colorIndex][2] * brightness / 255;

      analogWrite(pinR, r);
      analogWrite(pinG, g);
      analogWrite(pinB, b);
    }
  }
}

void setColor(int col[3]) {
  analogWrite(pinR, col[0]);
  analogWrite(pinG, col[1]);
  analogWrite(pinB, col[2]);
}

void setColorOff() {
  analogWrite(pinR, 0);
  analogWrite(pinG, 0);
  analogWrite(pinB, 0);
}

