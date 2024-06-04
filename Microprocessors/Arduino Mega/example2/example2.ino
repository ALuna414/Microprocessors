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

  int i;
  char keypad_input[3]={0,0,0};
  char keypad_current_key;
  int loop_active;

  int raw_sample;
  int raw_x, raw_y;

  Serial.println(" ");
  Serial.println(" ");
  Serial.println("Arduino Mega 2560 Analog-to-Digital Board Tests");
  
  Serial.println(" ");
  Serial.println(" ");
  Serial.println("Reading the Temperature probe.");
  Serial.print("Reading from analog channel ");
  Serial.println((int)(ADC_TEMPERATURE-A0));
  
  raw_sample=analogRead(ADC_TEMPERATURE);
  Serial.print("Raw sample value: ");
  Serial.println(raw_sample);
  
  Serial.print("Volts = ");
  Serial.print(calculate_volts(raw_sample));
  Serial.print(", Millivolts = ");
  Serial.println(calculate_millivolts(raw_sample));  
  
  Serial.print("If an LM34, deg F = ");
  Serial.print(calculate_LM34_fahrenheit(raw_sample));
  Serial.print(", deg C = ");
  Serial.println(calculate_LM34_celsius(raw_sample));
  
  Serial.print("If an LM35, deg F = ");
  Serial.print(calculate_LM35_fahrenheit(raw_sample));
  Serial.print(", deg C = ");
  Serial.println(calculate_LM35_celsius(raw_sample));
  
  Serial.print("If an MCP9701, deg F = ");
  Serial.print(calculate_MCP9701_fahrenheit(raw_sample));
  Serial.print(", deg C = ");
  Serial.println(calculate_MCP9701_celsius(raw_sample));

  delay(3000);
  
  Serial.println(" ");
  Serial.println("Reading the Photocell.");
  Serial.print("Reading from analog channel ");
  Serial.println((int)(PHOTOCELL-A0));
  
  raw_sample=analogRead(PHOTOCELL);
  Serial.print("Raw sample value: ");
  Serial.println(raw_sample);
  
  Serial.print("Volts = ");
  Serial.print(calculate_volts(raw_sample));
  Serial.print(", Millivolts = ");
  Serial.println(calculate_millivolts(raw_sample));  

  Serial.print("Photocell Resistance (ohms) = ");
  Serial.println(calculate_photocell_resistance(raw_sample));

  delay(3000);
  
  Serial.println(" ");
  Serial.println("Reading the Potentiometer.");
  Serial.print("Reading from analog channel ");
  Serial.println((int)(POTENTIOMETER-A0));
  
  raw_sample=analogRead(POTENTIOMETER);
  Serial.print("Raw sample value: ");
  Serial.println(raw_sample);
  
  Serial.print("Volts = ");
  Serial.print(calculate_volts(raw_sample));
  Serial.print(", Millivolts = ");
  Serial.println(calculate_millivolts(raw_sample));  

  delay(3000);
  
  Serial.println(" ");
  Serial.println("Reading the Joystick.");
  Serial.print("Reading from analog channel ");
  Serial.println((int)(JOYSTICK_BUTTON-A0));
  raw_sample=analogRead(JOYSTICK_BUTTON);
  Serial.print("Reading from analog channel ");
  Serial.println((int)(JOYSTICK_X-A0));
  raw_x=analogRead(JOYSTICK_X);
  Serial.print("Reading from analog channel ");
  Serial.println((int)(JOYSTICK_Y-A0));
  raw_y=analogRead(JOYSTICK_Y);
  
  Serial.print("Button sample value: ");
  Serial.println(raw_sample);

  Serial.print("X Axis sample value: ");
  Serial.println(raw_x);

  Serial.print("Y Axis sample value: ");
  Serial.println(raw_y);
  
  delay(3000);
  
  Serial.println(" ");
  Serial.println("Reading the Gas Sensor.");
  Serial.print("Reading from analog channel ");
  Serial.println((int)(GAS_SENSOR-A0));
  
  raw_sample=analogRead(GAS_SENSOR);
  Serial.print("Raw sample value: ");
  Serial.println(raw_sample);
  
  Serial.print("Volts = ");
  Serial.print(calculate_volts(raw_sample));
  Serial.print(", Millivolts = ");
  Serial.println(calculate_millivolts(raw_sample));

  delay(3000);
  
  Serial.println(" ");
  Serial.println("Reading the rotary encoder.");
  Serial.print("Reading from analog channel ");
  Serial.println((int)(ENCODER_A-A0));
  raw_x=analogRead(ENCODER_A);
  Serial.print("Reading from analog channel ");
  Serial.println((int)(ENCODER_B-A0));
  raw_y=analogRead(ENCODER_B);
  
  Serial.print("Encoder A sample value: ");
  Serial.println(raw_x);

  Serial.print("Encoder B sample value: ");
  Serial.println(raw_y);   

  delay(3000);
  
  Serial.println(" ");
  Serial.println("Reading the ADC Pushbutton.");
  Serial.print("Reading from analog channel ");
  Serial.println((int)(ADC_BUTTON-A0));
  
  raw_sample=analogRead(ADC_BUTTON);
  Serial.print("Raw sample value: ");
  Serial.println(raw_sample);
  
  Serial.print("Volts = ");
  Serial.print(calculate_volts(raw_sample));
  Serial.print(", Millivolts = ");
  Serial.println(calculate_millivolts(raw_sample));    

  Serial.println(" ");
  Serial.println("End of Test Cycle"); 

  delay(5000);

  }  //end of loop()
