#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

const int onhour=19;
const int onmin=32;

const int offhour=19;
const int offmin=34;

const int onhour1=18;
const int onmin1=57;

const int offhour1=18;
const int offmin1=58;

const int onhour2=18;
const int onmin2=59;

const int offhour2=19;
const int offmin2=00;

const char* ssid = "MyASUS";
const char* password = "hy12345678";

int pom =16; // D0

int ENA = 13; //D7
int IN1 = 5; //D1
int IN2 = 4; //D2

WiFiUDP ntpUDP;
const long utcOffsetInSeconds = 25200;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds );

void setup() {

  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting.");

  pinMode(pom, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("connected");
  timeClient.begin();
}


void loop() {

  timeClient.update();

  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());

  //----------------------------------------------------------------------------
  if(timeClient.getHours()==onhour && timeClient.getMinutes()==onmin)
  {
    bool pesan = false;
    
    Serial.println("Light on");
    digitalWrite(pom, HIGH);
    makan();
  }
  else if(timeClient.getHours()==offhour && timeClient.getMinutes()==offmin)
  {
    Serial.println("Light off");
    digitalWrite(pom, LOW);
  }

  //----------------------------------------------------------------------------
  if(timeClient.getHours()==onhour1 && timeClient.getMinutes()==onmin1)
  {
    Serial.println("Light on");
    digitalWrite(pom, HIGH);
  }
  else if(timeClient.getHours()==offhour1 && timeClient.getMinutes()==offmin1)
  {
    Serial.println("Light off");
    digitalWrite(pom, LOW);
  }

  //----------------------------------------------------------------------------
  if(timeClient.getHours()==onhour2 && timeClient.getMinutes()==onmin2)
  {
    Serial.println("Light on");
    digitalWrite(pom, HIGH);
  }
  else if(timeClient.getHours()==offhour2 && timeClient.getMinutes()==offmin2)
  {
    Serial.println("Light off");
    digitalWrite(pom, LOW);
  }

  delay(1000);
}

void makan(){
  analogWrite(ENA, 50);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void stop_makan(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

