/** 
 * Author Dat nguyen 
 * 7/3/18
 * This program result the particle electron to talk with uno 
 * uno: master 
 * electron: slave(receiver)
 */
 
#include <Wire.h>

const int maxlength = 64;
const byte address = 8;

char buffer[maxlength];
char printable[maxlength];


int received = 0;

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  received = howMany;
  memset(buffer, 0, maxlength);

  for (int i = 0; i < howMany; i++) {
    buffer[i] = Wire.read();
  }
}

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  pinMode(9, OUTPUT);
}

void loop() {
  if (received > 0) {
    memcpy(printable, buffer, maxlength);

    //TODO: Do something with the array here . 
    for (int i = 0; i < received; i++) {
      Serial.print(printable[i]);
     
    }
    Serial.println("");
     //Particle.publish("123", printable, PRIVATE);
    received = 0;
  }
}

