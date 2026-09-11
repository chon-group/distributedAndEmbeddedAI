#define RP 		2
#define YP 		3
#define GP 		4
#define RS 		5
#define YS 		6
#define GS 		7
#define btn		8
#define Led 	13
#define echoPin 9
#define trigPin 10

#include <HCSR04.h>
HCSR04 hc(trigPin, echoPin); 

void setup(){
    pinMode(Led,OUTPUT);
    pinMode(RP,OUTPUT);
    pinMode(YP,OUTPUT);
    pinMode(GP,OUTPUT);
    pinMode(RS,OUTPUT);
    pinMode(YS,OUTPUT);
    pinMode(GS,OUTPUT);
    pinMode(btn,INPUT);
	liberaPrincipal();
}


void loop(){
 	if(apertou() || veiculo()){
		liberaSecundaria();
		delay(60000);
		liberaPrincipal();
	}
}


void liberaPrincipal(){
    /* secundaria amarelo primeiro */
    digitalWrite(RS,LOW);
    digitalWrite(YS,HIGH);
    digitalWrite(GS,LOW);
    delay(10000);
    /* secundaria vermelho */
    digitalWrite(RS,HIGH);
    digitalWrite(YS,LOW);
    digitalWrite(GS,LOW);
    /* principal verde */
    digitalWrite(RP,LOW);
    digitalWrite(YP,LOW);
    digitalWrite(GP,HIGH);
}

void liberaSecundaria(){
    /* primaria amarelo primeiro */
    digitalWrite(RP,LOW);
    digitalWrite(YP,HIGH);
    digitalWrite(GP,LOW);
    delay(10000);
    /* primaria vermelho */
    digitalWrite(RP,HIGH);
    digitalWrite(YP,LOW);
    digitalWrite(GP,LOW);
    /* secundaria verde */
    digitalWrite(RS,LOW);
    digitalWrite(YS,LOW);
    digitalWrite(GS,HIGH);
}

bool apertou(){
	if(digitalRead(btn)){ /* por padrao chega 1 */
		digitalWrite(Led,HIGH); 
		return false;
	}else{
		digitalWrite(Led,LOW);
		return true;
	}  /* quando aperta chega 0 */
}


long quandoParou = 0;
bool inicioucontagem = false;

bool veiculo(){
   float distancia = hc.dist();
   if(distancia < 100){
	digitalWrite(Led,LOW);
	delay(100);
	digitalWrite(Led,HIGH);
		if(inicioucontagem){
			long agora = millis();
			if(agora-quandoParou > 5000){
				inicioucontagem  = false;
				digitalWrite(Led,LOW);				
				return true;
			}else{
				return false; /* ainda não deu 5 segundos */
			}
		}else{
			inicioucontagem = true;
			quandoParou = millis();
		}
	}else{
		inicioucontagem = false;
	}
	return false;
}
