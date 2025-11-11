int led = 3;   
int button = 2;         

int mode = 0;           
bool ledState = true;   
unsigned long lastBlink = 0; 

void setup() {
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);   
  digitalWrite(led, HIGH);        
}

void loop() {
  if (digitalRead(button) == LOW) {
    delay(50); 
    if (digitalRead(button) == LOW) {
      mode = mode + 1;            
      if (mode > 3) mode = 0;      
      while (digitalRead(button) == LOW); 
      delay(100); 
    }
  }
  
  if (mode == 0) {
    digitalWrite(led, HIGH);  
  }
  else if (mode == 1) {
    blinkLED(1000);           
  }
  else if (mode == 2) {
    blinkLED(500);            
  }
  else if (mode == 3) {
    blinkLED(200);           
  }
}

void blinkLED(int interval) {
  unsigned long now = millis();
  if (now - lastBlink >= interval) {
    lastBlink = now;
    ledState = !ledState;            
    digitalWrite(led, ledState);     
  }
}
