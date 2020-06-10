#include <Arduino.h>
#include <IRremote.h>
#include <Servo.h>

const byte servoPin = 9;
const int RECV_PIN = 6;
IRrecv irrecv(RECV_PIN);
decode_results results;

Servo servo; // Crea objeto Servo

void setup(){
  pinMode(servoPin, OUTPUT);
  servo.attach(servoPin);
  servo.write(90);
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop(){
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        Serial.println("Impacto!");
        
        
        servo.write(180);
        delay(2000);
        servo.write(90);
        irrecv.resume();
  }
  
}