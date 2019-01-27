# Weather station project requirements


### I.Hardware requirement
- A fully developed end to end weather station need to be created. (- start by create a flow diagram of your system/ UML diagram). Here is an [example](https://user-images.githubusercontent.com/35666615/51284584-9f0f5a00-19b1-11e9-9326-608e5ffdcf01.jpg). [Good Diagram drawing platform](https://www.lucidchart.com)
- Design of hardware components should be modularized. Example: If user would like to add new sensor or node(an extra Arduino Nano), then your system should allow user do that with out addding much code.
- Weather station should have the following sensor value fields.
	- temperture
	- Humidity
	- GPS coordinate(let's say if groups decide to change weather station location then Particle should be able to automatically update the longtitude and latitude). Particle should only update this field once everyday(efficiency reason). You might find [this guide](https://docs.particle.io/tutorials/integrations/google-maps/) helpfuls
	- 3 extra field require

### II.Software requirement
- Once sensors values are published to Thingspeak. System should be able to validate the sensor data with a database(or weather forecast) to average out and get a better approximation of your sensor values. [Link to weather database website](https://openweathermap.org/). Feel free to use multiple database to achieve a better approximation of your sensor values. Thingspeak 'React' apps can help you acoomplished this without feasible amount of work. 
- All field(sensor values) described above must be display visually to the [public channel](https://user-images.githubusercontent.com/35666615/51804309-cfae8980-2224-11e9-94b8-f4d9c69210ff.PNG).(available for every to view)
- Additionally, there should be extra field showing at least 3 graphs. Likes Temperature from sensor with temperature from database, humidity vs temperature,...
- Additionally, Thingspeak are integrated with apps. Thingspeak apps allow you to create dynamic data content visualization. Use at least 2 additional [apps](https://user-images.githubusercontent.com/35666615/51804549-f1f5d680-2227-11e9-8731-fc8246b30119.PNG) for your project. [Here is a list of all Thingspeak apps](https://thingspeak.com/apps)
- Ex: Note: each window is refers to a fields.

<br><img width="300" height="300" src="https://user-images.githubusercontent.com/35666615/51804501-59f7ed00-2227-11e9-9485-a0f6ccf00d33.PNG"><br>




### III. User interface requirement
- User should be able to add extra sensor with out having to add many line of codes
- EFfective error handling. An LED to indicate faulty or something to indicate there are error
