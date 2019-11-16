#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
//#define SS_PIN 3
//#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);
int data1 = 0;
int cardid[14];
int repeat =0;
int f=6; //switch at pin 6
void setup()
{
  pinMode(2,OUTPUT);
Serial.begin(9600);
SPI.begin();
pinMode(f,INPUT);
mfrc522.PCD_Init();
Serial.println("Approximate your card to the reader...");
Serial.println();
pinMode (7, OUTPUT);
digitalWrite(7,LOW);
}
void loop()
{
  int flag = digitalRead(f);//flag from switch to change state of program 
  String content= "";
  
  // Scan for cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    //digitalWrite(2,0);
    analogWrite (A0,LOW);
    return;
  }
  // Selects a card
  if ( ! mfrc522.PICC_ReadCardSerial())
  {  //digitalWrite(2,0);
    analogWrite (A0,LOW);
    return;
  }
    
  if(flag==HIGH){
    present();
  }//if flag switch is on the program work for attendance purpose
  
  else {
    outofbound();
  }//if flag is low the the program check if student is out of classroom during class hours

}


void outofbound(){
  String content= "";
  //show UID on serial monitor
  Serial.print("Student :\n");
  for (byte i = 0; i < mfrc522.uid.size; i++)
   {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
   }
    Serial.println();
    content.toUpperCase();
    String v=content.substring(1);
  if ((v == "AD 27 78 89")||(v == "")||(v == "")||(v == "")) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("STUDENT OUT OF THE CLASSROOM/SCHOOL");
    Serial.println();
    analogWrite(A0,LOW);
    analogWrite (A2,255);
    delay(200);
    analogWrite(A0,255);
    analogWrite (A2,LOW);
    delay(200);
  }
  else if((v == "D3 88 51 A3")||(v=="D6 59 6D F8")||(v=="")){
    //digitalWrite(2,HIGH);
    Serial.println("Visitor");
    analogWrite(A0,255);
    analogWrite (A2,150);
    delay(50); 
    analogWrite (A0,LOW);
    analogWrite (A2,LOW);
    delay(900); 
  }
  else {
    Serial.println("Unknown Person");
    analogWrite (A1,255);
    analogWrite(A0,LOW);
    analogWrite (A2,255);
    delay(400);
    analogWrite(A0,255);
    analogWrite (A1, LOW);
    analogWrite (A2,LOW);
    delay(300);
  }
  if (Serial.available()>0)
  {
    int data1=Serial.read();
    Serial.println((char) data1);
    
    for (int counter =0; counter<4;counter++)
    {
      data1=Serial.read();
      delay(50);
      cardid[counter]=data1;
      //Serial.println(cardid[counter]);
    }
    repeat++;

}


}


void present(){
  String content= "";
  //show UID on serial monitor
  Serial.print("Student :\n");
  for (byte i = 0; i < mfrc522.uid.size; i++)
   {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
   }
    Serial.println();
    content.toUpperCase();
    String v=content.substring(1);
    
  if (v == "AD 27 78 89")//change the codes with the cards codes found after scanning in serial monitor
  {
    //digitalWrite(2,HIGH);
    
    Serial.println("Anjali is present");
    analogWrite (A2,150);
    analogWrite(A0,255);
    delay(50); 
    analogWrite (A2,LOW);
    analogWrite (A0,LOW);
    delay(900); 
  }
  else if((v == "D3 88 51 A3")||(v=="D6 59 6D F8")||(v=="")){
    //digitalWrite(2,HIGH);
    Serial.println("Visitor");
    analogWrite(A0,255);
    analogWrite (A2,150);
    delay(50); 
    analogWrite (A0,LOW);
    analogWrite (A2,LOW);
    delay(900); 
  }
  else if(v == "1B 01 46 0C"){
    digitalWrite(2,HIGH);
    Serial.println("Anjali Verma is present");
    analogWrite(A0,255);
    analogWrite (A2,150);
    delay(50); 
    analogWrite (A0,LOW);
    analogWrite (A2,LOW);
    delay(900); 
  }
  //else if(v == ""){
    //digitalWrite(2,HIGH);
  //                      Serial.println("Anjali Verma is present");
  //                      analogWrite(A0,255);
  //                      analogWrite (A2,150);
  //                      delay(50); 
  //                      analogWrite (A0,LOW);
  //                      analogWrite (A2,LOW);
  //                      delay(900); 
  //}
  else {
    Serial.println("Unknown Person");
    analogWrite (A1,255);
    analogWrite(A0,LOW);
    analogWrite (A2,255);
    delay(400);
    analogWrite(A0,255);
    analogWrite (A1, LOW);
    analogWrite (A2,LOW);
    delay(300);
  }
  if (Serial.available()>0)
  {
    int data1=Serial.read();
    Serial.println((char) data1);
    
    for (int counter =0; counter<4;counter++)
    {
      data1=Serial.read();
      delay(50);
      cardid[counter]=data1;
      //Serial.println(cardid[counter]);
    }
    repeat++;
    
  }
}
