// Time needed for PIR sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 20;        
int pirState = 0;
int lastPirState = 0;

// Sensor outputs a low impulse
long unsigned int lowIn;         

// Minimum time in milliseconds the sensor must be low 
// before we consider all motion to be "stopped"
long unsigned int pause = 150;  

boolean lockLow = true;
boolean takeLowTime;  

// PIR output pin
int pirPin = 2;

void setup(){
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  digitalWrite(pirPin, LOW);

  // Give sensor time to calibrate

  for(int i = 0; i < calibrationTime; i++){
    Serial.print(".");
    delay(1000);
  }
  
  Serial.println("+");
  delay(50);
}

void loop(){
  pirState = digitalRead(pirPin);
  
  if(pirState == HIGH){
    delay(pause);

    if(lastPirState == LOW){
      // Begin motion
      Serial.println("+");
      lastPirState = HIGH;
    }
  } else {     
    if (lastPirState == HIGH){
      // End motion
      Serial.println("-");
      lastPirState = LOW;
    }
  }
}