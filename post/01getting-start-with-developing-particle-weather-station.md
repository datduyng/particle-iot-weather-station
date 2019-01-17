### Getting start with Particle Weather station

**Section** <br> 
- [Setting up particle Electron](#Setting-up-particle)
- [I2c Communication protocol](#I2C-Communication)


> <img src="https://user-images.githubusercontent.com/35666615/51284584-9f0f5a00-19b1-11e9-9326-608e5ffdcf01.jpg" height="400" width="600">


### Setting up particle
- Particle is a multi purpose device. It has a bunch of mode[(particle mode)](https://docs.particle.io/tutorials/device-os/led/electron/). Example: Arduino UNO would just have one red LED to indicate the power mode(on/off) -- So be familiar with all the mode indicate by the particle RGB LED.
- Let's start programming that particle.[here](https://docs.particle.io/tutorials/developer-tools/build/electron/)
- [Here is a good doc by Particle io](https://www.instructables.com/id/I2C-between-Arduinos/)
- Particle website allow you to download library and upload code right on the cloud. 
- In this project, The Particle only need to include the 'ThingSpeak' library(Since the particle is a bridge device between 'the ground' and 'the cloud'). So make sure you download thats.

### I2C Communication 
- I am asssuming that reader are familiar with Arduino sensor reading. 
- In order to avoid hurtting multiple component during operation phase, it is good practice to modularize the system. 
- In our project, We will use an `Arduino Nano` as a device to collect sensor data. Particle Electron as Module to transfer data to Thingspeak(or any cloud really). 
- here is some code that will allow you to send packages(or data) to the particle

```c++
#include<Wire.h> // i2c Communication


// Here you would define the address of the 
// SLAVE. why in byte?? max of a byte is 2^8 = 255 
// this mean that I2C communication is valid for only
// 255 node(module)
byte SLAVE_ADDRESS = 8;

// here buff is the package. We need to append
// all sensor values into one big string.
// or one big string package
int packageLength = 255;
char buff[255];

// this indicate the period you would like to send
// your data to the particle. Design this carefully, 
// here: 2000 mean that the Arduino will send data to particle
// every 2 seconds(2000 ms)
#define period_between_data 2000
long last_send = 0;

// NOTE: it is good to define sensor value as global 
// variable. So ALL function can view it.(You can use the variable
// in all places of the code)
int sensor_value1 = 0;
int sensor_value2 = 0; 
int sensor_value3 = 0;


int update_sensor1(){
	// write some code to update sensor value here
	return 0;
}

void setup(){
	Serial.begin(9600); // as usual just open the display usb port
	Wire.begin(); // join all the i2c connection
}

void loop(){
	// read and update data sensor here
	//
	sensor_value1 = update_sensor1();
	//
	//

	if((millis() - last_send) > period_between_data){
		last_send = millis(); // update the time you last send

		// 
		snprintf(buff, packageLength, "%d;%d", sensor_value1,sensor_value2);
		//ex: buff = "12;234";

		// send data to Particle
		Wire.beginTransmission(SLAVE_ADDRESS);
	    Wire.write(buff);// send the package
	    Wire.endTransmission();
	}
}

```

### Seting up Thing speak
- [This article do a really good job of explaining](https://www.codeproject.com/Articles/845538/An-Introduction-to-ThingSpeak)

### Now Let's get the data from Particle to Thingspeak

```c++
#include "Particle.h"
#include<Wire.h>
#include <ThingSpeak.h>


const int maxlength = 64;
const byte address = 8;

char buffer[maxlength];
char buff[maxlength];

TCPClient client;

//replace WRITE_API_KEY with your write api key 
// found in "api keys" tab in your channel 
// const char * myWriteAPIKey = "WRITE_API_KEY";
unsigned int myChannelID = 555279;
const char * myWriteAPIKey = "GF5ET2VD0SCL696P";


// period of sending data
const unsigned long PUBLISH_PERIOD = 1800000;//1800000 = 30 min -> particle send data every 30 min
const unsigned long FIRST_PUBLISH_MS = 5000;


// This function will execute whenever
// I2C bus receive any data. 
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
	Serial.begin(9600);           // start serial for output

    //setup i2c communication protocol
    Wire.begin(8);                // join i2c bus with address #8
    Wire.onReceive(receiveEvent); // register event

    //init thingspeak channel and client 
    ThingSpeak.begin(client);
}

void loop(){

    if (received > 0) {// when receiveEvent() got executed. 
    	               // received keep track of number of byte 
    	               // that we received
    	// do something here like 
    	// tokenizing the packages. 
    	// NOTE: buffer is a string that you sent above rememeber
    	//(ex: buff = "12;234";)
        received = 0;
    }

    if( (millis() - lastPublish) > PUBLISH_PERIOD){
        lastPublish = millis();
        //publish to Thingspeak
        publishToThingspeak();
        publishParticle();
    }
}

void publishToThingspeak(){
      // set field and publish to ThingSpeak 
  // to generate API key
  //
  ThingSpeak.setField(1,String(sensor_value1));//temp
  ThingSpeak.setField(2,String(sensor_value2));//humd
  ThingSpeak.setField(3,String(sensor_value3));//rain

  // Write the fields that you've set all at once.
  ThingSpeak.writeFields(myChannelID, myWriteAPIKey);
 
}

void publishParticle(){
    // Publish to Particle on website. (mostly for viewing only)
    Particle.publish("humidity: ",String(sensor_value1));
    Particle.publish("temperature: ",String(sensor_value2));
    Particle.publish("rain: ",String(sensor_value3));
}
```