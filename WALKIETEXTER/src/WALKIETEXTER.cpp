#include<Keypad_Particle.h>
#include "Particle.h"
const byte ROWS = 3;
const byte COLS = 3;
int lastC;
int pressed = 0;
int mesNum;
int theFogIsComing[9];
String MESSAGE[50];
SYSTEM_MODE(SEMI_AUTOMATIC);
char customKey;
void clicky(int OKEY);
char hexaKeys [ ROWS ][ COLS ] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'}
  };

  byte rowPins [ROWS]={D2,D3,D4};// 1 st to 4 th Keypad pins ( starting on left )
  byte colPins [COLS]={D5,D6,D7}; // 5 th to 8 th Keypad pins
     Keypad customKeypad = Keypad(makeKeymap(hexaKeys),rowPins,colPins, ROWS, COLS);
     void setup () {
  Serial.begin(9600) ;
  waitFor(Serial.isConnected,10000) ;
  }
     void loop () {
  customKey = customKeypad.getKey();
     if(customKey) {
  Serial.printf ("Key Pressed:%c\n",customKey);
  Serial.printf("Key Pressed (Hex Code)0x%02X\n",customKey); // ASCII Hex value
      if(customKey == '1'){
        if(lastC != customKey){
          pressed = 0;
        }
        lastC = '1';
        pressed ++;
      }
      if(customKey == '2'){
        if(lastC != customKey){
          pressed = 0;
        }
        lastC = '2';
        pressed ++;
      }
      if(customKey == '3'){
        if(lastC != customKey){
          pressed = 0;
        }
        lastC = '3';
        pressed ++;
      }
      if(customKey == '4'){
        if(lastC != customKey){
          pressed = 0;
        }
        lastC = '4';
        pressed ++;
      }
      if(customKey == '5'){
        if(lastC != customKey){
          pressed = 0;
        }
        lastC = '5';
        pressed ++;
      }
      if(customKey == '6'){
        if(lastC != customKey){
          pressed = 0;
        }
        lastC = '6';
        pressed ++;
      }
      if(customKey == '7'){
        if(lastC != customKey){
          pressed = 0;
        }
        lastC = '7';
        pressed ++;
      }
      if(customKey == '8'){
        if(lastC != customKey){
          pressed = 0;
        }
        lastC = '8';
        pressed ++;
      }
      if(customKey == '8'){
        
      }
      mesNum++;
  }
 }




