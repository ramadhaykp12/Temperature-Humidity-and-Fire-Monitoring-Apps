#define BLYNK_TEMPLATE_ID "TMPLW4ujpnPf"
#define BLYNK_DEVICE_NAME "Blynk API"
#define BLYNK_AUTH_TOKEN "3tRlv0RUItetWLdFG9ESFUTUXH6jxRi0"
#include <ESP8266WiFi.h> // include library
#include <BlynkSimpleEsp8266.h> // include library
#include <DHT.h> //Library untuk DHT
#define DHTPIN D3 //deklarasi pin D3 untuk output dari DHT11
#define DHTTYPE DHT11 //Tipe DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
char auth[] = BLYNK_AUTH_TOKEN ; //Auth Token

char ssid[] = "ssid"; //nama hotspot yang digunakan
char pass[] = "password"; //password hotspot yang digunakan

// lowest and highest sensor readings:
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum

//function untuk pengiriman sensor
void kirimDataSensor()
{
float t = dht.readTemperature(); //pembacaan sensor
float h = dht.readHumidity();
int sensorReading = analogRead(A0);
int range = map(sensorReading, sensorMin, sensorMax, 0, 3); //Menentukan range sensor 
Serial.print("% Temperature: ");
Serial.print(t);
Serial.println("C ");
Serial.print("% Kelembaban: ");
Serial.print(h);
Serial.println("% ");

//Untuk Kondisi Sensor Api
switch (range) {
  case 0:    // api sangat dekat
    Blynk.virtualWrite(V4,"Kebakaran");
    break;
  case 1:    // ada api 
    Blynk.virtualWrite(V4,"Ada Api");
    break;
  case 2:    // tidak ada api
    Blynk.virtualWrite(V4,"Aman");
    break;
  }
  delay(1);  // delay between reads
Blynk.virtualWrite(V2, t); //mengirimkan data temperatur ke Virtual pin VO di Blynk Cloud
Blynk.virtualWrite(V3, h); //mengirimkan data kelemaban ke Virtual pin V1 di Blynk Cloud

}
void setup() {
Serial.begin(115200); //serial monitor menggunakan bautrate 9600
Blynk.begin(auth, ssid, pass); //memulai Blynk
dht.begin(); //mengaktifkan DHT11
timer.setInterval(1000L, kirimDataSensor); //Mengaktifkan timer untuk pengiriman data 1000ms
}

void loop() {
Blynk.run(); //menjalankan blynk
timer.run(); //menjalankan timer
}
