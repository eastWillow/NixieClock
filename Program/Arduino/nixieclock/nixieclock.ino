int enablePin = 2;
int inputData=0;
int Switch;
int numbers;
void setup(){
  Serial.begin(9600);
  pinMode(enablePin,OUTPUT);
  digitalWrite(enablePin,HIGH);
  Switch = 1;
}
void loop(){
  DDRB = ~numbers;
}
void serialEvent(){
    if(Serial.available() >0){
    inputData=Serial.parseInt();
    if(inputData <10){
    Serial.print("I received: ");
    Serial.println(inputData);
    numbers =inputData;
    }
    else{
      Serial.println("You Input More Than 9 Switch!");
      if(Switch == 1) {
        digitalWrite(enablePin,LOW);
        Switch = 0;
      }
      else {
        digitalWrite(enablePin,HIGH);
        Switch = 1;
      }
    }
  }
}
