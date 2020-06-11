#include <Arduino.h>
#include "IRremote.h"
#include "CppList.h"
#include <Servo.h>

bool _initialized = false;

int rcv_count;
IRrecv **all_rcv;

const byte servo1Pin = 9;
const byte servo2Pin = 10;

Servo servo1; // Crea objeto Servo
Servo servo2;

unsigned long now1;
unsigned long now2;

const int interval = 2000;

void setup() {
  if (_initialized) return;
  
  Serial.begin(9600);
  
  rcv_count = 2;
  all_rcv = (IRrecv **)malloc(rcv_count*sizeof(int));
  all_rcv[0] = new IRrecv(5);
  all_rcv[1] = new IRrecv(6);
  
  for (int i=0; i<rcv_count; ++i){
    all_rcv[i]->enableIRIn();
  }
  
  pinMode(servo1Pin, OUTPUT);
  pinMode(servo2Pin, OUTPUT);

  servo1.attach(servo1Pin);
  servo1.write(0);
  servo2.attach(servo2Pin);
  servo2.write(0);

  _initialized = true;
}

void loop() {
  
  decode_results results;
  if (all_rcv[0]->decode(&results)) {
      
      Serial.println("Impacto en 1!!");
      all_rcv[0]->resume();
      servo1.write(180);
      now1 = millis();
  }

  if (all_rcv[1]->decode(&results)) {
      Serial.println("Impacto en 2!!");
      all_rcv[1]->resume();
      servo2.write(180);
      now2 = millis();
  }

  if((millis() - now1) > interval){
      servo1.write(0);
    }

    if((millis() - now2) > interval){
      servo2.write(0);
    }
}




/*
#include <IRremote.h>
#include <Servo.h>

const byte servo1Pin = 9;
const byte servo2Pin = 10;
Servo servo1; // Crea objeto Servo
Servo servo2;

unsigned long now1;
unsigned long now2;

int interval = 2000;

void setup(){
  pinMode(servo1Pin, OUTPUT);
  pinMode(servo2Pin, OUTPUT);

  servo1.attach(servo1Pin);
  servo1.write(0);
  servo2.attach(servo2Pin);
  servo2.write(0);
  Serial.begin(9600);
}

void loop(){
  if (irrecv1.decode(&results1)){
        Serial.println(results1.value, HEX);
        Serial.println("Impacto en 1!");
        irrecv1.resume();
        servo1.write(180);
        now1 = millis();
  }
  delay(25);

   if (irrecv2.decode(&results2)){
        Serial.println(results2.value, HEX);
        Serial.println("Impacto en 2!");
        irrecv2.resume();
        servo2.write(180);
        now2 = millis();
  }

    if((millis() - now1) > interval){
      servo1.write(0);
    }

    if((millis() - now2) > interval){
      servo2.write(0);
    }

}*/