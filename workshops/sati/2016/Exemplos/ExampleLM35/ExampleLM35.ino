int LM35 = A5;
int ledRed = 12, ledBlue = 11;
double temperature = 0;

void setup() {
  pinMode(LM35, INPUT_PULLUP);
  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  temperature = (analogRead(LM35)*10)*0.00488759;
  if (temperature > 25) {
    digitalWrite (ledRed,HIGH);
    digitalWrite (ledBlue,LOW);
  } else if (temperature < 20) {
    digitalWrite (ledRed,LOW);
    digitalWrite (ledBlue,HIGH);
  }else {
    digitalWrite (ledRed,LOW);
    digitalWrite (ledBlue,LOW);
  }
  Serial.println(temperature);
  delay(1000);
}
