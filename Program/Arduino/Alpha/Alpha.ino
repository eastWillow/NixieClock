#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <avr/wdt.h>
#define Display 1
#define A 2
#define  B  3
#define  C  4
#define  D  5
#define  Digital1  8
#define  Digital2  9
#define  Digital3  10
#define  Digital4  11
#define  Digital5  12
#define  Digital6  7
#define  PowerEN  A0
#define  EN  6
//From Library
tmElements_t tm;
//From Library
unsigned char Number[6]={5,5,5,5,5,5};
unsigned char Sleep[6]={15,36,00,15,36,15};
//Start Hour,Minute,Second,End  Hour,Minute,Second
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
  pinMode(PowerEN,OUTPUT);
  settingRTC();
  pinMode(EN,OUTPUT);
  Serial.begin(9600);
  serialWellcomeMSM();
  digitalWrite(PowerEN,HIGH);
  digitalWrite(EN,HIGH);
  wdt_enable(WDTO_1S);
}
void loop(){
 RTC.read(tm);
 /*if(tm.Second == Sleep[2] && tm.Minute == Sleep[1] && tm.Hour == Sleep[0]){
   digitalWrite(PowerEN,HIGH);
   digitalWrite(EN,HIGH);
   while(!(tm.Second == Sleep[5] && tm.Minute == Sleep[4] && tm.Hour == Sleep[3])) RTC.read(tm);;
 }*/
 //else{
   Number[0] = tm.Second % 10;
   Number[1] = tm.Second / 10;
   Number[2] = tm.Minute % 10;
   Number[3] = tm.Minute / 10;
   Number[4] = tm.Hour % 10;
   Number[5] = tm.Hour / 10;
   display();
//}
}
void BCD(unsigned char number){
  wdt_reset();
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
  digitalWrite(EN,HIGH);
  delayMicroseconds(100);
  digitalWrite(EN,LOW);
  digitalWrite(Digital1,HIGH);
  digitalWrite(Digital2,HIGH);
  digitalWrite(Digital3,HIGH);
  digitalWrite(Digital4,HIGH);
  digitalWrite(Digital5,HIGH);
  digitalWrite(Digital6,HIGH);
  delayMicroseconds(700);
}
void display(){
  digitalWrite(EN,LOW);
  digitalWrite(PowerEN,LOW);
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
  digitalWrite(Digital3,LOW);
  delay(Display);
  
  if((Number[0] % 2 != 0)){
    BCD(11);
    digitalWrite(Digital3,LOW);
    delay(Display);
    avoidGhost();
    BCD(10);
    digitalWrite(Digital4,LOW);
    delay(Display);
  }
  
  avoidGhost();
  BCD(Number[3]);
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
}
void serialEvent(){
  int Serialoption;
  digitalWrite(PowerEN,HIGH);
  digitalWrite(EN,HIGH);
  while(!Serial.available()>0);
  Serialoption = Serial.parseInt();
  Serial.print("You choice ");
  Serial.println(Serialoption);
  switch(Serialoption){
    case 1:
      settingRTC();
      break;
   case 2:
      settingRTCManual();
      break;
   case 3:
      justFun();
      break;
    /*case 4:
      settingSLP();
      break;*/
  }
    serialWellcomeMSM();
}
//From Example
bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}
void settingRTC(){
  digitalWrite(PowerEN,HIGH);
  bool parse=false;
  bool config=false;

  // get the date and time the compiler was run
  if (getTime(__TIME__)) {
    parse = true;
    // and configure the RTC with this info
    if (RTC.write(tm)) {
      config = true;
    }
  }
  Serial.print("DS1307 configured Time=");
  Serial.print(__TIME__);
}
//From Example
/*void settingSLP(){
  
  Serial.println("Please Input Start Hour");
  while(!Serial.available()>0);
  Sleep[0]=Serial.parseInt();
  Serial.println("Please Input Start Minute");
  while(!Serial.available()>0);
  Sleep[1]=Serial.parseInt();
  Serial.println("Please Input Start Second");
  while(!Serial.available()>0);
  Sleep[2]=Serial.parseInt();
  Serial.println("Please Input END Hour");
  while(!Serial.available()>0);
  Sleep[3]=Serial.parseInt();
  Serial.println("Please Input END Minute");
  while(!Serial.available()>0);
  Sleep[4]=Serial.parseInt();
  Serial.println("Please Input END Second");
  while(!Serial.available()>0);
  Sleep[5]=Serial.parseInt();
  Serial.println("Your Setting ");
  Serial.print(Sleep[0]);
  Serial.print(':');
  Serial.print(Sleep[1]);
  Serial.print(':');
  Serial.print(Sleep[2]);
  Serial.print(':');
  Serial.print('~');
  Serial.print(Sleep[3]);
  Serial.print(':');
  Serial.print(Sleep[4]);
  Serial.print(':');
  Serial.print(Sleep[5]);
  Serial.print(':');
}*/
void justFun(){
  unsigned int  loopCounter;
  Serial.println("El psy congroo");
  long worldLine=random(23456,923456);
  Serial.print("Here is : ");
  Serial.println(worldLine);
  while(loopCounter++<150){
    if(loopCounter % 9 == 0 && loopCounter< 99){
      Number[0] = worldLine % 10;
      Number[1] = worldLine % 100 / 10;
      Number[2] = worldLine % 1000 / 100;
      Number[3] = worldLine % 10000 / 1000;
      Number[4] = worldLine % 100000 / 10000;
      Number[5] = worldLine % 1000000 / 100000;
      worldLine=random(23456,123456);
    }
    digitalWrite(EN,LOW);
    digitalWrite(PowerEN,LOW);
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
    digitalWrite(Digital3,LOW);
    delay(Display);
  
    avoidGhost();
    BCD(Number[3]);
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
    
    avoidGhost();
    BCD(11);
    avoidGhost();
    digitalWrite(Digital6,LOW);
    delay(Display);
  }
}
void serialWellcomeMSM(){
  Serial.println();
  Serial.println("What Do you Want to Do?");
  Serial.println("1: Automaic time correction");
  Serial.println("2: Setting Time Manual");
  Serial.println("3: Just for Fun^^");
  //Serial.println("4: setting the sleep time");
}
void settingRTCManual(){
  wdt_disable();
  Serial.println("Please Input Hour");
  while(!Serial.available()>0);
  tm.Hour=Serial.parseInt();
  Serial.println("Please Input Minute");
  while(!Serial.available()>0);
  tm.Minute=Serial.parseInt();
  Serial.println("Please Input Second");
  while(!Serial.available()>0);
  tm.Second=Serial.parseInt();
  RTC.write(tm);
}
