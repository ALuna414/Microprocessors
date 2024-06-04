/*
 * example1.ino
 * revision date: 21 July 2022
 * Written by: William Stapleton
 * The purpose of this program is to demonstrate the associated header file functions
 * needed for the EE 3420 laboratory assignments in the Fall 2022 semester.
 * This code is designed for use on the Arduino Mega 2560.
 * The ee3420_mega_aux_board.h header will need to be in the same directory as this file.
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

// this is a local library and should be located in the same folder as the source code
#include "VT100.h"

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
  int i,j;
      
  while(Serial.available()) {Serial.read();}  //clear the serial buffer
  Serial.println("\n\nPress any key in the Serial terminal to continue.");
  while(!Serial.available()) {}  //empty wait loop
  while(Serial.available()) {Serial.read();} //clear the serial buffer

  Serial.print(vt100_erase_screen());

  for(i=0; i<20; i++)
  {
    Serial.print(vt100_move_cursor(i,i));
    Serial.print('*');
  }
  delay(5000);


  Serial.print(vt100_erase_screen());
    
  for(i=0; i<8; i++)
  {
    for(j=0; j<8; j++)
    {
      Serial.print(vt100_move_cursor(i+1,j+1));
      Serial.print(vt100_set_background(i));
      Serial.print(vt100_set_foreground(j));
      Serial.print('*');
      delay(1);
    }
  }
  Serial.print(vt100_text_default());
  Serial.print(vt100_move_cursor(10,1));
  Serial.println("Standard Color Set");
  
  delay(5000);  


  Serial.print(vt100_erase_screen());
  Serial.print(vt100_text_bright());
    
  for(i=0; i<8; i++)
  {
    for(j=0; j<8; j++)
    {
      Serial.print(vt100_move_cursor((i+1),(j+1)));
      Serial.print(vt100_set_background(i));
      Serial.print(vt100_set_foreground(j));
      Serial.print('*');
            delay(1);
    }
  }
  Serial.print(vt100_text_default());
  Serial.print(vt100_move_cursor(10,1));
  Serial.println("Bright Color Set");
  
  delay(5000); 

    Serial.print(vt100_erase_screen());
  Serial.print(vt100_text_underscore());
    
  for(i=0; i<8; i++)
  {
    for(j=0; j<8; j++)
    {
      Serial.print(vt100_move_cursor(i+1,j+1));
      Serial.print(vt100_set_background(i));
      Serial.print(vt100_set_foreground(j));
      Serial.print('*');
            delay(1);
    }
  }
  Serial.print(vt100_text_default());
  Serial.print(vt100_move_cursor(10,1));
  Serial.println("Underscore Color Set");
  
  delay(5000); 

    Serial.print(vt100_erase_screen());
  Serial.print(vt100_text_blink());
    
  for(i=0; i<8; i++)
  {
    for(j=0; j<8; j++)
    {
      Serial.print(vt100_move_cursor(i+1,j+1));
      Serial.print(vt100_set_background(i));
      Serial.print(vt100_set_foreground(j));
      Serial.print('*');
            delay(1);
    }
  }
  Serial.print(vt100_text_default());
  Serial.print(vt100_move_cursor(10,1));
  Serial.println("Blink Color Set");
  
  delay(5000); 

  Serial.print(vt100_erase_screen());
  Serial.print(vt100_text_hidden());
    
  for(i=0; i<8; i++)
  {
    for(j=0; j<8; j++)
    {
      Serial.print(vt100_move_cursor(i+1,j+1));
      Serial.print(vt100_set_background(i));
      Serial.print(vt100_set_foreground(j));
      Serial.print('*');
            delay(1);
      
    }
  }
  Serial.print(vt100_text_default());
  Serial.print(vt100_move_cursor(10,1));
  Serial.println("Hidden Color Set");
  
  delay(5000); 


  }  //end of loop()
