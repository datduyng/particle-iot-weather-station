
#include "Particle.h"
int led = D7;  // The on-board LED
int lightValue;

const unsigned long PUBLISH_PERIOD = 50000;
const unsigned long FIRST_PUBLISH_MS = 5000;

long lastPublish = 0;
void setup() {
    pinMode(led, OUTPUT);
    pinMode(A0,INPUT);
    Serial.begin(9600);
}

void loop() {

    // keeping track of sending period
    if( (millis() - lastPublish) > PUBLISH_PERIOD){
        lastPublish = millis();
        publishData();
    }

}

void publishData(){
  lightValue = analogRead(A0);
  int temp = random(500,600);
  int test = random(1000,1300);
//   String testStr = "Foo";
//   char* testCharArr = "testChar*";


  //print to buffer before sending to fireBase
  char buff[200];
  snprintf(buff,sizeof(buff),"{\"temp\":%d,\"test\":%d,\"lightValue\":%d}",temp,test,lightValue);
  //snprintf(buf, sizeof(buf), "{\"a\":%d,\"b\":%.3f,\"c\":%d}", a, b, c);

  Serial.printlnf("publishing %s", buff);
  Particle.publish("sensorLog", buff, PRIVATE);
  //Particle.publish("test",test,PRIVATE);

  // blink led
  digitalWrite(D7,HIGH);
  delay(300);
  digitalWrite(D7,LOW);
  delay(300);
}
