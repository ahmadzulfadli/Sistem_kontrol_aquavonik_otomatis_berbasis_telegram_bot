#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

//------------------------------
const int onhourpompa=8;
const int onminpompa=0;

const int offhourpompa=8;
const int offminpompa=30;

const int onhourpompa1=12;
const int onminpompa1=0;

const int offhourpompa1=12;
const int offminpompa1=30;

const int onhourpompa2=17;
const int onminpompa2=0;

const int offhourpompa2=17;
const int offminpompa2=30;

//------------------------------
const int onhourpakan=8;
const int onminpakan=40;

const int offhourpakan=11;
const int offminpakan=45;

const int onhourpakan1=12;
const int onminpakan1=40;

const int offhourpakan1=12;
const int offminpakan1=45;

const int onhourpakan2=17;
const int onminpakan2=40;

const int offhourpakan2=17;
const int offminpakan2=45;

//------------------------------

const char* ssid = "MyASUS";
const char* password = "hy12345678";

int pom =16; // D0

//----------------------------------------------------------------------------
int ENA = 13; //D7
int IN1 = 5; //D1
int IN2 = 4; //D2

//----------------------------------------------------------------------------
WiFiUDP ntpUDP;
const long utcOffsetInSeconds = 25200;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds );

//----------------------------------------------------------------------------
#define BOT_TOKEN "5468558062:AAFxFqwPsFug8WIPvVbqW9Egqbz_d71dgn8"
#define CHAT_ID "1096619393"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

//Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;
//----------------------------------------------------------------------------

void setup() {

  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting.");

  pinMode(pom, OUTPUT);
  digitalWrite(pom, LOW);
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
  timeClient.update();

  // Add root certificate for api.telegram.org
  configTime(0, 0, "pool.ntp.org");
  secured_client.setTrustAnchors(&cert);
  bot.sendMessage(CHAT_ID, "Sistem Berjalan", "");
}


