 //include library
#include <DHT.h>
#include <CTBot.h>

//variabel bot
CTBot myBot;

//setting koneksi wifi
String ssid = "Gratisan";
String pass = "88888888";

//variabel sensor
#define DHTPin D7
#define DHTTYPE DHT11
DHT dht(DHTPin, DHTTYPE);

#define pinBuzzer D5
#define pinFlame D6

//variabel telegram
String token = "5810226180:AAE5u8tlxfLGhwispOIYK7zjGYqtxWCm85Q";
const int id =  5498300829;

void setup(){
  Serial.begin(9600);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinFlame, INPUT);
  dht.begin();

// koneksi ke wifi
  Serial.println("Koneksi ke telegram...");
  myBot.wifiConnect(ssid, pass);
//  koneksi ke telegram
  myBot.setTelegramToken(token);

//cek koneksi wifi
  if(myBot.testConnection()){
    Serial.println("Koneksi berhasil!");
  }else{
    Serial.println("Koneksi Gagal...");
  }

  delay(1000);
}

void loop(){
//  sensor api
  int sensorReading = digitalRead(pinFlame);
  Serial.print("Deteksi Api : ");
  Serial.println(sensorReading);

//  sensor asap
  int sensorSmoke = analogRead(A0);
  Serial.print("Ketebalan asap : ");
  Serial.println(sensorSmoke);

//  sensor suhu
  float suhu = dht.readTemperature();
  Serial.print("temperature : ");
  Serial.println(suhu);

  Serial.println("");
  
  if(sensorReading == 0){
    digitalWrite(pinBuzzer,HIGH);
    Serial.println("Fire Detected");
    myBot.sendMessage(id, "Terdeteksi keberadaan api di Koperasi Pakem Berkah Bersama");
  }
  if(sensorSmoke > 150){
    digitalWrite(pinBuzzer,HIGH);
    Serial.println("Smoke Detected");
    myBot.sendMessage(id, "Terdeteksi asap di Koperasi Pakem Berkah Bersama");
  }
  if(suhu >= 33){
    digitalWrite(pinBuzzer,HIGH);
    Serial.println("Suhu Detected");
    myBot.sendMessage(id, "Terdeteksi suhu ruangan meningkat di Koperasi Pakem Berkah Bersama ");
  }
  if(sensorReading == 0 && sensorSmoke > 450 && suhu > 33){
    digitalWrite(pinBuzzer,HIGH);
    Serial.println("Terdeteksi Kebakaran");
    myBot.sendMessage(id, "Terdeteksi kebakaran di Koperasi Pakem Berkah Bersama ");
  }
    digitalWrite(pinBuzzer,LOW);
    Serial.println("Fire Not Detected");
  delay(1000);
}
