/* Connection pins:

Arduino       MQ-135
  A0            A0
 +5V            VCC
 GND            GND
 
*/
int input1 = 3;
int input2 = 4;
int input3 = 5;
int input4= 6;

int inputPin = 11;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

int ledPin = 12;    //Turn on LED

char junk;
#include "MQ135.h"
int analogPin = 10;
MQ135 gasSensor = MQ135(analogPin);
#define RZERO 310 // 76.63
int i = 0; 
double result;
double rzero;

void setup() {
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(input3, OUTPUT);
  pinMode(input4, OUTPUT);
  pinMode(inputPin, INPUT);     // declare sensor as input
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //Bot Control<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  if(Serial.available()>0){
  
    junk = Serial.read();
    
    if(junk == 's'){      //for going backward
      digitalWrite(input1,LOW); 
      digitalWrite(input2,HIGH); 
      digitalWrite(input3,LOW); 
      digitalWrite(input4,HIGH);
      delay(100);
    }
    if(junk == 'w'){   //for going forword
      digitalWrite(input1,HIGH); 
      digitalWrite(input2,LOW); 
      digitalWrite(input3,HIGH); 
      digitalWrite(input4,LOW);   
      delay(100);
    }

      
    if(junk == 'd'){   //for going rigft
      digitalWrite(input1,HIGH);
      digitalWrite(input2,LOW);
      digitalWrite(input3,LOW);
      digitalWrite(input4,HIGH);
      delay(100);
    }
    if(junk == 'a'){   //for going left
      digitalWrite(input1,LOW);
      digitalWrite(input2,HIGH);
      digitalWrite(input3,HIGH);
      digitalWrite(input4,LOW);
      delay(100);
    }
     if(junk == 'b'){
      digitalWrite(input1,LOW);
      digitalWrite(input2,LOW);
      digitalWrite(input3,LOW);
      digitalWrite(input4,LOW);
      delay(100);
    
    }
  //}
  //Gas Sensing<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  if(junk == 'r'){
             if (i==0) {
               rzero = gasSensor.getRZero(); // float
             }
             if (i>0) {  
               result = gasSensor.getRZero();
               rzero = (rzero + result)/2;
              }
              float ppm = gasSensor.getPPM();
              Serial.print(rzero);
              Serial.print(", ");
              Serial.print(result);
              Serial.print(", ");
              Serial.print(ppm);
              Serial.println(" ppm");
              i++;
              delay(200);
  }

  //PIR Sensing<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  if(junk=='p'){
          val = digitalRead(inputPin);  // read input value
      if (val == HIGH) {            // check if the input is HIGH
        if (pirState == LOW) {
          // we have just turned on
          Serial.println("Radiation detected!");
          // We only want to print on the output change, not state
          pirState = HIGH;
        }
      } else {
        if (pirState == HIGH){
          // we have just turned of
          Serial.println("Radiation ended!");
          // We only want to print on the output change, not state
          pirState = LOW;
        }
      }
    }
  
  //LED turn On
  if(junk=='l'){
    digitalWrite(ledPin, HIGH);
  }
  //LED turn off
  if(junk=='n'){
    digitalWrite(ledPin, LOW);
  }
    
}
}
