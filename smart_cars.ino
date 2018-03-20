
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); //RX, TX

void setup() {
  // put your setup code here, to run once:
Serial.begin(38400);
pinMode(A2,OUTPUT);
pinMode(A3,OUTPUT);
pinMode(A4,OUTPUT);
pinMode(A5,OUTPUT);
}


void front()
{
  analogWrite(A2,0);
 analogWrite(A3,255);
 analogWrite(A4,255);
 analogWrite(A5,0);

}

void back(int speedd)
{ 
  
 analogWrite(A3,0);
 analogWrite(A2,255);
 analogWrite(A5,255);
 analogWrite(A4,0);
 }
  
void left()
{
 analogWrite(A4,0);
 analogWrite(A5,255); 
 analogWrite(A2,0);
 analogWrite(A3,255);

  }
   
void right()
{
  analogWrite(A2,255);
 analogWrite(A3,0);
 analogWrite(A4,255);
 analogWrite(A5,0);

  
  }
  void stopp()
{analogWrite(A2,0);
 analogWrite(A3,0);
 analogWrite(A4,0);
 analogWrite(A5,0); 
  }
void loop()
{
  front();
  delay(1000);
  right();
  delay(300);
  front();
  delay(2000);
  left();
  delay(300);
  front();

}

