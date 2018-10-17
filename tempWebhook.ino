// This #include statement was automatically added by the Particle IDE.
#include <ThingSpeak.h>



int led = D7;  // The on-board LED
TCPClient client;

unsigned int myChannelNumber = 518268;
const char * myWriteAPIKey = "GGCUNMUK47UUQDOT";

void setup() {
    ThingSpeak.begin(client);
  pinMode(led, OUTPUT);
}

void loop() {
  String temp = String(random(60, 80));
  String test = "Foo";
  char* testChar = "testChar*";

  Particle.publish("temp", temp, PRIVATE);
  
  
      
  ThingSpeak.setField(1,temp);
  ThingSpeak.setField(2,test);
  ThingSpeak.setField(3,testChar);
  //ThingSpeak.setField(2,h);

  // Write the fields that you've set all at once.
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);  
    delay(10);               // Wait for 30 seconds

}