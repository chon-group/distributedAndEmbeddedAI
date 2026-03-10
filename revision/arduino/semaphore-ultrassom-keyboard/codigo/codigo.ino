#define RP 2
#define YP 3
#define GP 4
#define RS 5
#define YS 6
#define GS 7
#define energisaLinha1 8
#define btnAsterisco   9

void setup(){
    pinMode(RP,OUTPUT);
    pinMode(YP,OUTPUT);
    pinMode(GP,OUTPUT);
    pinMode(RS,OUTPUT);
    pinMode(YS,OUTPUT);
    pinMode(GS,OUTPUT);
    pinMode(energisaLinha1,OUTPUT);
    pinMode(btnAsterisco,INPUT);
    digitalWrite(energisaLinha1,HIGH);
    liberaPrincipal();
}

void loop(){
    if(isPedestre()){
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

bool isPedestre(){
    if(digitalRead(btnAsterisco)){ return true;}
    else {return false;}
}