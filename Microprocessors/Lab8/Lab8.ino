/*
 * Lab8.ino
 * revision date: 29 November 2022
 * Written by: Aaron Luna & Trey Akroosh III 
 * The purpose of this program is to produce a system capable of using IIC to 
 * interact with peripherals without using an excess of GPIO pins.
 * This code is designed for use on the Arduino Mega 2560.
 * The ee3420_mega_aux_board.h header will need to be in the same directory as this file.
 */

#define DEBUG

//commonly useful system libraries
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//added libraries 
#include <Wire.h> 
#include <SPI.h>
#include "Adafruit_EEPROM_I2C.h"

// this is a local library and should be located in the same folder as the source code
#include "ASCII.h"  

/* the ee3420_mega_aux_board.h header includes a lot of setup/shutdown functionality */
/* the header was written for this class and should be included in every lab program */
/* that involves the auxillary board */
#include "ee3420_mega_aux_board.h"  //comment out this line if not using aux board

/* the ee3420_mega_adc_board.h header includes a lot of setup/shutdown functionality */
/* the header was written for this class and should be included in every lab program */
/* that involves the analog-to-digital board */
#include "ee3420_mega_adc_board.h"  //comment out this line if not using adc board

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"

//RTC struct
RTC_DS3231 rtc;

DateTime now, last_action;

//variables for RTC initialization 
const char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", 
           "Friday", "Saturday"};
const char monthNames[12][12] = {"January", "February", "March", "April", "May", "June", 
           "July", "August", "September", "October" , "November", "December"};

//global variables
int temp;
int current_year, current_month, current_day, current_hour, current_minute, current_second;
char charBuffer[80];

//Adafruit initialization
Adafruit_EEPROM_I2C i2ceeprom;
#define EEPROM_ADDR 0x57  // address range is 0x50 - 0x57

//matrix for terminating program
char key_matrix [3] = {0,0,0};

void setup() {
  // put your setup code here, to run once:

  //initialize the serial port that will communicate to the host computer over USB
  Serial.begin(115200, SERIAL_8N1);
  Serial.setTimeout(60000);

  //initialize the pin controlling the built-in LED on the Arduino MEGA 2560
  //usually, this is equivalent to pin 13
  pinMode(LED_BUILTIN, OUTPUT);  //built in LED on Arduino Mega is pin 13
  digitalWrite(LED_BUILTIN,0);   //turn built in LED off

#ifdef EE3420_MEGA_AUX_H
  ee3420_mega_aux_setup();
#endif

#ifdef EE3420_MEGA_ADC_H
  ee3420_mega_adc_setup();
#endif

  //note DS3231 requires Wire so Wire must be initialized first
  Wire.begin();
  Wire.setClock(100000);

#ifdef DEBUG
  Serial.println("Names test");

  //for loops to display date numbers needed
  for(temp=0;temp<7;temp++)
  {Serial.println(daysOfTheWeek[temp]);}
  
  for(temp=0;temp<12;temp++)
  {Serial.println(monthNames[temp]);}

  //pauses for 5 seconds
  delay(5000);
#endif //#ifdef DEBUG

  //note DS3231 requires Wire so Wire must be initialized first
  if (! rtc.begin()) {
    Serial.println(F("Couldn't find RTC"));
    Serial.flush();
    while (1) delay(10);
  }

  //check for IIC component 
  if (!i2ceeprom.begin(EEPROM_ADDR)) 
  {  
    Serial.print(F("IIC EEPROM not found at IIC address 0x"));
    Serial.println(EEPROM_ADDR, HEX);
    Serial.println(F("Suspending operation ..."));
    Serial.flush();
    while (1) delay(10);   
  } 

  now = rtc.now();
  last_action=now;
  
  sprintf(charBuffer, "EE 3420 EEPROM Write test");
  i2ceeprom.write(0x00, charBuffer, strlen(charBuffer)+1);

  //console dsiplay for user menu options
  Serial.println(F("\nDS3231 Clock Demonstration\n\n"));
  Serial.println(F("Press 1 to update the clock time."));
  Serial.println(F("Press 2 to forward the clock time by 1 hour."));
  Serial.println(F("Press 3 to set-back the clock time by 1 hour."));
  Serial.println(F("Press 4 to forward the clock time by 1 minute."));
  Serial.println(F("Press 5 to set-back the clock time by 1 minute."));
  Serial.println(F("Press 0 to update the clock seconds time to 0."));
  Serial.println(F("Press A to save the date and time into EEPROM."));
  Serial.println(F("Press B to read the date and time from EEPROM"));
  
  while(Serial.available()) {Serial.read();}  //clear any serial input from buffer 
  
}  //end of setup()

