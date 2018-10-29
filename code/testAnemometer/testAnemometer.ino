/**
 * This program test the anemometer 
 * base on: http://www.vashonceltictunes.net/misc/WeatherStation/WeatherStation.pde
 */

#define ANE_PIN 2 
volatile int numRevsAnemometer = 0; // Incremented in the interrupt
// How often we want to calculate wind speed or direction
#define MSECS_CALC_WIND_SPEED 3000

long nextCalcSpeed;                // When we next calc the wind speed
long nextCalcDir;                  // When we next calc the direction
long time;                         // Millis() at each start of loop().


//=======================================================
// Calculate the wind speed, and display it (or log it, whatever).
// 1 rev/sec = 1.492 mph
//=======================================================
void calcWindSpeed() {
   int x, iSpeed;
   // This will produce mph * 10
   // (didn't calc right when done as one statement)
   long speed = 14920;
   speed *= numRevsAnemometer;
   speed /= MSECS_CALC_WIND_SPEED;
   iSpeed = speed;         // Need this for formatting below

   Serial.print("Wind speed: ");
   x = iSpeed / 10;
   Serial.print(x);
   Serial.print('.');
   x = iSpeed % 10;
   Serial.println(x);

   numRevsAnemometer = 0;        // Reset counter
}
//=======================================================
// Interrupt handler for anemometer. Called each time the reed
// switch triggers (one revolution).
//=======================================================
void countAnemometer() {
   numRevsAnemometer++;
//   Serial.print("NUM REv"); Serial.println(numRevsAnemometer);
}
void setup() {
  Serial.begin(9600);
  pinMode(ANE_PIN,INPUT);
  digitalWrite(ANE_PIN, HIGH);
  attachInterrupt(0,countAnemometer, CHANGE);
  nextCalcSpeed = millis() + MSECS_CALC_WIND_SPEED;
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
     time = millis();

   if (time >= nextCalcSpeed) {
      calcWindSpeed();
      nextCalcSpeed = time + MSECS_CALC_WIND_SPEED;
   }

//   Serial.print("Windspeed is"); Serial.println(nextCalcSpeed); 

}
