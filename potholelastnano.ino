#include <Servo.h>
Servo myservo;

int left1 = 3, left2 = 2, right1 = 6, right2 = 5;
int echo = 8, trigger = 7;
long duration = 0,distance = 0;

int leveling_M1=10,leveling_M2=11;

unsigned long current_millis = 0, data_millis = 0;
int data_interval = 1000;


void setup() 
{
  Serial.begin(9600);
  Serial.println("POTHOLE");
  pinMode(left1,OUTPUT);
  pinMode(left2,OUTPUT);
  pinMode(right1,OUTPUT);
  pinMode(right2,OUTPUT);

  pinMode(leveling_M1,OUTPUT);
  pinMode(leveling_M2,OUTPUT);

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  myservo.attach(9);

  myservo.write(90);                  
  delay(15); 
}

void loop() 
{
   digitalWrite(trigger, LOW);
   delayMicroseconds(2);
   digitalWrite(trigger, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigger, LOW);
   duration = pulseIn(echo, HIGH);
   distance = duration/29/2;

   current_millis = millis();

   if(current_millis - data_millis >= data_interval)
   {
    data_millis = current_millis;
    Serial.println("*U" + String(distance) + "*" );
   }


  if (Serial.available()>0)
  {
    char c = Serial.read();
    if (c == 'F')
    {
      digitalWrite(left1,HIGH);
      digitalWrite(left2,LOW);
      digitalWrite(right1,HIGH);
      digitalWrite(right2,LOW);
    }
    else if (c == 'B')
    {
      digitalWrite(left1,LOW);
      digitalWrite(left2,HIGH);
      digitalWrite(right1,LOW);
      digitalWrite(right2,HIGH);
    }
    else if (c == 'L')
    {
      digitalWrite(left1,LOW);
      digitalWrite(left2,HIGH);
      digitalWrite(right1,HIGH);
      digitalWrite(right2,LOW);
    }
    else if (c == 'R')
    {
      digitalWrite(left1,HIGH);
      digitalWrite(left2,LOW);
      digitalWrite(right1,LOW);
      digitalWrite(right2,HIGH);
    }
    else if (c == 'S')
    {
      digitalWrite(left1,LOW);
      digitalWrite(left2,LOW);
      digitalWrite(right1,LOW);
      digitalWrite(right2,LOW);
    }

    else if (c == 'U')
    {
      digitalWrite(leveling_M1,HIGH);
      digitalWrite(leveling_M2,LOW);

      delay(200);
      
      digitalWrite(leveling_M1,LOW);
      digitalWrite(leveling_M2,LOW);
    }

     else if (c == 'D')
    {
      digitalWrite(leveling_M1,LOW);
      digitalWrite(leveling_M2,HIGH);

      delay(200);
      
      digitalWrite(leveling_M1,LOW);
      digitalWrite(leveling_M2,LOW);
    }

    else if (c == 'C')
    {
      myservo.write(90);                  
      delay(50); 
    }
     else if (c == 'O')
    {
      myservo.write(0);                  
      delay(50); 
    }

     else if (c == 'Z')
    {
      if(distance>6)
      {
        myservo.write(0);                  
        delay(50); 
        digitalWrite(leveling_M1,LOW);
        digitalWrite(leveling_M2,HIGH);

        delay(2000);
      
        digitalWrite(left1,HIGH);
        digitalWrite(left2,LOW);
        digitalWrite(right1,HIGH);
        digitalWrite(right2,LOW);

        delay(2000);

        digitalWrite(leveling_M1,LOW);
        digitalWrite(leveling_M2,LOW);
        
        digitalWrite(left1,LOW);
        digitalWrite(left2,LOW);
        digitalWrite(right1,LOW);
        digitalWrite(right2,LOW);

        myservo.write(90);                  
        delay(50);  


        digitalWrite(leveling_M1,HIGH);
        digitalWrite(leveling_M2,LOW);
  
        delay(3000);
        
        digitalWrite(leveling_M1,LOW);
        digitalWrite(leveling_M2,LOW);
      
      
      }
    }
  }

}