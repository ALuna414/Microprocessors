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
  
}  //end of setup()

void loop() {
  // put your main code here, to run repeatedly:

  int i;
  char keypad_input[3]={0,0,0};
  char keypad_current_key;
  int loop_active;

  Serial.println(" ");
  Serial.println(" ");
  Serial.println("Arduino Mega 2560 Auxillary Board Tests");
  
  Serial.println(" ");
  Serial.println(" ");
  Serial.println("Testing the LEDs.  The LEDS will cycle three times.");

  for(i=0; i<3; i++)
  {
    Serial.print("Turning on ... Built-in, ");
    digitalWrite(LED_BUILTIN,1);
    delay(1000); //1000 ms = 1s
    Serial.print("green, ");
    digitalWrite(LED_GREEN,1);
    delay(1000); //1000 ms = 1s  
    Serial.print("yellow, ");
    digitalWrite(LED_YELLOW,1);
    delay(1000); //1000 ms = 1s  
    Serial.print("red, ");
    digitalWrite(LED_RED,1);
    delay(1000); //1000 ms = 1s
    Serial.print("blue, ");
    digitalWrite(LED_BLUE,1);
    delay(1000); //1000 ms = 1s  
    Serial.println("white.");
    digitalWrite(LED_WHITE,1);
    delay(1000); //1000 ms = 1s   
    Serial.print("Turning off ... Built-in, ");
    digitalWrite(LED_BUILTIN,0);
    delay(1000); //1000 ms = 1s
    Serial.print("green, ");
    digitalWrite(LED_GREEN,0);
    delay(1000); //1000 ms = 1s  
    Serial.print("yellow, ");
    digitalWrite(LED_YELLOW,0);
    delay(1000); //1000 ms = 1s  
    Serial.print("red, ");
    digitalWrite(LED_RED,0);
    delay(1000); //1000 ms = 1s
    Serial.print("blue, ");
    digitalWrite(LED_BLUE,0);
    delay(1000); //1000 ms = 1s  
    Serial.println("white.");
    digitalWrite(LED_WHITE,0);
    delay(1000); //1000 ms = 1s 
  }

  Serial.println("Testing the buzzer.  It will sound three times.");
  for(i=0; i<3; i++)
  {
    Serial.println("Turning on buzzer.");
    digitalWrite(BUZZER,1);
    delay(1000); //1000 ms = 1s
    Serial.println("Turning off buzzer.");
    digitalWrite(BUZZER,0);
    delay(1000); //1000 ms = 1s    
  }  

  Serial.println("Testing the Character LCD.");
  Serial.println("The LCD should now blank and remain blank for 3 seconds.");
  lcd.clear();
  delay(3000);
  Serial.println("The top line of the LCD should say \"Hello\" on the left.");
  lcd.setCursor(0,0);  //column 0, row 0
  lcd.print("Hello");
  delay(1000);
  Serial.println("The bottom line of the LCD should show the hexadecimal digits.");
  lcd.setCursor(0,1);  //column 0, row 1
  lcd.print("0123456789ABCDEF");
  delay(3000); 
  Serial.println("The top line of the LCD should now also say \"World\" on the right.");
  lcd.setCursor(11,0);  //column 11, row 0
  lcd.print("World");
  delay(1000); 
  
  while(Serial.available()) {Serial.read();}  //clear the serial buffer
  Serial.println("Press any key in the Serial terminal to continue.");
  while(!Serial.available()) {}  //empty wait loop
  while(Serial.available()) {Serial.read();} //clear the serial buffer

  Serial.println("Testing the 4x4 keypad.");
  Serial.println("Press keys on the keypad and they will be echoed to the screen and LCD.");
  Serial.println("Press the \'*\' key three times in sequence to stop the keypad test.");
  Serial.println("Press any key in the Serial terminal to stop the test early.");
  lcd.clear();
  loop_active=1;
  while(loop_active!=0)
  {
    keypad_current_key=keypad.getKey();
    if (keypad_current_key != NO_KEY)
    {
      keypad_input[2]=keypad_input[1];
      keypad_input[1]=keypad_input[0];
      keypad_input[0]=keypad_current_key;
      Serial.println(keypad_current_key);
      lcd.setCursor(0,0);
      lcd.print(keypad_current_key);
      lcd.setCursor(0,1);
      lcd.print(keypad_input[0]);
      lcd.print(keypad_input[1]);      
      lcd.print(keypad_input[2]);
    }    
    if((keypad_input[0]=='*')&&(keypad_input[1]=='*')&&(keypad_input[2]=='*')) 
    {
      loop_active=0;
    }
    if(Serial.available())
    {
      loop_active=0;
      while(Serial.available()) {Serial.read();} //clear the serial buffer
    }
  }

  Serial.println("Keypad test finished.");
  lcd.setCursor(0,0);
  lcd.print("END KEYPAD TEST");
  delay(5000);

  Serial.println("Servo motor test.");
  Serial.println("Servo 0 --> 1000 us pulse width.");
  servo0.writeMicroseconds(1000);
  delay(1000);  
  Serial.println("Servo 0 --> 1500 us pulse width.");
  servo0.writeMicroseconds(1500);
  delay(1000);
  Serial.println("Servo 0 --> 2000 us pulse width.");
  servo0.writeMicroseconds(2000);
  delay(1000);  
  Serial.println("Servo 0 --> 1500 us pulse width.");
  servo0.writeMicroseconds(1500);
  delay(1000); 
  
  Serial.println("Servo 1 --> 1000 us pulse width.");
  servo1.writeMicroseconds(1000);
  delay(1000);  
  Serial.println("Servo 1 --> 1500 us pulse width.");
  servo1.writeMicroseconds(1500);
  delay(1000);
  Serial.println("Servo 1 --> 2000 us pulse width.");
  servo1.writeMicroseconds(2000);
  delay(1000);  
  Serial.println("Servo 1 --> 1500 us pulse width.");
  servo1.writeMicroseconds(1500);
  delay(1000);

  Serial.println("Servo 2 --> 1000 us pulse width.");
  servo2.writeMicroseconds(1000);
  delay(1000);  
  Serial.println("Servo 2 --> 1500 us pulse width.");
  servo2.writeMicroseconds(1500);
  delay(1000);
  Serial.println("Servo 2 --> 2000 us pulse width.");
  servo2.writeMicroseconds(2000);
  delay(1000);  
  Serial.println("Servo 2 --> 1500 us pulse width.");
  servo2.writeMicroseconds(1500);
  delay(1000);  

  Serial.println("Servo 3 --> 1000 us pulse width.");
  servo3.writeMicroseconds(1000);
  delay(1000);  
  Serial.println("Servo 3 --> 1500 us pulse width.");
  servo3.writeMicroseconds(1500);
  delay(1000);
  Serial.println("Servo 3 --> 2000 us pulse width.");
  servo3.writeMicroseconds(2000);
  delay(1000);  
  Serial.println("Servo 3 --> 1500 us pulse width.");
  servo3.writeMicroseconds(1500);
  delay(1000);

  Serial.println("DC Motor H-Bridge test.");
  Serial.println("DC Motor Clockwise 100\%.");
  digitalWrite(MOTOR_CW,1);
  digitalWrite(MOTOR_CCW,0);   
  analogWrite(MOTOR_PWM,255);  //255=100%
  delay(2000);
  Serial.println("DC Motor Clockwise 75\%.");
  digitalWrite(MOTOR_CW,1);
  digitalWrite(MOTOR_CCW,0);   
  analogWrite(MOTOR_PWM,192);
  delay(2000);  
  Serial.println("DC Motor Clockwise 50\%.");
  digitalWrite(MOTOR_CW,1);
  digitalWrite(MOTOR_CCW,0);   
  analogWrite(MOTOR_PWM,128);
  delay(2000);
  Serial.println("DC Motor stopped.");
  digitalWrite(MOTOR_CW,0);
  digitalWrite(MOTOR_CCW,0);   
  analogWrite(MOTOR_PWM,0);
  delay(2000);
  Serial.println("DC Motor Counter-clockwise 100\%.");
  digitalWrite(MOTOR_CW,0);
  digitalWrite(MOTOR_CCW,1);   
  analogWrite(MOTOR_PWM,255);  //255=100%
  delay(2000);
  Serial.println("DC Motor Counter-clockwise 75\%.");
  digitalWrite(MOTOR_CW,0);
  digitalWrite(MOTOR_CCW,1);   
  analogWrite(MOTOR_PWM,192);
  delay(2000);  
  Serial.println("DC Motor Counter-clockwise 50\%.");
  digitalWrite(MOTOR_CW,0);
  digitalWrite(MOTOR_CCW,1);   
  analogWrite(MOTOR_PWM,128);
  delay(2000);
  Serial.println("DC Motor stopped.");
  digitalWrite(MOTOR_CW,0);
  digitalWrite(MOTOR_CCW,0);   
  analogWrite(MOTOR_PWM,0);
  delay(2000);      

  while(Serial.available()) {Serial.read();}  //clear the serial buffer
  lcd.clear();
  Serial.println("All tests finished.");
  Serial.println("Press any key in the Serial terminal to repeat the tests.");
  while(!Serial.available()) {}  //empty wait loop
  while(Serial.available()) {Serial.read();} //clear the serial buffer
  
  
}  //end of loop()
