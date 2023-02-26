#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#define Wall_Switch1  13
#define Wall_Switch2  12
#define Wall_Switch3  14
#define Wall_Switch4  26
#define Wall_Switch5  25
#define Wall_Switch6  33
#define Wall_Door  32

#define Switch1  15
#define Switch2  4
#define Switch3  18
#define Switch4  19
#define Switch5  21
#define Switch6  22
#define Door  23
byte checksw1 = 0;
byte checksw2 = 0;
byte checksw3 = 0;
byte checksw4 = 0;
byte checksw5 = 0;
byte checksw6 = 0;
byte checkDoor = 0;
const char* ssid     = "CED-IOT";
const char* password = "adminced.tct";
const char* mqtt_server = "202.44.35.76";
const int mqtt_port = 1883;
const char* mqtt_Client = "44702";
const char* mqtt_username = "sclass";
const char* mqtt_password = "class44702";
WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  while (!client.connected()) {
    if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
      client.subscribe("/Switch1");
      client.subscribe("/Switch2");
      client.subscribe("/Switch3");
      client.subscribe("/Switch4");
      client.subscribe("/Switch5");
      client.subscribe("/Switch6");
      client.subscribe("/Door44-702");
      digitalWrite(LED_BUILTIN, 1);
      digitalWrite(5, 1);}
    else{
      digitalWrite(LED_BUILTIN, 0);
      digitalWrite(5, 0);
      control();
    }
  }
}
void control(){
  if(digitalRead(Wall_Switch1)==0){
    checksw1 ++;
  }while (digitalRead(Wall_Switch1) == 0) delay(10);
   if(checksw1>=2){
      checksw1=0; }
     if(checksw1 == 1){digitalWrite(Switch1,1);
       client.publish("/data_update_Switch1", "Status Update Light Mode1 On");}
     else if(checksw1 == 0){digitalWrite(Switch1,0);
       client.publish("/data_update_Switch1", "Status Update Light Mode1 Off");}
  if(digitalRead(Wall_Switch2)==0){
    checksw2 ++;
  }while (digitalRead(Wall_Switch2) == 0) delay(10);
   if(checksw2>=2){
      checksw2=0;} 
     if(checksw2 == 1){digitalWrite(Switch2,1);
      client.publish("/data_update_Switch2", "Status Update Light Mode2 On");}
     else if(checksw2 == 0){digitalWrite(Switch2,0);
      client.publish("/data_update_Switch2", "Status Update Light Mode2 Off");}
  if(digitalRead(Wall_Switch3)==0){
     checksw3 ++;
  }while (digitalRead(Wall_Switch3) == 0) delay(10);
     if(checksw3>=2){
      checksw3=0;} 
     if(checksw3 == 1){digitalWrite(Switch3,1);
       client.publish("/data_update_Switch3", "Status Update Light Mode3 On");}
     else if(checksw3 == 0){digitalWrite(Switch3,0);
       client.publish("/data_update_Switch3", "Status Update Light Mode3 Off");}
   ////////////////////////////////////////////////
  if(digitalRead(Wall_Switch4)==0){
    checksw4 ++;
  }while (digitalRead(Wall_Switch4) == 0) delay(10);
     if(checksw4>=2){
        checksw4=0;} 
     if(checksw4 == 1){digitalWrite(Switch4,1);
        client.publish("/data_update_Switch4", "Status Update Light Mode4 On");}
     else if(checksw4 == 0){digitalWrite(Switch4,0);
        client.publish("/data_update_Switch4", "Status Update Light Mode4 Off");}
  if(digitalRead(Wall_Switch5)==0){
    checksw5 ++;
  }while (digitalRead(Wall_Switch5) == 0) delay(10);
     if(checksw5>=2){
      checksw5=0;} 
     if(checksw5 == 1){digitalWrite(Switch5,1);
      client.publish("/data_update_Switch5", "Status Update Light Mode5 On");}
     else if(checksw5 == 0){digitalWrite(Switch5,0);
      client.publish("/data_update_Switch5", "Status Update Light Mode5 Off");}
  if(digitalRead(Wall_Switch6)==0){
    checksw6 ++;
  }while (digitalRead(Wall_Switch6) == 0) delay(10);
    if(checksw6>=2){
      checksw6=0;} 
    if(checksw6 == 1){digitalWrite(Switch6,1);
      client.publish("/data_update_Switch6", "Status Update Light Mode6 On");}
    else if(checksw6 == 0){digitalWrite(Switch6,0);
      client.publish("/data_update_Switch6", "Status Update Light Mode6 Off");}
  if(digitalRead(Wall_Door)==0){
    checkDoor ++;
  }while (digitalRead(Wall_Door) == 0) delay(10);
    if(checkDoor>=2){
      checkDoor=0;} 
    if(checkDoor == 1){digitalWrite(Door,1);
      client.publish("/data_update_Door", "Status Update Door44-702 On");}
    else if(checkDoor == 0){digitalWrite(Door,0);
      client.publish("/data_update_Door", "Status Update Door44-702 Off");}
}
void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  String topic_str = topic, payload_str = (char*)payload;
  String message;
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];
  }
  if(String(topic) == "/Switch1"){
    if (message == "on"){
      checksw1 = 1;}
    else if (message == "off"){
        checksw1 = 0;}
  }
 if(String(topic) == "/Switch2"){
    if (message == "on"){
      checksw2 = 1;}
    else if (message == "off"){
      checksw2 = 0;}
  }
 if(String(topic) == "/Switch3"){
    if (message == "on"){
      checksw3 = 1;}
    else if (message == "off"){
      checksw3 = 0;}
  }
 if(String(topic) == "/Switch4"){
    if (message == "on"){
      checksw4 = 1;}
    else if (message == "off"){
      checksw4 = 0;}
  }
 if(String(topic) == "/Switch5"){
    if (message == "on"){
      checksw5 = 1;}
    else if (message == "off"){
      checksw5 = 0;}
  }
 if(String(topic) == "/Switch6"){
  if (message == "on"){
      checksw6 = 1;}
    else if (message == "off"){
      checksw6 = 0;}
  }
 if(String(topic) == "/Door44-702"){
  if (message == "on"){
      checkDoor = 1;}
    else if (message == "off"){
      checkDoor = 0;}
  }
}

void setup() {
   Serial.begin(115200);
  Wire1.begin(4, 5);
  pinMode(Wall_Switch1,INPUT_PULLUP);
  pinMode(Wall_Switch2,INPUT_PULLUP);
  pinMode(Wall_Switch3,INPUT_PULLUP);
  pinMode(Wall_Switch4,INPUT_PULLUP);
  pinMode(Wall_Switch5,INPUT_PULLUP);
  pinMode(Wall_Switch6,INPUT_PULLUP);
  pinMode(Wall_Door,INPUT_PULLUP);
  pinMode(Switch1,OUTPUT);
  digitalWrite(Switch1,0);
  pinMode(Switch2,OUTPUT);
  digitalWrite(Switch2,0);
  pinMode(Switch3,OUTPUT);
  digitalWrite(Switch3,0);
  pinMode(Switch4,OUTPUT);
  digitalWrite(Switch4,0);
  pinMode(Switch5,OUTPUT);
  digitalWrite(Switch5,0);
  pinMode(Switch6,OUTPUT);
  digitalWrite(Switch6,0);
  pinMode(Door,OUTPUT);
  digitalWrite(Door,0);
  if (WiFi.begin(ssid, password)) {
    while (WiFi.status() != WL_CONNECTED) {
    }
  }
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(5, OUTPUT);
}
void loop() {  
  control();
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  delay(1);
}
