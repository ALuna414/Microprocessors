/*
 * Lab1.ino
 * revision date: 23 September 2022
 * Written by: Aaron Luna
 * The purpose of this program is to demonstrate a program in which will prompt 
 * the user to input a number between 1-65535. Program will test all possible 
 * integers as the other leg of triangle. If value is found, then hypotenuse
 * will be calculated and if also an integer, then program will output numbers
 * to the console. 
 */

//commonly useful system libraries
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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
  
}  //end of setup()

void loop() {
  // put your main code here, to run repeatedly:

  // initiate varibles needed to be displayed
  int side1, side2 = 0;
  double hypotenuse; 

  // ask user to input a number into the console
  Serial.println("Input a number between 1-65535. ");
  lcd.clear(); 

  while(Serial.available() == 0)
  {
  }

  // assigns side1 to user inputted number
  side1 = Serial.parseInt();

  // checks if number is in range then does calculations
  if(side1<0 || side1>65535)
  {
    Serial.println("Input a number between 1-65535. "); 
    side1 = Serial.read();
  }

  // checking numbers starting at 2, then hypotenuse is calculated with equation
  for(int i=2; i<=65535; i++)
  {
    hypotenuse = sqrt(pow(side1,2) + pow(i,2));

    if(fmod(hypotenuse,1.00) == 0.0)
    {
      side2 = i;
    }
  }

  // if a valid number was found then side1, side2, and hypotenuse are printed 
  if(side2 != 0)
  {
    Serial.println("Side 1 is \n");
    lcd.print("Side 1 is \n");
    Serial.println(side1);
    lcd.print(side1);
    Serial.println("Side 2 is \n");
    Serial.println(side2);
    Serial.println("Hypotenuse side is \n");
    Serial.println(hypotenuse);
  }

  // if loop above failed then console prints..
  else
  {
    Serial.print("No numbers match");
  }


  }  //end of loop()
