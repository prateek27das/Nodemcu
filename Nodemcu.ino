#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <Servo.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial

#define FIREBASE_HOST "esp8-14574-default-rtdb.firebaseio.com"                    
#define FIREBASE_AUTH "74DB2qvMVBNoYrjGePyWarWXUQjokiRsa7HfxR04" 

char auth[] = "e_1aCyS7khnyhZtUAZIwIqQaMZJTNi5p";
char ssid[] = "Sharadindu" ;
char pass[] = "Themelware4321beast" ;

#define WIFI_SSID "Sharadindu"                                               
#define WIFI_PASSWORD "Themelware4321beast"  
#define TRIGGER 5 //D1
#define ECHO    4 //D2

FirebaseData firebaseData;

String fireStatus ="";

long duration;
int distance;


Servo myservo;
int n = 0;

void setup() {
  
Serial.begin(9600);

 pinMode(D3, OUTPUT);
 pinMode(D7,OUTPUT);
 pinMode(D4, OUTPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

digitalWrite(D7, HIGH);
myservo.attach(13);

Blynk.begin(auth, ssid, pass);
// connect to wifi.
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                        
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   

  Firebase.reconnectWiFi(true);
  delay(1000);
//Firebase.setString("LED_STATUS", "OFF");
Firebase.setInt(firebaseData,"LOCK_STATUS",0);

}



void loop() {

  
  Blynk.run();
  
Firebase.getInt(firebaseData,"LOCK_STATUS");
n = firebaseData.intData();

  long duration, distance;
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;
  
  Serial.print(distance);
  Serial.println("Centimeter:");
  delay(1000);
  
if(distance > 7)
  {
    Blynk.email("bangladesh1971auth@gmail.com", "Subject:Dhaka School Of Science And Technology", "The Lock has been Broken");
    digitalWrite(D3,HIGH);
    Firebase.setInt(firebaseData,"ALERT",1);
  }
else{
    Firebase.setInt(firebaseData,"ALERT",0);
   
}

if (n==1) {
Serial.println("LED ON");
digitalWrite(D4,HIGH);
myservo.write(60);
return;
delay(10);
}

else {
Serial.println("LED OFF");
digitalWrite(D3,LOW);
myservo.write(8);
digitalWrite(D4,LOW);
return;
}
}
