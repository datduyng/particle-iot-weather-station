## Weather station

***Section***
- [Overview](#overview)
- [Working Flowchart](#working-flowchart)
- [Components](#components)
- [Wiring](#wiring)
	- [troubleshooting on wiring process](#troubleshooting-on-wiring-process )
- [example code.](#example-code)
- [Data export](#data-export)
- [Interact with thingspeak and Thingspeak feature](#interact-with-thingspeak)
	- [matlab visualization app](#matlab-visualization-app)
	- [matlab analysis app](#matlab-analysis-app) 
	- [TimeControl app](#iimeControl-app)
- [Other feature](#other-feature)
	- [interact with firebase(DB)](#interact-with-firebase(DB))
- [What other people have done?](#what-other-people-have-done)

### Overview 
- This project interact the particle with thingspeak. 
- Particle electron module will retrieve data from weather shield via I2C bus 
- In the front end, Thingspeak will receive the data from weather shield and from [OpenWeathermap](https://openweathermap.org) Database
- User will view the most accurate data averaging from all channel.
- Public Thingspeak channel can be view [Here](https://thingspeak.com/channels/521293) 
- front end of project overview(refer to picture)
> ![data](https://user-images.githubusercontent.com/35666615/47681099-99fef380-db96-11e8-9463-28405fdc240f.PNG)

### Working Flowchart
> ![weatherstationflowchart](https://user-images.githubusercontent.com/35666615/47680953-3ecd0100-db96-11e8-9347-1282e704f4b8.PNG)

### Components
- [Particle electron(0.7.0 firmware version)](https://www.particle.io/products/hardware/electron-cellular-2g-3g-lte)
- [Weather Meters(sparkfun)](https://www.sparkfun.com/products/8942)
- [SparkFun Weather Shield](https://www.sparkfun.com/products/13956)
- Arduino uno 

### Wiring 
> ![528e2775757b7fb0668b4567](https://user-images.githubusercontent.com/35666615/42290717-b720172a-7f8c-11e8-975b-02a0eb231c07.jpg)
- plug the 2 wire that control the windspeed and rain sensor to the weather shield
- additionaly
	- `SDA(arduino) -> SDA(electron-pinD0)`
	- `SCL(arduino) -> SCL(electron-pinD1)`

#### troubleshooting on wiring process 
- refer 
	- https://learn.sparkfun.com/tutorials/weather-shield-hookup-guide

### Interact with thingspeak
- https://thingspeak.com/
- create an account
- create a channel 
- go to channel setting
- create more field(a channel- data get send from your device to thingspeak)
> ![thingspeak](https://user-images.githubusercontent.com/35666615/42291253-3503e376-7f90-11e8-8c30-869d3e6b403d.PNG)
- In my sketch, I use field 4,5,6 for example. 
- ***note:*** make sure your field number match with field number on thingspeak.
- access to `amsl.lab.unl@gmail.com`() for more example code .


#### matlab visualization app
- example of matlab code that graph 2 field with filled area
> ![filledgraph](https://user-images.githubusercontent.com/35666615/42291837-e093f5c0-7f93-11e8-8996-6804bf4540e7.PNG)


#### matlab analysis app
- this app allow you to run a program
- retrieve data using matlab given a period of time 
- retrieve data from field.
- example show a matlab program that calculate and display avaerage humidity 


#### TimeControl app
- this app work with[matlab analysis](####matlab-analysis-app) you can schedule thingspeak to run a matlab script 
- In the example, I show a matlab script that trigger an API provide by [ifttt](https://ifttt.com/discover) to send you an email when a value reach certain threshold. You can make it send you a phone message to.
- https://www.mathworks.com/help/thingspeak/analyze-channel-data-to-send-email-notification-from-ifttt.html 

### example code
- [Arduino node ](https://gist.github.com/datduyng/f580f32d41ddd0baf7030e16ab3fa9e0)
- [Particle node](https://gist.github.com/datduyng/4cb1a0e75b28d30198b6f3c847d2a881)

### Data export
- Thingspeak allow you to export your data from fields to diffrence format(JSON,XML,CSV)
- simply click "Public view" or "Private view" then click on "Data Export"


### Other feature 
#### interact with firebase(DB)
- Google firebase .
  - store data retrieve from sensor to Google fire Firebase
  - https://github.com/rickkas7/firebase_tutorial
- to retrieve data from firebase with programming language
  - https://firebase.google.com/docs/database/admin/retrieve-data
- firebase lib for python
  - https://github.com/ozgur/python-firebase

### What other people have done? 
- https://www.hackster.io/hliang/thingspeak-weather-station-data-analysis-2877b0 


