/*
 * Lab4.ino
 * revision date: 14 October 2022
 * Written by: Aaron Luna
 * The purpose of this program is to demonstrate the implementation of a traffic light
 * and act like one as well. One microprocessor will be North/South and other will be 
 * East/South and both have different LED light options. Will terminate whenever * is 
 * pushed three times. A group lab with both codes being different depending on 
 * instructions and how users want it to operate. 
 * This code is designed for use on the Arduino Mega 2560.
 * The ee3420_mega_aux_board.h header will need to be in the same directory as this file.
 */

// implements the matrix for user
char key_matrix [3] = {0,0,0};
// implments global varibale for input changes
int state; 

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

  // initialize buzzer on auxiliary board
  pinMode(37, OUTPUT);

  // initialize the serial port that will communicate to the host computer over USB
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

  // declare input variable to be stored
  char input_k; 

  // takes input from serial console
  state = Serial1.read(); 

  // reads input and triggers switch to start cycling through cases
  switch (state)
  {
    // first intructions from report manual
    case 1: 
      digitalWrite(11,HIGH);
      digitalWrite(10,LOW);
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
      digitalWrite(5,HIGH);
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);
      digitalWrite(2,LOW);
      delay(3000);

    if (keypad.getKey() != NO_KEY)
    {
      // wrties to other microprocessor
      Serial1.write(1); 
    }

    state = Serial1.read(); 
    break;

    case 2:
      digitalWrite(11,HIGH);
      digitalWrite(10,LOW);
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
      digitalWrite(5,HIGH);
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);
      digitalWrite(2,LOW);
      delay(2000);
    
    if(keypad.getKey() != NO_KEY)
    {
      Serial1.write(1); 
      state = Serial1.read(); 
      break;
    }
    else
    {
      // stops for 5 seconds
      delay(5000);
      state = Serial1.read(); 
      break;
    }

    case 3: 
      digitalWrite(11,HIGH);
      digitalWrite(10,LOW);
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
      digitalWrite(5,HIGH);
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);
      digitalWrite(2,LOW);
      delay(2000);
   
    if(keypad.getKey() != NO_KEY)
    {
      Serial1.write(1); 
      state = Serial1.read(); 
      break;
    }

    state = Serial1.read(); 

    // breaks out of case option
    break;

    case 4:
      digitalWrite(11,HIGH);
      digitalWrite(10,LOW);
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
      digitalWrite(5,HIGH);
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);
      digitalWrite(2,LOW);
      delay(3000);
    
    if(keypad.getKey() != NO_KEY)
    { 
      Serial1.write(1); 
      state = Serial1.read(); 
      break;
    }

    state = Serial1.read(); 
    break;

    case 5: 
      digitalWrite(11,LOW);
      digitalWrite(10,LOW);
      digitalWrite(9,HIGH);
      digitalWrite(8,LOW);
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(3,HIGH);
      digitalWrite(2,LOW);
      delay(2000);

    if(keypad.getKey() != NO_KEY)
    {
      Serial1.write(1); 
      state = Serial1.read(); 
      break;
    }
    // reads input from other microprocessor
    else
    {
      delay(5000);
      state = Serial1.read(); 
      break;
    }
    
    case 6:
      digitalWrite(11,LOW);
      digitalWrite(10,HIGH);
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
      digitalWrite(5,LOW);
      digitalWrite(4,HIGH);
      digitalWrite(3,LOW);
      digitalWrite(2,LOW);
      delay(2000);
    
    if(keypad.getKey() != NO_KEY)
    {
      Serial1.write(1);
      state = Serial1.read(); 
      break;
    }

    state = Serial1.read(); 
    break;

    case 7: 
      digitalWrite(11,HIGH);
      digitalWrite(10,LOW);
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
      digitalWrite(5,HIGH);
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);
      digitalWrite(2,LOW);
      delay(2000);
      state = Serial1.read(); 

    break;

    case 8:
      digitalWrite(11,LOW);
      digitalWrite(10,HIGH);
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
      digitalWrite(5,LOW);
      digitalWrite(4,HIGH);
      digitalWrite(3,LOW);
      digitalWrite(2,LOW);
      delay(2000);
      state = Serial1.read(); 
    
    break;

    case 9: 
      digitalWrite(11,HIGH);
      digitalWrite(10,LOW);
      digitalWrite(9,LOW);
      digitalWrite(8,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);
      digitalWrite(2,HIGH);

    // for loop to activate buzzer and how it sounds
    for(int i = 0; i <= 5; i++)
    {
      tone(37, 1000);
      delay(1000);
      noTone(37);
      delay(1000);
    }

    state = Serial1.read(); 
    
    break;  
  } // end of switch loop

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

  }  //end of loop()
