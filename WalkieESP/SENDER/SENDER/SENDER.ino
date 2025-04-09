#include "Arduino.h"
String password = "AA4104132968BA2224299079021594AB"; // AES128 password
String myName = "JasonEdington";
const int RADIOADDRESS = 0xC8;
const int TIMEZONE = -6;
// Define Constants
const int RADIONETWORK = 7;    // range of 0-16
const int SENDADDRESS = 302;   // address of radio to be sent to
const unsigned int UPDATE = 3000;
unsigned int lastGPS;
// Declare Functions
void sendData(String name);
void reyaxSetup(String password);
void setup() {
  Serial.begin(115200);
  reyaxSetup(password);
}
void loop() {
  if (Serial.available())  { // full incoming buffer: +RCV=203,50,35.08,9,-36,41
    String parse0 = Serial.readStringUntil('=');  //+RCV
    String parse1 = Serial.readStringUntil(',');  // address received from
    String parse2 = Serial.readStringUntil(',');  // buffer length
    String parse3 = Serial.readStringUntil(',');  // fuseSound
    String parse4 = Serial.readStringUntil(',');  // fuseDust
    String parse5 = Serial.readStringUntil(',');  // rssi
    String parse6 = Serial.readStringUntil('\n'); // snr
    String parse7 = Serial.readString();          // extra
    sendData(myName);
    delay(100);
  }
}
void sendData(String name) {
  char buffer[60];
  sprintf(buffer, "AT+SEND=%i,60,%s\r\n", SENDADDRESS,name.c_str());
  Serial1.printf("%s",buffer);
  //Serial1.println(buffer);
  delay(1000);
  if (Serial.available() > 0)
  {
    String reply = Serial1.readStringUntil('\n');
  }
}
void reyaxSetup(String password) {
  // following four paramaters have most significant effect on range
  // recommended within 3 km: 10,7,1,7
  // recommended more than 3 km: 12,4,1,7
  const int SPREADINGFACTOR = 10;
  const int BANDWIDTH = 7;
  const int CODINGRATE = 1;
  const int PREAMBLE = 7;
  String reply; // string to store replies from module
  Serial1.printf("AT+ADDRESS=%i\r\n", RADIOADDRESS); // set the radio address
  delay(200);
  if (Serial.available() > 0) {
    reply = Serial.readStringUntil('\n');
  }
  Serial.printf("AT+NETWORKID=%i\r\n", RADIONETWORK); // set the radio network
  delay(200);
  if (Serial.available() > 0) {
    reply = Serial.readStringUntil('\n');
  }
  Serial.printf("AT+CPIN=%s\r\n", password.c_str());
  delay(200);
  if (Serial.available() > 0) {
    reply = Serial.readStringUntil('\n');
  }
  Serial.printf("AT+PARAMETER=%i,%i,%i,%i\r\n", SPREADINGFACTOR, BANDWIDTH, CODINGRATE, PREAMBLE);
  delay(200);
  if (Serial.available() > 0) {
    reply = Serial.readStringUntil('\n');
  }
  Serial.printf("AT+ADDRESS?\r\n");
  delay(200);
  if (Serial.available() > 0) {
    reply = Serial.readStringUntil('\n');
  }
  Serial.printf("AT+NETWORKID?\r\n");
  delay(200);
  if (Serial.available() > 0) {
    reply = Serial.readStringUntil('\n');
  }
  Serial.printf("AT+PARAMETER?\r\n");
  delay(200);
  if (Serial.available() > 0) {
    reply = Serial.readStringUntil('\n');
  }
  Serial.printf("AT+CPIN?\r\n");
  delay(200);
  if (Serial.available() > 0) {
    reply = Serial.readStringUntil('\n');
  }
}