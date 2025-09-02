int led = 13;
int LDR = A0;
  
void setup() {  
  pinMode(led, OUTPUT);
  pinMode(LDR, INPUT);
}  
   
void loop() {  
  int light = analogRead(LDR);
  if (light > 300) {  
    digitalWrite(led, HIGH);  
  }  
  else {  
    digitalWrite(led, LOW);  
  }  
}  
