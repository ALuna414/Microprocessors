/*
 * shell.ino
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
#include <SPI.h>

int digit_pattern [16]= {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,
    0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
    
// implements the matrix for user
char key_matrix [3] = {0,0,0};
int joystick_x, x_scale;
int joystick_y, y_scale;

#define MAX7219_CS 53 
#define RCLK 12

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
  
  //initialize the serial port that will communicate to the host computer over USB
  Serial.begin(115200, SERIAL_8N1);

  //initialize pins
  //pinMode(50, HIGH);
  //pinMode(51, HIGH);
  //pinMode(52, HIGH);
  //pinMode(53, HIGH);
  //8x8 LED
  pinMode(MAX7219_CS,OUTPUT);
  //Potentiometer
  pinMode(A2, INPUT);
  //Y axis control
  pinMode(A4, INPUT);
  //X axis control
  pinMode(A5, INPUT);
  
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  pinMode(RCLK,OUTPUT);

  lcd.setCursor(0,0); 

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
  int x;  

  x = analogRead(A2); 
  x = x / 64;
  SPI.transfer(digit_pattern [x]);
  digitalWrite(RCLK,1);
  delay(100);
  digitalWrite(RCLK,0); 
  Serial.println(x);
  SPI.endTransaction();




  joystick_x = analogRead(A5);
  joystick_y = analogRead(A4);
  x_scale = joystick_x;
  y_scale = joystick_y;
  lcd.setCursor(0,0);
  lcd.print("X Coord: ");
  lcd.print(x_scale);
  lcd.setCursor(0,1);
  lcd.print("Y Coord: "); 
  lcd.print(y_scale);
  x_scale = (joystick_x / 128);
  y_scale = (joystick_y / 128);





  char input_k;
  input_k = keypad.getKey();
  Serial.println(input_k);
  key_matrix[2]=key_matrix[1];
  key_matrix[1]=key_matrix[0];
  key_matrix[0]=input_k;
  // if loop for when symbol is pressed 3 times it will exit program
  if((key_matrix[0] == '*')&&(key_matrix[1] == '*')&&(key_matrix[2] == '*'))
  {
    Serial.println("Exiting program");
    Serial1.println("Exiting program");
    SPI.endTransaction();
  }
  
  
}  //end of loop()
