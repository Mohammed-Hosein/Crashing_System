
#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>



DFRobot_SIM808 sim808(&Serial);

const int buttonPin = 12;     // the number of the pushbutton pin
int buttonState = LOW;         // variable for reading the pushbutton status
char MESSAGE[300];
char lat[12];
char lon[12];
#define PHONE_NUMBER "07729137239"  
boolean sms_stop = false;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);


  //******** Initialize sim808 module *************
  while(!sim808.init()) { 
      delay(1000);
      Serial.print("Sim808 init error\r\n");
  }

 
}


void get_gps(){
   //************* Turn on the GPS power************
  while(!sim808.attachGPS())
      Serial.println("Open the GPS power failure");
   
      Serial.println("Open the GPS power success");

   while (!sim808.getGPS()) {
   }

    
    Serial.print("latitude :");
    Serial.println(sim808.GPSdata.lat,6);
    
    
    Serial.print("longitude :");
    Serial.println(sim808.GPSdata.lon,6);
    
    float la = sim808.GPSdata.lat;
    float lo =sim808.GPSdata.lon;

    dtostrf(la, 4,6,lat);
    dtostrf(lo, 4,6,lon);
    
    
     sprintf(MESSAGE, "Car Crashing happend \nLatitude : %s\nLongitude: %s\nhttp://www.latlong.net/Show-Latitude-Longitude.html\nhttp://maps.google.com/maps?q=%s,%s\n", lat, lon, lat, lon);
    Serial.println(MESSAGE);
    
    //************* Turn off the GPS power ************
     
  sim808.detachGPS();
}

void loop() {
  buttonState = digitalRead(buttonPin);
    if (buttonState== HIGH) {
sms_stop=false;
}
if (sms_stop==false){
    get_gps(); 
       sim808.sendSMS(PHONE_NUMBER,MESSAGE);
       Serial.print("Message sent"); 
       sms_stop=true;
}
}
