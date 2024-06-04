/*
 * Lab7.ino
 * revision date: 11 September 2022
 * Written by: Aaron Luna
 * The purpose of this program is to demonstrate a system capable of using SPI to 
 * interact with peripherals without using an excess of GPIO pins. This would be done 
 * with a 7-segement display and an 8x8 LED array. 
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

// array for 8x8 LED
int digit_pattern [16]= {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,
    0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
    
// implements the matrix for user
char key_matrix [3] = {0,0,0};
int joystick_x, x_scale;
int joystick_y, y_scale;

//53 is default CS for Mega 2560
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
  //8x8 LED
  pinMode(MAX7219_CS,OUTPUT);
  //Potentiometer
  pinMode(A2, INPUT);
  //Y axis control
  pinMode(A4, INPUT);
  //X axis control
  pinMode(A5, INPUT);

  SPI.begin();
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  pinMode(RCLK,OUTPUT);
  lcd.setCursor(0,0); 
  
  // compares to LED8x8_init function from example code
  digitalWrite(MAX7219_CS,0);
  SPI.transfer(9);
  SPI.transfer(0); //for 8x8 LED, no decode on MAX7219
  digitalWrite(MAX7219_CS,1);
  digitalWrite(MAX7219_CS,0);
  SPI.transfer(0xA);
  SPI.transfer(0xF); //select maximum brightness
  digitalWrite(MAX7219_CS,1);
  digitalWrite(MAX7219_CS,0);
  SPI.transfer(0xB);
  SPI.transfer(7); //select all digits/columns to be displayed
  digitalWrite(MAX7219_CS,1);
  digitalWrite(MAX7219_CS,0);
  SPI.transfer(0xC);
  SPI.transfer(1); //enable output
  digitalWrite(MAX7219_CS,1);
  digitalWrite(MAX7219_CS,0);
  SPI.transfer(0xF);
  SPI.transfer(0); //disable test mode
  digitalWrite(MAX7219_CS,1);
  
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

  // stores analog value from potentiometer
  x = analogRead(A2); 
  x = x / 64; // divides by 64 to correlate to hex value
  SPI.transfer(digit_pattern [x]);
  digitalWrite(RCLK,1);
  delay(100);
  digitalWrite(RCLK,0); 
  Serial.println(x); // prints value to console
  SPI.endTransaction();

  // stores analog values of joysticks
  joystick_x = analogRead(A5);
  joystick_y = analogRead(A4);
  x_scale = joystick_x;
  y_scale = joystick_y;
  lcd.clear(); // clears LCD screen
  lcd.setCursor(0,0);
  lcd.print("X Coord: ");
  lcd.print(x_scale);
  lcd.setCursor(0,1); // tabs to next line on LCD
  lcd.print("Y Coord: "); 
  lcd.print(y_scale);

  // for loop to clear all LEDs on 8x8 
  for(int i = 1; i < 9; i++)
  {
    digitalWrite(MAX7219_CS,0);
    SPI.transfer(i);
    SPI.transfer(0);
    digitalWrite(MAX7219_CS,1);
  }

  // divides joysticks value by 128 to show column and row position
  x_scale = (joystick_x / 128);
  y_scale = (joystick_y / 128);
  digitalWrite(MAX7219_CS,0);
  SPI.transfer(x_scale + 1);
  SPI.transfer(1 << y_scale);
  digitalWrite(MAX7219_CS,1);

  // code to initiate termination of program
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
