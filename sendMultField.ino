
/**
 * @author Dat Nguyen 
 * Date: 06/14/18 
 * This program send multi field to ThingSpeak to generate
 * An API key holding data in JSON Format
 **/

// This #include statement was automatically added by the Particle IDE.
#include <ThingSpeak.h>



int led = D7;  // The on-board LED

String lightValue;
TCPClient client;

unsigned int myChannelNumber = 518268;
const char * myWriteAPIKey = "GGCUNMUK47UUQDOT";

void setup() {
    ThingSpeak.begin(client);
    pinMode(led, OUTPUT);
    pinMode(A0,INPUT);
}

void loop() {
  lightValue = String(analogRead(A0));
  String temp = String(random(10,50));
  String test = String(random(120,150));
  String testStr = "Foo";
  char* testCharArr = "testChar*";
  
  /** Print to Serial Monitor**/
  Serial.print("lightValue:");Serial.print(lightValue);
  Serial.print("  temp:");Serial.print(temp);
  Serial.print("  test:");Serial.print(test);
  Serial.print("  testStr:");Serial.print(testStr);
  Serial.print("  testCharArr:");Serial.println(testCharArr);

  // publish to particle console
  Particle.publish("temp", temp, PRIVATE);
  Particle.publish("lightValue", lightValue, PRIVATE);
  Particle.publish("test", test, PRIVATE);
  Particle.publish("testStr", testStr, PRIVATE);
  Particle.publish("testCharArr", testCharArr, PRIVATE);
  
  
  // set field and publish to ThingSpeak 
  // to generate API key
  ThingSpeak.setField(2,temp);
  ThingSpeak.setField(1,test);
  ThingSpeak.setField(3,lightValue);
  ThingSpeak.setField(4,testCharArr);
  ThingSpeak.setField(5,testStr);
  //ThingSpeak.setField(2,h);

  // Write the fields that you've set all at once.
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);  
  
  
    delay(10);               // Wait for 30 seconds

}