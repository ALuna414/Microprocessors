/*
 * Lab9.ino
 * revision date: 28 November 2022
 * Written by: Aaron Luna
 * The purpose of this program is to demonstrate a system capable of acting as a weather 
 * station with data gathering capabilities. This is done with two Microprocessors. 
 * This code is designed for use on the Arduino Mega 2560.
 * The ee3420_mega_aux_board.h header will need to be in the same directory as this file.
 */

//commonly useful system libraries
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
// libraries needed for SD functions
#include <SPI.h>
#include "SdFat.h"

//SD functions
SdFat SD;
File myFile; 
#define SD_CS_PIN 53 

//global variable 
int sampleCount=0; 

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

void setup() {
  // put your setup code here, to run once:

  //initialize the serial port that will communicate to the host computer over USB
  Serial.begin(115200, SERIAL_8N1);
  Serial1.begin(115200, SERIAL_8N1);
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

//checks for reading of SD card
if (!SD.begin(SD_CS_PIN)) {
    Serial.println(F("SD initialization failed!  Suspending."));
    Serial.flush();
    while(1);
  }

}  //end of setup()

void loop() {
  // put your main code here, to run repeatedly:

  //iniaties variable to store values from other processor
  String dataLab; 
  dataLab = Serial1.readString();
  //prints to console
  Serial.println(dataLab); 

  //opens/creates weather file
  myFile = SD.open("weather.csv", FILE_WRITE); 

  //if statement to see if file is present
  if(!myFile)
  {
    Serial.println(F("Unable to open CSV file.  Suspending."));
    Serial.flush();
    while(1);
  }

  //if statement to write to SD card
  if (myFile) 
  {
    Serial.println("Writing to SD card...");
    myFile.print(dataLab); 
    //closes file
    myFile.close();
  }

  sampleCount++;
  
  //allows for only 10 readings to be done 
  if(sampleCount > 10)
  {
    Serial.println("Safe fto Remove SD card"); 
    while(1)
    {   
    }
  }
}  //end of loop()
