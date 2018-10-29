
/**
 * This program interact the electron with thingspeak, send data
 * @author Dat Nguyen 
 * Date: 8/15/18
 */
#include <ThingSpeak.h>
#include <Wire.h>
#include "Particle.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int led = D7;  // The on-board LED\

// sensor val 
const int data_num = 2;
float data[data_num];
String dataName[data_num] = {"H","T"};
//1: H(humidity)
//2: T(Temperatur)


const int maxlength = 64;
const byte address = 8;

char buffer[maxlength];
char buff[maxlength];
char *printable;
char printable2[64];
int received = 0;
// byte SLAVE_ADDRESS = 8;

TCPClient client;


//replace WRITE_API_KEY with your write api key 
// found in "api keys" tab in your channel 
// const char * myWriteAPIKey = "WRITE_API_KEY";
unsigned int myChannelID = 555279;
const char * myWriteAPIKey = "GF5ET2VD0SCL696P";


// period of sending data
const unsigned long PUBLISH_PERIOD = 2700000;// 45 min
const unsigned long FIRST_PUBLISH_MS = 5000;

long lastPublish = 0;

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
    //setup i2c communication protocol
    Wire.begin(8);                // join i2c bus with address #8
    Wire.onReceive(receiveEvent); // register event
    Serial.begin(9600);           // start serial for output
  
    pinMode(led, OUTPUT);

    //init thingspeak channel and client 
    ThingSpeak.begin(client);
}
/**
 * This function split a char array given a delimiter
 * return 2d_char array
 */ 
char ** split(char *str, char delimiter, int *n) {
  int i, numDelimiters = 0;
  char delimit[] = {delimiter, '\0'};
  char *s = deepCopy(str);
  for(i=0; i<strlen(str); i++) {
    if(str[i] == delimiter) {
      numDelimiters++;
    }
  }

  char **result = (char **) malloc(sizeof(char**) * (numDelimiters+1));
  char *token = strtok(s, delimit);
  i = 0;
  while(token != NULL) {
    result[i] = deepCopy(token);
    token = strtok(NULL, delimit);
    i++;
  }

  free(s);
  *n = (numDelimiters+1);
  return result;
}
/*
 * This function deep copy an array
 */
char * deepCopy(const char *s) {
  char *copy = (char *) malloc( (strlen(s) + 1) * sizeof(char) );
  strcpy(copy, s);
  return copy;
}


void loop() {
    printable = (char*) malloc(sizeof(char) * maxlength);
    char **token;
    int *size = 0;
    //TODO: retrieve data here 
    Serial.println("out here");
    if (received > 0) {
        Serial.println("getiing data");
        
        // init the data array to validate
        for(int i =0;i<data_num;i++){
            data[i] = -1;
        }
        memcpy(printable, buffer, maxlength);
        Serial.print("FULL:");Serial.println(printable); 
        //token data here 
        token = split(printable,';',size);
        //parse token 
        for(int i = 0;i < data_num;i++){
            memset(buff,0,strlen(buff));
            if(token[i][0] == 'H'){// windspeed
                memcpy(buff, token[i]+1,sizeof(token[i]));
                data[0] = atof(buff);
            }else if(token[i][0] == 'T'){ // humidity
                memcpy(buff, token[i]+1,sizeof(token[i]));
                data[1] = atof(buff);
            }
            
        }
        received = 0;
 
          // print out all data received for debug 
          for(int j=0;j<data_num;j++){
              Serial.printf("\t%s: %lf",dataName[j],data[j]);
          }
          Serial.println();
    }
    

    delay(200);
    // keeping track of sending period 
    if( (millis() - lastPublish) > PUBLISH_PERIOD){
        lastPublish = millis();
        //publish to Thingspeak
        publishToThingspeak();
        publishParticle();
    }
    free(printable);

}

void publishToThingspeak(){
      // set field and publish to ThingSpeak 
  // to generate API key
  Serial.println("------------------");
  ThingSpeak.setField(1,String(data[1]));
  ThingSpeak.setField(2,String(data[0]));
    Serial.println("sended data to thingspeak");
  // Write the fields that you've set all at once.
  ThingSpeak.writeFields(myChannelID, myWriteAPIKey);
 
}

void publishParticle(){
    //FIXME: find a way to upload 
    Serial.println("sended data to particle Console");
    Particle.publish("humidity: ",String(data[0]));
    Particle.publish("temperature: ",String(data[1]));
}


