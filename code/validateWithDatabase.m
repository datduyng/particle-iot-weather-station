%{
@Author Dat Nguyen 
Date: 07/20/18 

This script validate the data retrieving from particle with `https://openweathermap.org/` 
api. then append the validated data to the graph showing in the public page of 
the channel .

 to see data type
https://openweathermap.org/current

dataFromDb = 

  struct with fields:

         coord: [1×1 struct]
       weather: [1×1 struct]
          base: 'stations'
          main: [1×1 struct]
    visibility: 16093
          wind: [1×1 struct]
        clouds: [1×1 struct]
            dt: 1.5342e+09
           sys: [1×1 struct]
            id: 5034652
          name: 'Lincoln County'
           cod: 200

%}

% channel with data to validate

chId_val = 558872
writeKey_val = 'BFO2IT9RVJHSRNZS'
readKey_val = 'SQ4O9BFNQTPSZR9Q'


chIdToRead = 555279
readKey_sens = 'MNQ7CKXBTZL3U2GY'
writekey_sens = 'GF5ET2VD0SCL696P'

% main channel to display data. 
chId = 521293
API_KEY = '3551223b0f56ff975fe725c7c49e8a64'
writeKey_main = '3R2OOEAFSLAGUUIR'
readKey_main = 'G9NZGBITUB5K4FF1'


MPS_MPH = 2.23694

% delay in case a devices upload data to rapidly. 
delay_per_message = 15

% with free account thing speak allow user to post one message per 15 s
% therefore, a delay is needed. 
pause on 
time_count = 0 
while(time_count < delay_per_message)
    time_count = time_count+1    
    pause(1)
end 


% having weird problem with using sprintf 
% with the url. url would pass expect data
url = 'https://api.openweathermap.org/data/2.5/weather?id=5034652&appid=3551223b0f56ff975fe725c7c49e8a64'

"reading data from api"
dataFromDb = webread(url)

tempDb = (9/5) *(dataFromDb.main.temp - 273) + 32
humdDb = dataFromDb.main.humidity
windSpeedDb = dataFromDb.wind.speed*MPS_MPH
rainDb = 0.0
if(strcmp(dataFromDb.weather,"rain"))
    rainDb = dataFromDb.rain.rh*1.0
end 

%read the ,most recent data from the channel used for validation.
[dataThingspeak,timestamps,chInfo] = thingSpeakRead(chIdToRead,'Fields',[1,2,4] ,'ReadKey',readKey_sens)

disp(dataThingspeak)

% validate the data by taking the average
meanTemp = (dataThingspeak(1) + tempDb)/2
meanHumd = (dataThingspeak(2) + humdDb)/2
meanWind = (dataThingspeak(3) + windSpeedDb)/2

% write to sens_channel and validation_channel 
thingSpeakWrite(chId,'Fields',[1,2,3,4],'Values',[meanTemp, meanHumd,rainDb, meanWind],'WriteKey',writeKey_main)
thingSpeakWrite(chId_val,'Fields',[1,2,3,4],'Values',[tempDb, humdDb,rainDb, windSpeedDb],'WriteKey',writeKey_val)

