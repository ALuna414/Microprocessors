/*
 * Lab5.ino
 * revision date: 21 October 2022
 * Written by: Aaron Luna
 * The purpose of this program is to demonstrate the use of Pulse-Width Modulation 
 * functions to power a DC motor and a Servo motor. User inputted values will 
 * decide how the motors should operate. The program can be ended at any time 
 * with the desired asterisk input. 
 * This code is designed for use on the Arduino Mega 2560.
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
#include <Servo.h>

// variable to initiate speed at beginning 
int speed = 1000;

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
  // put your setup code here, to run once:;

  // initializes the Servo motor at desired pin
  servo0.attach(46,1000,2000);
  
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
  //analogWrite(pin,value)
  //attach() – select the pin to control the named servo
  //write() – select the angle for the servo (0 to 180)
  //writeMicroseconds() – select the pulse width in microseconds (1000 to 2000)
  //read() – read the current angle for the servo (0 to 180)
  //attached() – determine if the servo is attached to a pin
  //detach() – disconnect the pin from the servo
 
  char state;
  // selects the angle for the servo (0 to 180) 
  servo0.write(180);
  // selects the pulse width in microseconds (1000 to 2000)
  servo0.writeMicroseconds(speed);

  // asks user for input
  state = keypad.getKey();

 if(state != NO_KEY)
 {
  // switch cases to task actions from instructions 
  switch (state)
  {
    case '1': 
        if (speed >= 1000 && speed <= 2000)
          speed++; 
          
        servo0.writeMicroseconds(speed);
        // prints to serial screen
        Serial.println("PW is "); 
        Serial.println(speed); 

        if (speed < 1000 || speed > 2000)
        speed = 1000;
     state = keypad.getKey();
     break;

    case '2':
        // executes if statement if within this range
        if (speed >= 1000 && speed <= 2000)
          speed = speed + 10; 
          
        servo0.writeMicroseconds(speed);
        Serial.println("PW is "); 
        Serial.println(speed); 

        if (speed < 1000 || speed > 2000)
          speed = 1000;
     state = keypad.getKey(); 
     // exits case
     break;

    case '3': 
        if (speed >= 1000 && speed <= 2000)
          speed = speed + 100; // adds 100 to speed 
          
        servo0.writeMicroseconds(speed);
        Serial.println("PW is "); 
        Serial.println(speed); 

        if (speed < 1000 || speed > 2000)
          speed = 1000;
    state = keypad.getKey();
    break;

    case '4':
        if (speed >= 1000 && speed <= 2000)
          speed = speed - 1; 
          
        servo0.writeMicroseconds(speed);
        Serial.println("PW is "); 
        Serial.println(speed); // speed number is printed

        if (speed < 1000 || speed > 2000)
          speed = 1000;
    state = keypad.getKey(); 
    break;

    case '5':
        if (speed >= 1000 && speed <= 2000)
          speed = speed - 10; 
          
        servo0.writeMicroseconds(speed);
        Serial.println("PW is "); 
        Serial.println(speed); 
 
        if (speed < 1000 || speed > 2000)
          speed = 1000;
    // gets user input again for next action      
    state = keypad.getKey();
    break;

    case '6':
        if (speed >= 1000 && speed <= 2000)
          speed = speed - 100; 

        // changes pulse-width  
        servo0.writeMicroseconds(speed);
        Serial.println("PW is "); 
        Serial.println(speed); 

        if (speed < 1000 || speed > 2000)
          speed = 1000;
    state = keypad.getKey(); 
    break; // exit case

    case '7':
        if (speed >= 1000 && speed <= 2000)
          speed = 1000; 
          
        servo0.writeMicroseconds(speed);
        Serial.println("PW is "); 
        Serial.println(speed); 

        if (speed < 1000 || speed > 2000)
          speed = 1000;
    state = keypad.getKey(); 
    break;

    case '8':
        if (speed >= 1000 && speed <= 2000)
          speed = 1500; 
          
        servo0.writeMicroseconds(speed);
        Serial.println("PW is "); 
        Serial.println(speed); 

        // if speed is out of range then it resets it
        if (speed < 1000 || speed > 2000)
          speed = 1000;
    state = keypad.getKey(); 
    break;

    case '9':
        if (speed >= 1000 && speed <= 2000)
          speed = 2000; // max speed set
          
        servo0.writeMicroseconds(speed);
        Serial.println("PW is "); 
        Serial.println(speed); 

        if (speed < 1000 || speed > 2000)
          speed = 1000;
    state = keypad.getKey();
    break;

   }

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
  } 
 }  //end of loop()
