#include <NewPing.h>             //Library untuk HC-SR04
#include <ESP8266WiFi.h>         //library untuk nodemcu
#include <BlynkSimpleEsp8266.h>  //library untuk blynk

#define TRIGGER_PIN D5    //Pin Trigger HC-SR04 pada NodeMCU
#define ECHO_PIN D6       //Pin Echo HC-SR04 pada NodeMCU
#define MAX_DISTANCE 250  //Maksimum Pembacaan Jarak (cm)

#define BLYNK_TEMPLATE_ID "TMPL6MgAxW8JI"
#define BLYNK_TEMPLATE_NAME "Posttest2"
#define BLYNK_AUTH_TOKEN "XsfIePFslY6kOLq3C6eiVQvnqN8mnFsg"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Universitas Mulawarman";  // type your wifi name
char pass[] = "";                        // type your wifi password

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  //Setup Pin HC-SR04 dan Jarak Pembacaan dengan Fungsi Library

BlynkTimer timer;

void setup() {
  Serial.begin(115200);  //Memulai Komunikasi Serial Monitor
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  // Fungsi mengirim data setiap 2,5 detik
  timer.setInterval(1000L, sendsensor);
}

void loop() {
  Blynk.run();
  timer.run();
}

void sendsensor() {
  float jarak = sonar.ping_cm();  //Melakukan Pembacaan Jarak dalam bentuk cm
  //Mencetak Hasil Pembacaan pada Serial Monitor
  Blynk.virtualWrite(V0, jarak);
  Serial.println("Monitoring Jarak");
  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");
  delay(1000);  //Delay 1 Detik
}