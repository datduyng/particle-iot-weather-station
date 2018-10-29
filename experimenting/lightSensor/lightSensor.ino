// This #include statement was automatically added by the Particle IDE.
#include "lib1.h"
int value;
void setup() {
    pinMode(A0,INPUT);
    Serial.begin(9600);
    Particle.publish("Ready to go");
    
}

void loop() {
    char buf[4];

    value = analogRead(A0);
    // value.toCharArray(10);  
    sprintf(buf,"%d",value);
    Serial.print("Value:");Serial.println(value);
    Serial.print("Value in string");Serial.println(buf);
    Particle.publish("Value",buf);
    delay(1000);
}