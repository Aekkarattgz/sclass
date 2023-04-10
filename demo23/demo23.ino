#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#define Wall_Switch1  13
#define Wall_Switch2  12
#define Wall_Switch3  14
#define Wall_Switch4  26
#define Wall_Switch5  25
#define Wall_Switch6  33
#define Wall_Door  32
#define Reed_Switch  2
#define Switch1  15
#define Switch2  4
#define Switch3  18
#define Switch4  19
#define Switch5  21
#define Switch6  22
#define Door  23
#define LED_Status  5
byte checksw1 = 0;
byte checksw2 = 0;
byte checksw3 = 0;
byte checksw4 = 0;
byte checksw5 = 0;
byte checksw6 = 0;
byte checkDoor = 0;
byte checkReed = 0;
byte checkReed_Table = 0;
byte checkTable = 0;
const char* ssid     = "CED-IOT";
const char* password = "adminced.tct";
const char* mqtt_server = "202.44.35.76";
const int mqtt_port = 1883;
const char* mqtt_Client = "44702";
const char* mqtt_username = "sclass";
const char* mqtt_password = "class44702";
WiFiClient espClient;
PubSubClient client(espClient);
const uint16_t kIrLed1 = 27;
IRsend irsend1(kIrLed1);
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
      client.subscribe("/Air");
      client.subscribe("/Table");
      digitalWrite(LED_BUILTIN, 1);
      digitalWrite(LED_Status, 1);
      Serial.println("client.connect");
  }
    else{
      digitalWrite(LED_BUILTIN, 1);
      digitalWrite(LED_Status,1);
      delay(500);
      digitalWrite(LED_BUILTIN, 0);
      digitalWrite(LED_Status,0);
      control();
      Serial.println("client.disconnect");
    }
  }
}
void setup() {
  irsend1.begin();
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // 
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
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);
  pinMode(LED_Status,OUTPUT);
  digitalWrite(LED_Status,0);
  if (WiFi.begin(ssid, password)) {
    while (WiFi.status() != WL_CONNECTED) {
      Serial.println("wifi");
      digitalWrite(LED_BUILTIN, 1);
      digitalWrite(LED_Status,1);
      delay(500);
      digitalWrite(LED_BUILTIN, 0);
      digitalWrite(LED_Status,0);
      control();
    }
  }
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}
uint16_t rawData_ON18[131] = {9244, 4462,  642, 462,  590, 1568,  588, 1566,  640, 464,  588, 1566,  642, 464,  640, 464,  640, 464,  640, 462,  590, 1566,  640, 464,  640, 464,  640, 464,  640, 464,  588, 1568,  590, 1566,  642, 462,  640, 464,  640, 464,  640, 464,  640, 464,  640, 462,  642, 462,  640, 464,  640, 464,  640, 462,  642, 464,  640, 464,  640, 464,  642, 462,  640, 464,  640, 464,  640, 464,  640, 464,  640, 464,  640, 464,  640, 464,  640, 464,  638, 464,  640, 464,  588, 1566,  642, 464,  588, 1568,  642, 464,  640, 464,  640, 464,  640, 464,  588, 1568,  640, 464,  640, 464,  640, 464,  640, 464,  640, 464,  586, 1568,  588, 1568,  588, 1568,  642, 462,  642, 462,  642, 464,  640, 464,  588, 1568,  640, 464,  640, 464,  640, 464,  508};  // UNKNOWN 4866B7C7
uint16_t rawData_ON19[131] = {9238, 4466,  638, 466,  584, 1572,  586, 1570,  640, 466,  584, 1570,  640, 464,  638, 466,  642, 462,  640, 464,  588, 1568,  642, 462,  660, 442,  642, 464,  588, 1568,  660, 444,  658, 444,  660, 444,  660, 442,  662, 442,  662, 442,  660, 442,  662, 442,  662, 442,  662, 442,  662, 442,  662, 442,  662, 444,  660, 444,  662, 442,  662, 442,  662, 440,  664, 440,  664, 442,  662, 444,  660, 444,  660, 442,  660, 444,  660, 444,  660, 444,  640, 464,  588, 1568,  642, 464,  640, 464,  586, 1568,  640, 466,  638, 466,  640, 464,  586, 1570,  640, 464,  638, 468,  636, 468,  638, 464,  636, 468,  584, 1572,  584, 1572,  582, 1574,  634, 470,  632, 472,  634, 472,  634, 470,  580, 1576,  632, 472,  630, 474,  634, 470,  500};  // CARRIER_AC64 10E0890000002216
uint16_t rawData_ON20[131] =  {9268, 4436,  666, 438,  610, 1546,  610, 1546,  664, 440,  610, 1548,  662, 442,  664, 438,  662, 442,  662, 442,  610, 1546,  662, 442,  664, 444,  658, 446,  604, 1550,  658, 448,  608, 1546,  664, 440,  660, 446,  654, 448,  608, 528,  628, 442,  658, 448,  606, 496,  608, 496,  658, 448,  654, 448,  608, 498,  658, 444,  664, 442,  606, 496,  662, 444,  660, 444,  608, 500,  658, 442,  662, 442,  608, 496,  658, 446,  660, 446,  662, 440,  664, 438,  608, 1550,  662, 442,  660, 446,  658, 446,  660, 442,  606, 498,  664, 440,  602, 1554,  660, 444,  660, 444,  656, 446,  658, 448,  664, 440,  612, 1544,  610, 1546,  612, 1544,  660, 444,  658, 448,  662, 442,  660, 444,  610, 1546,  664, 440,  662, 440,  664, 442,  536};  // UNKNOWN 9D0C3D52
uint16_t rawData_ON21[131] =  {9244, 4462,  640, 464,  588, 1568,  588, 1570,  640, 462,  590, 1568,  642, 464,  640, 462,  642, 464,  640, 464,  588, 1570,  640, 464,  642, 462,  642, 464,  588, 1568,  588, 1568,  642, 464,  640, 464,  640, 464,  638, 464,  642, 464,  640, 464,  642, 464,  640, 464,  640, 464,  642, 464,  640, 464,  642, 462,  640, 464,  640, 464,  640, 464,  640, 464,  640, 464,  640, 464,  640, 464,  640, 464,  640, 462,  640, 464,  640, 464,  640, 464,  640, 464,  640, 464,  586, 1568,  588, 1568,  586, 1570,  642, 464,  638, 464,  640, 464,  588, 1568,  642, 462,  640, 464,  640, 464,  640, 464,  640, 466,  586, 1570,  588, 1568,  586, 1570,  640, 464,  640, 464,  640, 464,  640, 464,  588, 1570,  638, 464,  642, 464,  640, 464,  508};  // UNKNOWN 303F7905
uint16_t rawData_ON22[131] = {9264, 4442,  658, 446,  606, 1548,  610, 1548,  644, 462,  608, 1548,  660, 442,  662, 444,  660, 444,  660, 444,  608, 1548,  662, 444,  660, 442,  660, 444,  590, 1566,  590, 1566,  610, 1546,  644, 462,  662, 444,  660, 442,  662, 442,  660, 444,  660, 444,  660, 446,  660, 442,  642, 462,  642, 462,  640, 464,  642, 464,  640, 462,  642, 462,  642, 462,  642, 462,  642, 462,  642, 462,  642, 464,  640, 462,  642, 462,  642, 464,  640, 462,  640, 464,  640, 464,  588, 1566,  590, 1566,  642, 464,  640, 464,  640, 464,  640, 464,  588, 1568,  642, 464,  640, 464,  640, 464,  640, 464,  638, 466,  588, 1570,  586, 1570,  588, 1568,  640, 464,  642, 464,  638, 464,  640, 464,  588, 1568,  640, 466,  638, 464,  640, 464,  508};  // UNKNOWN 1B7B4685
uint16_t rawData_ON23[131] = {9244, 4462,  642, 464,  586, 1568,  590, 1566,  642, 462,  588, 1568,  642, 464,  640, 464,  642, 464,  640, 462,  588, 1568,  640, 464,  642, 462,  588, 1566,  642, 462,  642, 464,  640, 464,  640, 464,  640, 464,  640, 462,  640, 464,  642, 462,  640, 462,  642, 464,  640, 464,  640, 464,  642, 462,  640, 464,  640, 462,  642, 464,  640, 462,  642, 462,  642, 462,  640, 462,  642, 462,  642, 464,  640, 464,  640, 464,  642, 462,  640, 464,  640, 464,  640, 464,  588, 1568,  642, 462,  588, 1568,  640, 464,  642, 462,  640, 464,  588, 1568,  642, 462,  640, 464,  642, 464,  640, 462,  640, 462,  590, 1568,  586, 1570,  588, 1568,  642, 462,  642, 462,  640, 464,  640, 464,  588, 1568,  640, 464,  640, 464,  640, 464,  508};  // UNKNOWN D075A9D3
uint16_t rawData_ON24[131] = {9240, 4464,  638, 466,  584, 1572,  584, 1570,  638, 468,  586, 1570,  636, 468,  636, 466,  640, 466,  638, 466,  586, 1570,  638, 464,  636, 468,  586, 1570,  638, 466,  640, 466,  584, 1570,  640, 464,  638, 466,  638, 466,  636, 468,  636, 468,  636, 468,  638, 466,  636, 468,  636, 466,  636, 468,  636, 468,  636, 468,  636, 468,  638, 466,  636, 468,  636, 468,  634, 470,  636, 468,  634, 468,  634, 470,  634, 470,  632, 474,  626, 478,  632, 470,  632, 472,  578, 1578,  628, 476,  632, 472,  630, 474,  578, 526,  630, 474,  576, 1580,  630, 474,  578, 526,  578, 526,  578, 524,  580, 526,  526, 1630,  526, 1630,  526, 1630,  578, 526,  578, 526,  578, 526,  578, 526,  526, 1630,  580, 524,  628, 476,  578, 526,  446};  // UNKNOWN 632A90D3
uint16_t rawData_ON25[131] = {9268, 4466,  638, 466,  586, 1570,  586, 1570,  638, 466,  610, 1546,  638, 466,  638, 466,  638, 466,  636, 468,  584, 1572,  638, 468,  636, 470,  584, 1570,  640, 466,  608, 1548,  636, 466,  638, 466,  636, 466,  638, 468,  636, 466,  660, 444,  636, 468,  638, 466,  638, 468,  636, 466,  638, 466,  638, 466,  638, 466,  636, 468,  638, 466,  638, 466,  638, 466,  638, 468,  636, 466,  638, 466,  636, 466,  638, 466,  638, 466,  662, 442,  636, 468,  638, 466,  636, 468,  584, 1570,  586, 1570,  640, 466,  638, 466,  638, 466,  586, 1572,  638, 466,  638, 468,  636, 466,  636, 468,  636, 468,  586, 1570,  586, 1570,  610, 1546,  638, 466,  636, 468,  638, 466,  638, 466,  586, 1570,  638, 468,  636, 468,  636, 468,  506};  // UNKNOWN 40588247
uint16_t rawData_ON26[131] = {9244, 4462,  640, 464,  586, 1568,  588, 1568,  640, 464,  588, 1568,  642, 462,  640, 464,  640, 464,  640, 464,  588, 1570,  640, 464,  640, 464,  588, 1568,  640, 464,  586, 1570,  588, 1570,  640, 464,  640, 464,  640, 464,  640, 464,  640, 464,  640, 462,  640, 464,  638, 464,  640, 464,  640, 464,  640, 464,  640, 464,  640, 466,  638, 464,  640, 466,  638, 464,  640, 464,  640, 466,  638, 468,  636, 464,  640, 464,  640, 464,  638, 466,  638, 464,  640, 464,  640, 464,  586, 1570,  640, 464,  640, 464,  640, 464,  640, 466,  586, 1570,  640, 464,  640, 464,  638, 464,  640, 464,  638, 466,  586, 1568,  588, 1568,  588, 1570,  640, 464,  640, 464,  642, 464,  640, 464,  586, 1570,  640, 464,  642, 462,  640, 466,  508};  // UNKNOWN 2B944FC7
uint16_t rawData_ON27[131] = {9242, 4464,  638, 466,  584, 1572,  584, 1574,  634, 470,  582, 1574,  636, 470,  634, 468,  638, 466,  636, 466,  584, 1574,  630, 474,  634, 470,  582, 1574,  578, 1578,  630, 474,  636, 468,  636, 468,  634, 472,  634, 470,  634, 470,  628, 476,  632, 472,  630, 474,  578, 526,  632, 472,  580, 526,  632, 472,  578, 526,  578, 526,  626, 478,  578, 526,  578, 526,  628, 476,  578, 526,  628, 476,  578, 526,  578, 526,  628, 476,  578, 526,  578, 526,  630, 474,  632, 472,  628, 476,  578, 1578,  632, 472,  634, 470,  628, 476,  578, 1578,  632, 472,  632, 472,  578, 526,  634, 470,  632, 474,  580, 1576,  582, 1574,  582, 1574,  630, 476,  632, 470,  628, 476,  630, 474,  580, 1576,  634, 470,  634, 470,  634, 470,  502};  // UNKNOWN 978A7921
uint16_t rawData_ON28[131] = {9234, 4472,  634, 470,  578, 1578,  582, 1576,  628, 476,  580, 1578,  632, 470,  632, 472,  632, 472,  632, 472,  580, 1576,  634, 470,  632, 472,  576, 1580,  580, 1576,  634, 472,  580, 1574,  632, 474,  632, 470,  632, 472,  634, 470,  628, 476,  634, 470,  632, 472,  630, 476,  630, 472,  630, 474,  626, 476,  632, 472,  634, 472,  630, 472,  626, 478,  632, 470,  632, 472,  630, 474,  632, 472,  634, 472,  630, 474,  628, 476,  630, 474,  628, 476,  632, 472,  632, 472,  632, 474,  578, 526,  578, 526,  632, 472,  578, 526,  574, 1580,  580, 524,  578, 526,  628, 474,  578, 526,  630, 474,  574, 1582,  526, 1630,  526, 1630,  626, 478,  578, 526,  578, 526,  578, 526,  526, 1630,  628, 476,  578, 526,  578, 526,  446};  // UNKNOWN E9888F61
uint16_t rawData_ON29[131] = {9244, 4460,  642, 462,  588, 1568,  588, 1568,  640, 464,  588, 1568,  642, 462,  640, 462,  642, 464,  638, 464,  588, 1568,  640, 464,  640, 462,  588, 1568,  588, 1568,  588, 1568,  640, 464,  640, 464,  640, 464,  640, 464,  640, 464,  638, 466,  640, 462,  642, 462,  642, 462,  642, 462,  642, 462,  640, 464,  640, 464,  640, 464,  640, 464,  640, 464,  640, 464,  640, 464,  640, 466,  638, 464,  640, 464,  640, 464,  640, 464,  640, 464,  640, 464,  588, 1568,  588, 1568,  588, 1570,  588, 1568,  642, 462,  640, 464,  640, 464,  590, 1566,  640, 464,  640, 464,  642, 462,  640, 464,  640, 464,  588, 1568,  588, 1570,  588, 1568,  640, 464,  640, 464,  640, 466,  638, 466,  588, 1568,  640, 464,  640, 464,  640, 464,  510};  // UNKNOWN C854C16D
uint16_t rawData_ON30[131] = {9232, 4474,  632, 474,  526, 1630,  578, 1578,  626, 480,  576, 1580,  632, 472,  630, 474,  578, 526,  578, 526,  578, 1578,  632, 472,  632, 472,  576, 1580,  578, 1578,  578, 1578,  580, 1576,  578, 526,  632, 472,  578, 526,  632, 472,  624, 480,  578, 526,  578, 526,  626, 478,  632, 472,  578, 526,  630, 472,  626, 478,  578, 526,  578, 526,  580, 524,  632, 472,  626, 478,  578, 526,  628, 476,  578, 524,  630, 474,  578, 526,  578, 526,  580, 524,  526, 1628,  576, 1582,  526, 1630,  626, 476,  578, 526,  578, 526,  578, 526,  526, 1628,  626, 478,  580, 526,  578, 528,  578, 526,  578, 526,  526, 1630,  526, 1630,  526, 1630,  578, 526,  578, 526,  624, 478,  580, 526,  526, 1630,  580, 524,  580, 526,  578, 526,  446};  // UNKNOWN B3908EED
uint16_t rawData_OFF[131] = {9244, 4462,  640, 462,  588, 1568,  588, 1568,  640, 464,  640, 464,  630, 474,  642, 464,  640, 464,  640, 464,  588, 1568,  640, 464,  640, 464,  642, 462,  640, 466,  638, 464,  588, 1568,  640, 464,  642, 464,  640, 462,  640, 464,  640, 464,  640, 464,  640, 464,  640, 464,  640, 462,  642, 464,  640, 462,  642, 464,  640, 464,  640, 464,  640, 462,  640, 466,  640, 464,  640, 464,  640, 464,  640, 464,  640, 466,  640, 462,  640, 462,  642, 464,  640, 464,  586, 1570,  640, 464,  642, 462,  640, 464,  640, 464,  640, 464,  588, 1568,  640, 464,  642, 464,  640, 462,  640, 464,  640, 464,  588, 1568,  588, 1570,  588, 1568,  640, 464,  640, 464,  640, 464,  640, 464,  586, 1570,  640, 464,  640, 464,  642, 464,  508};  // UNKNOWN 8843AF63
void control(){
  if(digitalRead(Wall_Switch1)==0){
    checksw1 ++;
  }while (digitalRead(Wall_Switch1) == 0) delay(10);
   if(checksw1>=2){
      checksw1=0; }
     if(checksw1 == 1){digitalWrite(Switch1,1);
       client.publish("/Update_Switch1", "On");}
     else if(checksw1 == 0){digitalWrite(Switch1,0);
       client.publish("/Update_Switch1", "Off");}
  if(digitalRead(Wall_Switch2)==0){
    checksw2 ++;
  }while (digitalRead(Wall_Switch2) == 0) delay(10);
   if(checksw2>=2){
      checksw2=0;} 
     if(checksw2 == 1){digitalWrite(Switch2,1);
      client.publish("/Update_Switch2", "On");}
     else if(checksw2 == 0){digitalWrite(Switch2,0);
      client.publish("/Update_Switch2", "Off");}
  if(digitalRead(Wall_Switch3)==0){
     checksw3 ++;
  }while (digitalRead(Wall_Switch3) == 0) delay(10);
     if(checksw3>=2){
      checksw3=0;} 
     if(checksw3 == 1){digitalWrite(Switch3,1);
       client.publish("/Update_Switch3", "On");}
     else if(checksw3 == 0){digitalWrite(Switch3,0);
       client.publish("/Update_Switch3", "Off");}
  if(digitalRead(Wall_Switch4)==0){
    checksw4 ++;
  }while (digitalRead(Wall_Switch4) == 0) delay(10);
     if(checksw4>=2){
        checksw4=0;} 
     if(checksw4 == 1){digitalWrite(Switch4,1);
        client.publish("/Update_Switch4", "On");}
     else if(checksw4 == 0){digitalWrite(Switch4,0);
        client.publish("/Update_Switch4", "Off");}
  if(digitalRead(Wall_Switch5)==0){
    checksw5 ++;
  }while (digitalRead(Wall_Switch5) == 0) delay(10);
     if(checksw5>=2){
      checksw5=0;} 
     if(checksw5 == 1){digitalWrite(Switch5,1);
      client.publish("/Update_Switch5", "On");}
     else if(checksw5 == 0){digitalWrite(Switch5,0);
      client.publish("/Update_Switch5", "Off");}
  if(digitalRead(Wall_Switch6)==0){
    checksw6 ++;
  }while (digitalRead(Wall_Switch6) == 0) delay(10);
    if(checksw6>=2){
      checksw6=0;} 
    if(checksw6 == 1){digitalWrite(Switch6,1);
      client.publish("/Update_Switch6", "On");}
    else if(checksw6 == 0){digitalWrite(Switch6,0);
      client.publish("/Update_Switch6", "Off");}
  if(checkTable == 0){
    if(digitalRead(Reed_Switch)==0){
        checkReed =0 ;
      }
    else {
      checkReed = 1;
      checkDoor = 0;
      if(digitalRead(Wall_Door)==0){
          digitalWrite(Door,1);
          }while (digitalRead(Wall_Door) == 0) delay(10);
      }
    if(digitalRead(Wall_Door)==0){
      checkDoor ++;
    }while (digitalRead(Wall_Door) == 0) delay(10);
     if(checkDoor>=2){checkDoor=0;} 
      if(checkDoor == 1 && checkReed == 0){
        digitalWrite(Door,1);
        client.publish("/Update_Door44-702", "On");
        }
      else if(checkDoor == 0 && checkReed == 0)
        {digitalWrite(Door,0);
        client.publish("/Update_Door44-702", "Off");
       }      
    }
  if(checkTable == 1){
    if(checkDoor == 1 && checkReed_Table == 0){
        digitalWrite(Door,1);
        client.publish("/Update_Door44-702", "On");
        }
  }
  if (!client.connected()) {
    reconnect();
  }
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
  if(String(topic) == "/Table"){
  if (message == "on"){
      checkTable = 1;
      checkDoor = 1;}
    else if (message == "off"){
      checkTable = 0;
      checkDoor = 0;}
  }
  if (String(topic) == "/Air") {
    if (message == "18") {
      irsend1.sendRaw(rawData_ON18, 131, 38);
    }
    else if (message == "19") {
      irsend1.sendRaw(rawData_ON19, 131, 38);
    }
    else if (message == "20") {
      irsend1.sendRaw(rawData_ON20, 131, 38);
    }
    else if (message == "21") {
      irsend1.sendRaw(rawData_ON21, 131, 38);
    }
    else if (message == "22") {
      irsend1.sendRaw(rawData_ON22, 131, 38);
    }
    else if (message == "23") {
      irsend1.sendRaw(rawData_ON23, 131, 38);
    } 
    else if (message == "24") {
      irsend1.sendRaw(rawData_ON24, 131, 38);
    }
    else if (message == "25") {
      irsend1.sendRaw(rawData_ON25, 131, 38);
    }
    else if (message == "26") {
      irsend1.sendRaw(rawData_ON26, 131, 38);
    }
    else if (message == "27") {
      irsend1.sendRaw(rawData_ON27, 131, 38);
    }
    else if (message == "28") {
      irsend1.sendRaw(rawData_ON28, 131, 38);
    }
    else if (message == "29") {
      irsend1.sendRaw(rawData_ON29, 131, 38);
    }
    else if (message == "30") {
      irsend1.sendRaw(rawData_ON30, 131, 38);
    }
    else if (message == "on") {
      irsend1.sendRaw(rawData_ON22, 131, 38);
    }
    else if (message == "off") {
      irsend1.sendRaw(rawData_OFF, 131, 38);
    }
  }
}
void loop() { 
  control();
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  delay(1);
}
