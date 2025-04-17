#include <Particle.h>
//#include <Adafruit_GPS.h>
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"



Adafruit_SSD1306 display(-1);
//Adafruit_GPS GPS(&Wire);

// Define User and Credentials
String password = "AA4104132968BA2224299079021594AB"; // AES128 password
String myName = "IoTFreq";
const int RADIOADDRESS = 302; // Get address from Instructor, it will be a value between 0xC1 - 0xCF
const int TIMEZONE = -6;

// Define Constants
const int RADIONETWORK = 7;    // range of 0-16
const int SENDADDRESS = 0x00;   // address of radio to be sent to

// Declare Variables
float lat, lon, alt;
int sat;
unsigned long currentTime, lastTime;

void sendData(String name, float latitude, float longitude, int satelittes);
void reyaxSetup(String password);
SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected, 5000);

  Serial1.begin(115200);
  reyaxSetup(password);
  delay(2000);
  //sendData(myName, 33.400322, -104.534897, 0);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  display.display(); // show splashscreen
  //delay(2000);
  
  display.setTextColor(WHITE);
  display.setTextSize(1);
  
  display.clearDisplay();   // clears the screen and buffer
  //display.setRotation(2);
  display.display();
 

  // GPS.begin(0x10);  // The I2C address to use is 0x10
  // GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); 
  // GPS.sendCommand(PGCMD_ANTENNA);
  // delay(1000);
  // GPS.println(PMTK_Q_RELEASE);
  // delay(1500);
  
  
  
  

}

void loop() {
  currentTime = millis();
  
  // GPS.read();
  // if (GPS.newNMEAreceived()) {
  //   if (!GPS.parse(GPS.lastNMEA())) {
  //     return;
  //   }   
  // }
  
  //listen for incoming lora messages and then send GPS back
  if (Serial1.available())  { // full incoming buffer: +RCV=203,50,35.08,9,-36,41 
    display.clearDisplay();
    display.setCursor(0,0);
    display.display();
    String parse0 = Serial1.readStringUntil('=');  //+RCV
    String parse1 = Serial1.readStringUntil(',');  // address received from
    String parse2 = Serial1.readStringUntil(',');  // buffer length
    String parse3 = Serial1.readStringUntil(',');  // picPart
    // String parse4 = Serial1.readStringUntil(',');  // fuseDust
    String parse5 = Serial1.readStringUntil(',');  // rssi
    String parse6 = Serial1.readStringUntil('\n'); // snr
    String parse7 = Serial1.readString();          // extra

    Serial.printf("parse1: %s\nparse3: %s\nparse5: %s\n" ,  parse1.c_str(), parse3.c_str(), parse5.c_str());
    //Serial.printf("parse0: %s\nparse1: %s\nparse2: %s\nparse3: %s\nparse5: %s\nparse6: %s\nparse7: %s\n", parse0.c_str(), parse1.c_str(), parse2.c_str(), parse3.c_str(), parse5.c_str(), parse6.c_str(), parse7.c_str());
    delay(100);
    //sendData(myName,39.9612, 82.9988, 5);
    display.printf("parse1: %s\nparse3: %s\nparse5: %s\n" ,  parse1.c_str(), parse3.c_str(), parse5.c_str());
    display.display();
    
  }
  // if((currentTime - lastTime) > 10000){
  //   sendData(myName,39.9612, 82.9988, 5);
  //   lastTime = millis();
  // }
}

// void getGPS(float *latitude, float *longitude, float *altitude, int *satellites) {
//   int theHour;
//   //display.clearDisplay();   // clears the screen and buffer
  

//   theHour = GPS.hour + TIMEZONE;
//   if (theHour < 0) {
//     theHour = theHour + 24;
//   }

//   Serial.printf("Time: %02i:%02i:%02i:%03i\n", theHour, GPS.minute, GPS.seconds, GPS.milliseconds);
//   //display.printf("Time: %02i:%02i:%02i:%03i\n", theHour, GPS.minute, GPS.seconds, GPS.milliseconds);
  
//   Serial.printf("Dates: %02i-%02i-%02i\n", GPS.month, GPS.day, GPS.year);
//   Serial.printf("Fix: %i, Quality: %i", (int)GPS.fix, (int)GPS.fixquality);
  
  
//   if (GPS.fix) {
//     *latitude = GPS.latitudeDegrees;
//     *longitude = GPS.longitudeDegrees;
//     *altitude = GPS.altitude;
//     *satellites = (int)GPS.satellites;
//   }
// }

void sendData(String name, float latitude, float longitude, int satelittes) {
  display.clearDisplay();   // clears the screen and buffer
  display.setCursor(0,0);
  display.display();
  char buffer[60];
  sprintf(buffer, "AT+SEND=%i,60,%f,%f,%i,%s\r\n", SENDADDRESS, latitude, longitude, satelittes, name.c_str());
  Serial1.printf("%s",buffer);
  display.printf("%s", buffer);
  //Serial1.println(buffer); 
  delay(1000);
  if (Serial1.available() > 0)
  {
    Serial.printf("Awaiting Reply from send\n");
    String reply = Serial1.readStringUntil('\n');
    Serial.printf("Send reply: %s\n", reply.c_str());
    display.printf("Send reply: %s\n", reply.c_str());
    display.display();
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
  if (Serial1.available() > 0) {
    Serial.printf("Awaiting Reply from address\n");
    reply = Serial1.readStringUntil('\n');
    Serial.printf("Reply address: %s\n", reply.c_str());
  }

  Serial1.printf("AT+NETWORKID=%i\r\n", RADIONETWORK); // set the radio network
  delay(200);
  if (Serial1.available() > 0) {
    Serial.printf("Awaiting Reply from networkid\n");
    reply = Serial1.readStringUntil('\n');
    Serial.printf("Reply network: %s\n", reply.c_str());
  }

  Serial1.printf("AT+CPIN=%s\r\n", password.c_str());
  delay(200);
  if (Serial1.available() > 0) {
    Serial.printf("Awaiting Reply from password\n");
    reply = Serial1.readStringUntil('\n');
    Serial.printf("Reply: %s\n", reply.c_str());
  }

  Serial1.printf("AT+PARAMETER=%i,%i,%i,%i\r\n", SPREADINGFACTOR, BANDWIDTH, CODINGRATE, PREAMBLE);
  delay(200);
  if (Serial1.available() > 0) {
    reply = Serial1.readStringUntil('\n');
    Serial.printf("reply: %s\n", reply.c_str());
  }

  Serial1.printf("AT+ADDRESS?\r\n");
  delay(200);
  if (Serial1.available() > 0) {
    Serial.printf("Awaiting Reply\n");
    reply = Serial1.readStringUntil('\n');
    Serial.printf("Radio Address: %s\n", reply.c_str());
  }

  Serial1.printf("AT+NETWORKID?\r\n");
  delay(200);
  if (Serial1.available() > 0) {
    Serial.printf("Awaiting Reply\n");
    reply = Serial1.readStringUntil('\n');
    Serial.printf("Radio Network: %s\n", reply.c_str());
  }

  Serial1.printf("AT+PARAMETER?\r\n");
  delay(200);
  if (Serial1.available() > 0) {
    Serial.printf("Awaiting Reply\n");
    reply = Serial1.readStringUntil('\n');
    Serial.printf("RadioParameters: %s\n", reply.c_str());
  }

  Serial1.printf("AT+CPIN?\r\n");
  delay(200);
  if (Serial1.available() > 0) {
    Serial.printf("Awaiting Reply\n");
    reply = Serial1.readStringUntil('\n');
    Serial.printf("Radio Password: %s\n", reply.c_str());
  }
}