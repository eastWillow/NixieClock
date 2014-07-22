int Display = 1;
int Numbers;
int A = 2;
int B = 3;
int C = 4;
int D = 5;
int Digital1 = 8;
int Digital2 = 9;
int Digital3 = 10;
int Digital4 = 11;
int Digital5 = 12;
int Digital6 = 7;
int EN = 6;
int Number[6]={5,5,5,5,5,5};
int lastTime;
int currentTime;
void setup(){
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
  pinMode(Digital1,OUTPUT);
  pinMode(Digital2,OUTPUT);
  pinMode(Digital3,OUTPUT);
  pinMode(Digital4,OUTPUT);
  pinMode(Digital5,OUTPUT);
  pinMode(Digital6,OUTPUT);
  pinMode(EN,OUTPUT);
  Serial.begin(9600);
  Serial.println("Please Input A Number Below 100");
}
void loop(){
  avoidGhost();
  BCD(Number[0]);
  avoidGhost();
  digitalWrite(Digital1,LOW);
  delay(Display);
  avoidGhost();
  BCD(Number[1]);
  avoidGhost();
  digitalWrite(Digital2,LOW);
  delay(Display);
  avoidGhost();
  BCD(Number[2]);
  avoidGhost();
  digitalWrite(Digital3,LOW);
  delay(Display);
  avoidGhost();
  BCD(Number[3]);
  avoidGhost();
  digitalWrite(Digital4,LOW);
  delay(Display);
  avoidGhost();
  BCD(Number[4]);
  avoidGhost();
  digitalWrite(Digital5,LOW);
  delay(Display);
  avoidGhost();
  BCD(Number[5]);
  avoidGhost();
  digitalWrite(Digital6,LOW);
  delay(Display);
  currentTime = millis();
  if((currentTime - lastTime) > 10){
      if(Numbers < 1000000) Numbers++;
      else Numbers = 0;
      Number[0] = Numbers % 10;
      Number[1] = Numbers % 10;
      Number[2] = Numbers % 10;
      Number[3] = Numbers % 10;
      Number[4] = Numbers % 10;
      Number[5] = Numbers % 10;
      /*Number[1] = Numbers % 100 / 10;
      Number[2] = Numbers % 1000 / 100;
      Number[3] = Numbers % 10000 / 1000;
      Number[4] = Numbers % 100000 / 10000;
      Number[5] = Numbers % 1000000 / 100000;*/
      lastTime = currentTime;
  }
}
void serialEvent(){
    if(Serial.available() >0){
    Numbers=Serial.parseInt();
    if(Numbers <10000){
    Serial.print("I received: ");
    Serial.println(Numbers);
    Serial.println("Please Input A Number Below 100");
    }
    else{
      Serial.println("Error!, Please Try Again:");
    }
  }
}
void BCD(int number){
  switch(number){
    case 0:
    digitalWrite(A,LOW);
    digitalWrite(B,LOW);
    digitalWrite(C,LOW);
    digitalWrite(D,LOW);
    break;
    case 1:
    digitalWrite(A,HIGH);
    digitalWrite(B,LOW);
    digitalWrite(C,LOW);
    digitalWrite(D,LOW);
    break;
    case 2:
    digitalWrite(A,LOW);
    digitalWrite(B,HIGH);
    digitalWrite(C,LOW);
    digitalWrite(D,LOW);
    break;
    case 3:
    digitalWrite(A,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(C,LOW);
    digitalWrite(D,LOW);
    break;
    case 4:
    digitalWrite(A,LOW);
    digitalWrite(B,LOW);
    digitalWrite(C,HIGH);
    digitalWrite(D,LOW);
    break;
    case 5:
    digitalWrite(A,HIGH);
    digitalWrite(B,LOW);
    digitalWrite(C,HIGH);
    digitalWrite(D,LOW);
    break;
    case 6:
    digitalWrite(A,LOW);
    digitalWrite(B,HIGH);
    digitalWrite(C,HIGH);
    digitalWrite(D,LOW);
    break;
    case 7:
    digitalWrite(A,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(C,HIGH);
    digitalWrite(D,LOW);
    break;
    case 8:
    digitalWrite(A,LOW);
    digitalWrite(B,LOW);
    digitalWrite(C,LOW);
    digitalWrite(D,HIGH);
    break;
    case 9:
    digitalWrite(A,HIGH);
    digitalWrite(B,LOW);
    digitalWrite(C,LOW);
    digitalWrite(D,HIGH);
    break;
    case 10:
    digitalWrite(A,LOW);
    digitalWrite(B,HIGH);
    digitalWrite(C,LOW);
    digitalWrite(D,HIGH);
    break;
    case 11:
    digitalWrite(A,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(C,LOW);
    digitalWrite(D,HIGH);
    break;
  }
}
void avoidGhost(){
  digitalWrite(Digital1,HIGH);
  digitalWrite(Digital2,HIGH);
  digitalWrite(Digital3,HIGH);
  digitalWrite(Digital4,HIGH);
  digitalWrite(Digital5,HIGH);
  digitalWrite(Digital6,HIGH);
  delay(1);
}
