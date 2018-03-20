

void setup() {
  // put your setup code here, to run once:
Serial.begin(38400);
pinMode(A2,OUTPUT);
pinMode(A3,OUTPUT);
pinMode(A4,OUTPUT);
pinMode(A5,OUTPUT);
 // mySerial.begin(9600);

for(int i= 2;i<=13;i++)
{
  if((i%2)==0)
  {
    pinMode(i,OUTPUT);
    }
    else
    {
       pinMode(i,INPUT);
   
      }
  }
}

int c,d,e;
void front(int speedd)
{
  analogWrite(A2,0);
 analogWrite(A3,speedd);
 analogWrite(A4,speedd);
 analogWrite(A5,0);

}

void back(int speedd)
{ 
  
 analogWrite(A3,0);
 analogWrite(A2,speedd);
 analogWrite(A5,speedd);
 analogWrite(A4,0);
 }
  
void left()
{
   int narasu = checkEcho(10,11);
   if(narasu>6)
   {
 analogWrite(A4,0);
 analogWrite(A5,255); 
 analogWrite(A2,0);
 analogWrite(A3,255);
 delay(400);
 stopp(); }
  }
   
void right()
{
     int narasu = checkEcho(12,13);
   if(narasu>6)
   {
  analogWrite(A2,255);
 analogWrite(A3,0);
 analogWrite(A4,255);
 analogWrite(A5,0);
 delay(400);
 stopp(); } 
  }
  void stopp()
{analogWrite(A2,0);
 analogWrite(A3,0);
 analogWrite(A4,0);
 analogWrite(A5,0); 
  }


 int checkEcho(int i,int j)
 {
  long duration,inches,cm;
  pinMode(i,OUTPUT);
  digitalWrite(i,LOW);
  delayMicroseconds(2);
  digitalWrite(i,HIGH);
  delayMicroseconds(10);
  digitalWrite(i,LOW);  
  pinMode(j,INPUT);
  duration=pulseIn(j,HIGH);
  //inches=microtoin(duration);
  cm=microtocm(duration);
     
  return cm;
  
  }
  
long microtocm(long ms) 
{
  return ms/29/2;
  } 
    char p='1';
void loop() {
  if(p=='b')
   {
      int l=checkEcho(8,9);
    
      if(l<2)
       {     front(255 );
             //digitalWrite(8,HIGH);
             delay(500);
            
          stopp();
          p='s';
      }   
      else
     {
     back(130);
     }
    
    
    }
    
    
 if(Serial.available())
 {
   char d = Serial.read();
   if(d!=p)  
     p=d;
    
  if(p=='f')
  {
    Serial.write("Move in front");
    front(255);
 
    }
    else if(p=='b')
    {Serial.write("Move in back");
      back(130);
      }
      
    else if(p=='l')
    {Serial.write("Move in left");
      left();
      }
      
    else if(p=='r')
    {Serial.write("Move in right");
      right();
      }
      
    else if(p=='s')
    {Serial.write("stop");
      stopp();
      }
  }
  // put your main code here, to run repeatedly:

}