void loop() {

  //Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());

  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }

  //----------------------------------------------------------------------------
  if(timeClient.getHours()==onhourpompa && timeClient.getMinutes()==onminpompa)
  {
    if(timeClient.getHours()==onhourpompa && timeClient.getMinutes()==onminpompa && timeClient.getSeconds()==0){
      bot.sendMessage(CHAT_ID, "Pompa Hidup", "");
    }
    Serial.println("pompa hidup");
    digitalWrite(pom, HIGH);
  }
  else if(timeClient.getHours()==offhourpompa && timeClient.getMinutes()==offminpompa)
  {
    digitalWrite(pom, LOW);
    Serial.println("pompa mati");
    if(timeClient.getHours()==offhourpompa && timeClient.getMinutes()==offminpompa && timeClient.getSeconds()==0){
      bot.sendMessage(CHAT_ID, "Pompa Mati", "");
    } 
  }

  //----------------------------------------------------------------------------
  if(timeClient.getHours()==onhourpakan && timeClient.getMinutes()==onminpakan)
  {
    if(timeClient.getHours()==onhourpakan && timeClient.getMinutes()==onminpakan && timeClient.getSeconds()==0){
      bot.sendMessage(CHAT_ID, "Pakan Ikan Sedang Diberikan", "");
      Serial.println("Pakan Ikan Sedang Diberikan");
    }
    makan();
    
  }else if(timeClient.getHours()==offhourpakan && timeClient.getMinutes()==offminpakan)
  {
    if(timeClient.getHours()==offhourpakan && timeClient.getMinutes()==offminpakan && timeClient.getSeconds()==0){
      Serial.println("Pakan Ikan Selesai Diberikan");
      bot.sendMessage(CHAT_ID, "Pakan Ikan Selesai Diberikan", "");
    }
    stop_makan();
  }

  //----------------------------------------------------------------------------
  if(timeClient.getHours()==onhourpompa1 && timeClient.getMinutes()==onminpompa1)
  {
    if(timeClient.getHours()==onhourpompa1 && timeClient.getMinutes()==onminpompa && timeClient.getSeconds()==0){
      bot.sendMessage(CHAT_ID, "Pompa Hidup", "");
    }
    Serial.println("pompa hidup");
    digitalWrite(pom, HIGH);
  }
  else if(timeClient.getHours()==offhourpompa1 && timeClient.getMinutes()==offminpompa1)
  {
    digitalWrite(pom, LOW);
    Serial.println("pompa mati");
    if(timeClient.getHours()==offhourpompa1 && timeClient.getMinutes()==offminpompa1 && timeClient.getSeconds()==0){
      bot.sendMessage(CHAT_ID, "Pompa Mati", "");
    } 
  }

  //----------------------------------------------------------------------------
  if(timeClient.getHours()==onhourpakan1 && timeClient.getMinutes()==onminpakan1)
  {
    if(timeClient.getHours()==onhourpakan1 && timeClient.getMinutes()==onminpakan1 && timeClient.getSeconds()==0){
      bot.sendMessage(CHAT_ID, "Pakan Ikan Sedang Diberikan", "");
      Serial.println("Pakan Ikan Sedang Diberikan");
    }
    makan();
    
  }else if(timeClient.getHours()==offhourpakan1 && timeClient.getMinutes()==offminpakan1)
  {
    if(timeClient.getHours()==offhourpakan1 && timeClient.getMinutes()==offminpakan1 && timeClient.getSeconds()==0){
      Serial.println("Pakan Ikan Selesai Diberikan");
      bot.sendMessage(CHAT_ID, "Pakan Ikan Selesai Diberikan", "");
    }
    stop_makan();
  }

  //----------------------------------------------------------------------------
  if(timeClient.getHours()==onhourpompa2 && timeClient.getMinutes()==onminpompa2)
  {
    if(timeClient.getHours()==onhourpompa2 && timeClient.getMinutes()==onminpompa2 && timeClient.getSeconds()==0){
      bot.sendMessage(CHAT_ID, "Pompa Hidup", "");
    }
    Serial.println("pompa hidup");
    digitalWrite(pom, HIGH);
  }
  else if(timeClient.getHours()==offhourpompa2 && timeClient.getMinutes()==offminpompa2)
  {
    digitalWrite(pom, LOW);
    Serial.println("pompa mati");
    if(timeClient.getHours()==offhourpompa2 && timeClient.getMinutes()==offminpompa2 && timeClient.getSeconds()==0){
      bot.sendMessage(CHAT_ID, "Pompa Mati", "");
    } 
  }

  //----------------------------------------------------------------------------
  if(timeClient.getHours()==onhourpakan2 && timeClient.getMinutes()==onminpakan2)
  {
    if(timeClient.getHours()==onhourpakan2 && timeClient.getMinutes()==onminpakan2 && timeClient.getSeconds()==0){
      bot.sendMessage(CHAT_ID, "Pakan Ikan Sedang Diberikan", "");
      Serial.println("Pakan Ikan Sedang Diberikan");
    }
    makan();
    
  }else if(timeClient.getHours()==offhourpakan2 && timeClient.getMinutes()==offminpakan2)
  {
    if(timeClient.getHours()==offhourpakan2 && timeClient.getMinutes()==offminpakan2 && timeClient.getSeconds()==0){
      Serial.println("Pakan Ikan Selesai Diberikan");
      bot.sendMessage(CHAT_ID, "Pakan Ikan Selesai Diberikan", "");
    }
    stop_makan();
  }
  delay(1000);
}

void makan(){
  for(int i = 0; i <= 15; i++){
    analogWrite(ENA, 255);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    delay(1000);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    delay(1000);
  }
}

void stop_makan(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void handleNewMessages(int numNewMessages) {
  Serial.print("Handle New Messages: ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);
    
    String from_name = bot.messages[i].from_name;
    if (text == "/start") {
      String welcome = "Welcome , " + from_name + "\n";
      welcome += "Panduan Penggunaan \n";
      welcome += "/pompa_on : Menghidupkan pompa air\n";
      welcome += "/pakan_on : Memberi pakan \n";

      welcome += "/pompa_off : Mematikan pompa air\n";
      welcome += "/pakan_off : Pakan selesai diberikan \n";
      bot.sendMessage(CHAT_ID, welcome, "");
    }
    if (text == "/pompa_on") {
      bot.sendMessage(CHAT_ID, "Pompa Hidup", "");
      Serial.println("pompa hidup");
      digitalWrite(pom, HIGH);
    }
    
    if (text == "/pompa_off") {
      digitalWrite(pom, LOW);
      Serial.println("pompa mati");
      bot.sendMessage(CHAT_ID, "Pompa Mati", "");
    }
    
    if (text == "/pakan_on") {
      bot.sendMessage(CHAT_ID, "Pakan Ikan Sedang Diberikan", "");
      Serial.println("Pakan Ikan Sedang Diberikan");
      makan();
    }
    
    if (text == "/pakan_off") {
      Serial.println("Pakan Ikan Selesai Diberikan");
      bot.sendMessage(CHAT_ID, "Pakan Ikan Selesai Diberikan", "");
      stop_makan();
    }     
  }
}

