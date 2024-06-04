/*
 * Lab2.ino
 * revision date: 30 September 2022
 * Written by: Aaron Luna
 * The purpose of this program is to extend the user input and output options using a 
 * keypad, LCD, and serial console. Doing so will allow corresponding character to be 
 * displayed both on the local “Serial” console and the character LCD for both users. 
 * The ee3420_mega_aux_board.h header will need to be in the same directory as this file.
 */

// implements the matrix for user
char key_matrix [3] = {0,0,0};

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

  // allows communication on other users console
  Serial1.begin(115200, SERIAL_8N1); 

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

  lcd.setCursor(0,0);

  // data types needed for input 
  char input_k;
  char input_s;
  char input_UART;

  // takes in cahracter from user
  input_k = keypad.getKey();
 
  // once a charater is inputted then code will run and print as needed
  if(input_k!= NO_KEY)
  {
   
    Serial.write(input_k);
   
    Serial1.write(input_k);
   
    lcd.setCursor(0,1);
 
    lcd.print(input_k);
    key_matrix[2]=key_matrix[1];
    key_matrix[1]=key_matrix[0];
    key_matrix[0]=input_k;

    // if loop for when symbol is pressed 3 times it will exit program
    if((key_matrix[0] == '*')&&(key_matrix[1] == '*')&&(key_matrix[2] == '*'))
    {
      Serial.println("Exiting program");
      Serial1.println("Exiting program");
    
    }
 
  }

  // allows continuation of characters inputted as long as console is taking input
  if(Serial.available())
  {
    input_s = Serial.read();
 
    Serial.write(input_s);
   
    Serial1.write(input_s);
   
    lcd.setCursor(0,1);
 
    lcd.print(input_s);
   
  }
 
  if(Serial1.available())
  {
    input_UART = Serial1.read();
 
    Serial.write(input_UART);
   
    lcd.setCursor(0,1);
 
    lcd.print(input_UART);
  }
 
 }  //end of loop()