void loop() {
  // put your main code here, to run repeatedly:

  //clears lcd ouput
  lcd.clear(); 
  char input, state; 
  int h=0, mi=0, s=0; 

  //local variables
  h = now.hour();
  mi = now.minute();
  s = now.second();

  //reads input by user
  input = Serial.read(); 
  
  //asks user for input
  state = keypad.getKey();
  
  if(input)
  {
    //switch statments for conditions asked
    switch(input)
    {
      //displays current RTC values
      case '1':
        h = now.hour();
        mi = now.minute();
        s = now.second();
 
      input = Serial.read(); 
      break;

      //adds 1 hour to hour value
      case '2':
      h = h + 1; 
      input = Serial.read(); 

      break;

      //subtracts 1 hour to hour values
      case '3':
      h = h - 1; 
      input = Serial.read(); 

      break;

      //adds 1 minutes to minute value
      case '4':
      mi = mi + 1;
      input = Serial.read(); 

      break;

      //subtracts 1 minute to minute values
      case '5': 
      mi = mi - 1; 
      input = Serial.read(); 

      break;

      //sets seconds to 0
      case '0':
      s = 0;
      input = Serial.read(); 

      break;

      //saves current RTC values into EEPROM
      case 'A':
      sprintf(charBuffer,"%s, %s %d, %d ", daysOfTheWeek[now.dayOfTheWeek()], monthNames[now.month()-1],now.day(), now.year());
      Serial.println(F("Writing new string to offset 0x20")); 
      Serial.println(charBuffer); 
      i2ceeprom.write(0x20, charBuffer, strlen(charBuffer)+1);
  
      sprintf(charBuffer,"%d:%02d:%02d %c.M.", now.twelveHour(), now.minute(), now.second(), (now.isPM()?'P':'A'));
      Serial.println(F("Writing new string to offset 0x40")); 
      Serial.println(charBuffer);
      i2ceeprom.write(0x40, charBuffer, strlen(charBuffer)+1);

      break;

      //reads saved RTC values from EEPROM
      case 'B':
      Serial.println(F("String located at I2C EEPROM offset 0x00"));
      i2ceeprom.read(0x00, charBuffer, 32);
      Serial.println((String)charBuffer);

      Serial.println(F("String located at I2C EEPROM offset 0x20"));
      i2ceeprom.read(0x20, charBuffer, 32);
      Serial.println((String)charBuffer); 

      Serial.println(F("String located at I2C EEPROM offset 0x40"));
      i2ceeprom.read(0x40, charBuffer, 32);
      Serial.println((String)charBuffer); 

      break; 
     }
   }
  //prints out values to serial console
  Serial.print(now.year(), DEC);
  Serial.print(F("/"));
  Serial.print(now.month(), DEC);
  Serial.print(F("/"));
  Serial.print(now.day(), DEC);
  Serial.print(F("  "));
  Serial.print(h);
  Serial.print(F(":"));
  Serial.print(mi);
  Serial.print(F(":"));
  Serial.print(s);
  Serial.println();
  //displays values to LCD screen      
  lcd.print(now.year(), DEC);
  lcd.print(F("/"));
  lcd.print(now.month(), DEC);
  lcd.print(F("/"));
  lcd.print(now.day(), DEC);
  lcd.print(F("  "));
  lcd.setCursor(0,1);
  lcd.print(h);
  lcd.print(F(":"));
  lcd.print(mi);
  lcd.print(F(":"));
  lcd.print(s);

  // matrix code for asterisk input
  lcd.print(state);
  key_matrix[2]=key_matrix[1];
  key_matrix[1]=key_matrix[0];
  key_matrix[0]=state;
  // if loop for when symbol is pressed 3 times it will exit program
  if((key_matrix[0] == '*')&&(key_matrix[1] == '*')&&(key_matrix[2] == '*'))
  {
    Serial.println("Exiting program");
  }
  //pauses for 5 seconds
  delay(5000); 
}//end of loop
