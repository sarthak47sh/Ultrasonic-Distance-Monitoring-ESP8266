/*

# Project: UltraSonic Distance Sensor Version 6 (Public / Not Working as I have not mentioned my channel id :) )
  Add IoT / WiFi Extension (ThingSpeak)
  Improving Speed

# Author: <Sarthak Sharma>
          <IIIT Bhopal>

# Description:
    Measures distance using an ultrasonic sensor and NodeMCU ESP8266 
    and displays the output on the Serial Monitor.


# Pin Connections

⦁Ultrasonic Sensor (HC-SR04)
VCC → Vin (5V from USB)
GND → GND
TRIG → D6
ECHO ── 1kΩ ───┐
               ├── D5
GND  ── 1kΩ ───┘

## Adding LEDs and Logic
 Distance (cm) | LED    
  ------------ | ------ 
   50 cm       | Green  
 20 – 50 cm    | Yellow 
 < 20 cm       | Red    


*/

// 
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const char* WiFi_SSID = "My_HotSpot_Name";
const char* WiFi_PASSWORD = "My_HotSopt_Password";

unsigned long Channel_Id = My_ThingSpeak_Channel_Id;
const char* Write_API_Key = "My_Write_API_Key";

WiFiClient Client;
//

//
unsigned long LastUploadTime = 0;
const unsigned long UploadInterval = 15000;                 // 15 seconds (ThingSpeak rule)
//

// Defining Names to Different Pins on NodeMCU
#define Green_LED D1
#define Yellow_LED D2
#define Red_LED D3

#define Trig_Pin D6
#define Echo_Pin D5

#define Near_Distance 20
#define Safe_Distance 50

long Duration;
float Distance;


void setup() {
  // put your setup code here, to run once:
  pinMode(Green_LED, OUTPUT);
  pinMode(Yellow_LED, OUTPUT);
  pinMode(Red_LED, OUTPUT);
  pinMode(Trig_Pin, OUTPUT);
  pinMode(Echo_Pin, INPUT);

  Serial.begin(9600);                                               // Baud Value

  //
  WiFi.begin(WiFi_SSID, WiFi_PASSWORD);
  Serial.print("Connecting tio WiFi ");

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
  ThingSpeak.begin(Client);
  //

}

float Get_Distance_By_UltraSonic_Sensor(){

  digitalWrite(Trig_Pin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(Trig_Pin, HIGH);
  delayMicroseconds(10);

  digitalWrite(Trig_Pin, LOW);

  Duration = pulseIn(Echo_Pin, HIGH);                             // 0.034 cm per microsecond
  return ( ( Duration * 0.034 ) /2 );                             // divide by 2 -> because of RoundTrip

}

void Update_LED_Status(float Distance){

  if(Distance >= 0 && Distance < Near_Distance){                                 // Close Distance
    digitalWrite(Red_LED, HIGH);
    digitalWrite(Yellow_LED, LOW);
    digitalWrite(Green_LED, LOW);
  }

  else if(Distance >= Near_Distance && Distance < Safe_Distance){               // Near Distance
    digitalWrite(Red_LED, LOW);
    digitalWrite(Yellow_LED, HIGH);
    digitalWrite(Green_LED, LOW);
  }
  
  else{                                                                         // Safe Distance
    digitalWrite(Red_LED, LOW);
    digitalWrite(Yellow_LED, LOW);
    digitalWrite(Green_LED, HIGH);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  
  Distance = Get_Distance_By_UltraSonic_Sensor(); 

  if (Distance <= 0 || Distance > 400) {
    Serial.println("Out of range");
    delay(1000);
    return;
  }

  // Local Updates
  Serial.print("Distance : ");
  Serial.print(Distance);
  Serial.println(" cm");

  Update_LED_Status(Distance);

  //
  if( millis - LastUploadTime >= UploadInterval ){
    ThingSpeak.setField(1, Distance);
    int status = ThingSpeak.writeFields(Channel_Id, Write_API_Key);

    if (status == 200) {
      Serial.println("Data Sent to ThingSpeak");
    } 
      else{
    Serial.println("ThingSpeak Error");
    }

    LastUploadTime = millis();

  }

  delay(300);
  //delay(15000);                                             // REQUIRED minimum delay of ThingSpeak
                                                              // Removed in Version 6

}
