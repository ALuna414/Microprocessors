/*
 * Lab6.ino
 * revision date: 04 November 2022
 * Written by: Aaron Luna
 * The purpose of this program is to demonstrate the use and implementation of Analog-
 * To-Digital (ADC) valuess. Theses values once converted were used with components
 * to light up certain LEDs to indicate a certain task was being done. Limits on 
 * those values would also be printed to the serial monitor and LCD. 
 * The ee3420_mega_aux_board.h header will need to be in the same directory as this file.
 */

//commonly useful system libraries
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <Servo.h>

// implements the matrix for user
char key_matrix [3] = {0,0,0};

// global variables for added components on ADC board
int joystick_x, x_scale;
int joystick_y, y_scale;
float v_mag, v_angle, temp; 
int input_temp, dark, volts; 
int dutyCycle;

// adds DC motor use
Servo MicroS; 

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
  MicroS.attach(45);
  //Green LED
  pinMode(38, OUTPUT);
  //Yellow LED
  pinMode(39, OUTPUT); 
  //Red LED
  pinMode(40, OUTPUT);
  //White LED
  pinMode(42, OUTPUT);
  //Temperature
  pinMode(A0, INPUT); 
  //Photoresistor
  pinMode(A1, INPUT);
  //Potentiometer
  pinMode(A2, INPUT);
  //Y axis control
  pinMode(A4, INPUT);
  //X axis control
  pinMode(A5, INPUT);

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
  char input_k;
  // gets user input at start of loop
  input_k = keypad.getKey();

  // reads analog value of CdS photocell
  dark = analogRead(A1);
  // reads analog value of joystick movements
  joystick_x = analogRead(A5) - 512;
  joystick_y = analogRead(A4) - 512;
  // reads analog value of potentiometer
  volts = analogRead(A2);
  // reads analog value of LM34
  input_temp = analogRead(A0);

  x_scale = (joystick_x / 512);
  y_scale = (joystick_y / 512);

  // converts values into desired vector quantities
  v_mag = sqrt(pow(x_scale, 2) + pow(y_scale, 2));
  v_angle = atan(y_scale / x_scale);  

  // LCD code to be display on there
  lcd.setCursor(0,0);
  lcd.print("Mag = "); 
  lcd.print(v_mag);
  lcd.setCursor(0,1);
  lcd.print("Phase = "); 
  lcd.print(v_angle);

  // turns on yellow LED 
  if(v_mag >= 0.25)
    digitalWrite(39, HIGH);
  // turns off tellow LED if condition met
  if(v_mag < .25)
    digitalWrite(39, LOW);

  // function call to adc file
  temp = calculate_MCP9701_celsius(input_temp);
  Serial.print(temp); 
  Serial.println(" degrees celsius");  

  // turns on red LED if temperature exceeded
  if(temp >= 25)
  {
    digitalWrite(40, HIGH);
    Serial.println("HOT");
    digitalWrite(5, HIGH);
  }
  // turns off LED if cool enough
  if(temp < 25)
  {
    digitalWrite(40, LOW);
    digitalWrite(5, LOW);
  }

  // assgins dark value to function call
  dark = calculate_photocell_resistance(dark);

  // white LED turns on if dark enough levels read
  if(dark > 10000)
    digitalWrite(42, HIGH);
  // keeps LED off if not dark
  if(dark <= 10000)
    digitalWrite(42, LOW); 
     
  Serial.println(dark);

  volts = calculate_volts(volts);
  // prints to serial monitor volts reading
  Serial.print("Volts = "); 
  Serial.println(volts);

  // meant for DC motor
  dutyCycle = volts*200+1000;
  MicroS.writeMicroseconds(dutyCycle);

  // turns on green LED when all conditions not met
  if(v_mag < .25 && temp < 25 && dark <= 10000)
    digitalWrite(38, HIGH); 
  // turns off green LED
  if(v_mag >= 0.25 || temp >= 25 || dark > 10000)
    digitalWrite(38, LOW); 

  // code for inputing asterisk three times and storing it
  Serial.println(input_k);
  key_matrix[2]=key_matrix[1];
  key_matrix[1]=key_matrix[0];
  key_matrix[0]=input_k;

  // if loop for when symbol is pressed 3 times it will exit program
  if((key_matrix[0] == '*')&&(key_matrix[1] == '*')&&(key_matrix[2] == '*'))
  {
    Serial.println("Exiting program");
    Serial1.println("Exiting program");
  }

  // delay a second between analog readings
  delay(1000);
  
}  //end of loop()
