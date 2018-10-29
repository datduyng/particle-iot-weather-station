#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include <Wire.h> //I2C needed for sensors
#include <cactus_io_AM2315.h>

AM2315 am2315;
int packageLength = 255;
byte SLAVE_ADDRESS = 8;
char buff[255];

float temperature=0.0; 
float humidity=0.0;

void setup(){
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
  if(!am2315.begin()){
    Serial.println("Check sensor wiring...");
    while(millis()<10000){
      digitalWrite(13,LOW); delay(1000); 
      digitalWrite(13,HIGH); delay(100);
      digitalWrite(13,LOW); delay(100); 
      digitalWrite(13,HIGH); delay(100);
    }
  }
  
}

void loop(){
  am2315.readSensor();  
  temperature = am2315.getTemperature_F();
  humidity = am2315.getHumidity();
  snprintf(buff,packageLength,";H%s;T%s",String(humidity).c_str(),String(temperature).c_str());// float does not support sprintf arduin
  sendPacketI2c(buff);
  delay(3000);
}

void sendPacketI2c(char *package){
//    snprintf(buff,packageLength,";WS%s;HS%d;TS%d;DS%d;HA%s;TA%s",String(windspeedmph).c_str(),(int)humidity,(int)tempf, winddir,String(humd_am2315).c_str(), String(temp_am2315).c_str());// float does not support sprintf arduino 
    Serial.print("buff:");Serial.println(buff);
    Wire.beginTransmission(SLAVE_ADDRESS);// transmit to device #8
    Wire.write(buff);// send the package
    Wire.endTransmission();
    // clean up the packagewindSpeedInStr
    memset(buff,0,strlen(buff));
}
