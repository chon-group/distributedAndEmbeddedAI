#include <Javino.h>

Javino javino;
int led = 13;
int LDR = A0;
int LM35 = A5;
int light = 0;
int ledRed = 12, ledBlue = 11;
double tempSensor = 0;  
String msg = "";
char buffer[25];

void setup() {  
  pinMode(led, OUTPUT);
  pinMode(LDR, INPUT);
  pinMode(LM35, INPUT_PULLUP);
  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  Serial.begin(9600);
}  
   
void loop() {  
  if(javino.availablemsg()){
    msg = javino.getmsg();  
  }
 
  if (msg == "getPercepts") {
    getPercepts();
  }

  if (msg == "lightOn") {
    lightOn();
  }
 
  if (msg == "lightOff") {
    lightOff();
  }
 
  if (msg == "hotSignal") {
    hotSignal();
  }
 
  if (msg == "coldSignal") {
    coldSignal();
  }
 
  if (msg == "coolSignal") {
    coolSignal();
  } 
  msg="";
}

void getPercepts () {
  String percepts = getLight()+getTemp();
  javino.sendmsg(percepts);
}

String getLight() {
  light = analogRead(LDR);
  return "light("+String(light)+");";
}

String getTemp() {
  tempSensor = (analogRead(LM35)*10)*0.00488759;
  char tempString[10];  
  dtostrf(tempSensor,3,2,tempString);
  return "temperature("+String(tempString)+");"; }

void lightOn() {
  digitalWrite(led, HIGH); }

void lightOff() {  
  digitalWrite(led, LOW); }

void hotSignal() {
  digitalWrite (ledRed,HIGH);
  digitalWrite (ledBlue,LOW); }

void coldSignal() {
  digitalWrite (ledRed,LOW);
  digitalWrite (ledBlue,HIGH); }

void coolSignal() {
  digitalWrite (ledRed,LOW);
  digitalWrite (ledBlue,LOW); }


