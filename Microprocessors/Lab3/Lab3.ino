

/*
 * lab4.ino
 * revision date: 7 October 2022
 * Written by: Aaron Luna
 * The purpose of this program is to implement a code to operate the stepper
 * motor. It will work in modes that are listed in the lab and chosen by
 * the user. It will continue asking for input until program key to 
 * terminate is activated. 
 * This code is designed for use on the Arduino Mega 2560.
 * The ee3420_mega_aux_board.h header will need to be in the same directory as this file.
 */

//commonly useful system libraries
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <Stepper.h>

//Global variables 
const int RMS = 500;
Stepper motor(RMS,8,9,10,11);
char key_matrix [3] = {0,0,0};
int mode = 1;
int count = 0; 
char direct = '+';
int steps = 100; 


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

//function call
  SingleCoil(); 

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
  int input_m; 
  char input_d;

   // ask user for an input
   input_d = keypad.getKey(); 

   if(input_d != NO_KEY)
   {
      //user selects 1 so loop occurs
      if(input_d == '1')
      {
        mode = 1; 

        Serial.println("Mode chosen is "); 
        Serial.println(mode);
        Serial.println("Direction is "); 
        Serial.println(direct); 
        Serial.println("Steps is "); 
        Serial.println(steps); 

        Serial.println("Single Coil Steps"); 
        count = 0; 
        SingleCoil(); 
      }

      // Mode 2 activated
      if(input_d == '2')
      {
        mode = 2; 

        Serial.println("Mode chosen is "); 
        Serial.println(mode);
        Serial.println("Direction is "); 
        Serial.println(direct); 
        Serial.println("Steps is "); 
        Serial.println(steps); 

        Serial.println("Double Coil Steps"); 
        count = 0; 
        DoubleCoil(); 
      }

      if(input_d == '3')
      {
        mode = 3; 

        Serial.println("Mode chosen is "); 
        Serial.println(mode);
        Serial.println("Direction is "); 
        Serial.println(direct); 
        Serial.println("Steps is "); 
        Serial.println(steps); 

        Serial.println("Half Coil Steps"); 
        count = 0; 
        HalfCoil(); 
      }

      if(input_d == 'A')
      {
        direct = '+'; 

        Serial.println("Mode chosen is "); 
        Serial.println(mode);
        Serial.println("Direction is "); 
        Serial.println(direct); 
        Serial.println("Steps is "); 
        Serial.println(steps);
      }

      if(input_d == 'B')
      {
        direct = '-'; 

        Serial.println("Mode chosen is "); 
        Serial.println(mode);
        Serial.println("Direction is "); 
        Serial.println(direct); 
        Serial.println("Steps is "); 
        Serial.println(steps); 
      }

      if(input_d == 'C')
      {
        if(steps > 1)
        {
          steps--;
          motor.step(steps); 
          Serial.println("Mode chosen is "); 
          Serial.println(mode);
          Serial.println("Direction is "); 
          Serial.println(direct); 
          Serial.println("Steps is "); 
          Serial.println(steps); 
        }
      }

      if(input_d == 'D')
      {
        if(steps < 1000)
        {
          steps++;
          motor.step(steps); 
          Serial.println("Mode chosen is "); 
          Serial.println(mode);
          Serial.println("Direction is "); 
          Serial.println(direct); 
          Serial.println("Steps is "); 
          Serial.println(steps); 
        }
      }

      // matrix for terminating program
      key_matrix[2]=key_matrix[1];
      key_matrix[1]=key_matrix[0];
      key_matrix[0]=input_d;
      if((key_matrix[0] == '*')&&(key_matrix[1] == '*')&&(key_matrix[2] == '*'))
      {
        Serial.println("Exiting program");
      }
    }

// initiate console inputs
 if(Serial.available())
    {
      while(input_m == '*' || input_d == '*')
      {
        char finish = Serial.read();
        char finish2 = keypad.getKey();

        if(finish == '#' || finish2 == '#')
        break;
      }

      input_m = Serial.read();

      if(input_m == '1')
      {
        mode = 1; 

        Serial.println("Mode chosen is "); 
        Serial.println(mode);
        Serial.println("Direction is "); 
        Serial.println(direct); 
        Serial.println("Steps is "); 
        Serial.println(steps); 

        Serial.println("Single Coil Steps"); 
        count = 0; 
        SingleCoil(); 
      }

      if(input_d == '2')
      {
        mode = 2; 

        Serial.println("Mode chosen is "); 
        Serial.println(mode);
        Serial.println("Direction is "); 
        Serial.println(direct); 
        Serial.println("Steps is "); 
        Serial.println(steps); 

        Serial.println("Double Coil Steps"); 
        count = 0; 
        DoubleCoil(); 
      }

      if(input_d == '3')
      {
        mode = 3; 

        Serial.println("Mode chosen is "); 
        Serial.println(mode);
        Serial.println("Direction is "); 
        Serial.println(direct); 
        Serial.println("Steps is "); 
        Serial.println(steps); 

        Serial.println("Half Coil Steps"); 
        count = 0; 
        HalfCoil(); 
      }
      
      if(input_d == 'A')
      {
        direct = '+'; 

        Serial.println("Mode chosen is "); 
        Serial.println(mode);
        Serial.println("Direction is "); 
        Serial.println(direct); 
        Serial.println("Steps is "); 
        Serial.println(steps);
      }

      if(input_d == 'B')
      {
        direct = '-'; 

        Serial.println("Mode chosen is "); 
        Serial.println(mode);
        Serial.println("Direction is "); 
        Serial.println(direct); 
        Serial.println("Steps is "); 
        Serial.println(steps); 
      }

      if(input_d == 'C')
      {
        if(steps > 1)
        {
          steps--;
          motor.step(steps); 
          Serial.println("Mode chosen is "); 
          Serial.println(mode);
          Serial.println("Direction is "); 
          Serial.println(direct); 
          Serial.println("Steps is "); 
          Serial.println(steps); 
        }
      }

      if(input_d == 'D')
      {
        if(steps < 1000)
        {
          steps++;
          motor.step(steps); 
          Serial.println("Mode chosen is "); 
          Serial.println(mode);
          Serial.println("Direction is "); 
          Serial.println(direct); 
          Serial.println("Steps is "); 
          Serial.println(steps); 
        }
      }
    }      
   } // end of loop


//function defintion for mode `1
void SingleCoil()
{
  for (count == 0; count <= 3; count++)
    {
      if(direct == '+')
      {
        switch(count) 
        {
          case 0:
            digitalWrite(8, HIGH); 
            digitalWrite(9, LOW);
            digitalWrite(10, LOW);
            digitalWrite(11, LOW);
            break;
          case 1:
            digitalWrite(8, LOW); 
            digitalWrite(9, HIGH);
            digitalWrite(10, LOW);
            digitalWrite(11, LOW);
            break;
          case 2:
            digitalWrite(8, LOW); 
            digitalWrite(9, LOW);
            digitalWrite(10, HIGH);
            digitalWrite(11, LOW);
            break;
        case 3:
          digitalWrite(8, LOW); 
          digitalWrite(9, LOW);
          digitalWrite(10, LOW);
          digitalWrite(11, HIGH);    
          break; 
        }
     }

     // direction affected loop for counter-clockwise
     if(direct == '-')
     {
      switch(count) 
      {
        case 0:
          digitalWrite(8, LOW); 
          digitalWrite(9, LOW);
          digitalWrite(10, LOW);
          digitalWrite(11, HIGH);
          break;
        case 1:
          digitalWrite(8, LOW); 
          digitalWrite(9, LOW);
          digitalWrite(10, HIGH);
          digitalWrite(11, LOW);
          break;
        case 2:
          digitalWrite(8, LOW); 
          digitalWrite(9, HIGH);
          digitalWrite(10, LOW);
          digitalWrite(11, LOW);
          break;
      case 3:
        digitalWrite(8, HIGH); 
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);    
        break; 
      }
     }

     if(count == 3)
     {
      count = -1;
     }

     delay(100);

     int finish = Serial.read();
     int finish2 = keypad.getKey();
     
     if(finish == '#'|| finish2 == '#')
      break;
  }
}

// void defintion for number 2 input
void DoubleCoil()
{
  for(count = 0; count <= 3;count++)
  {
    if(direct == '+')
    {
      switch(count) 
      {
        case 0:
          digitalWrite(8, HIGH); 
          digitalWrite(9, HIGH);
          digitalWrite(10, LOW);
          digitalWrite(11, LOW);
          break;
        case 1:
          digitalWrite(8, LOW); 
          digitalWrite(9, HIGH);
          digitalWrite(10, HIGH);
          digitalWrite(11, LOW);
          break;
        case 2:
          digitalWrite(8, LOW); 
          digitalWrite(9, LOW);
          digitalWrite(10, HIGH);
          digitalWrite(11, HIGH);
          break;
      case 3:
        digitalWrite(8, HIGH); 
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        digitalWrite(11, HIGH);    
        break; 
      }
    }

    if(direct == '-')
    {
      switch(count) 
      {
        case 0:
          digitalWrite(8, LOW); 
          digitalWrite(9, LOW);
          digitalWrite(10, HIGH);
          digitalWrite(11, HIGH);
          break;
        case 1:
          digitalWrite(8, LOW); 
          digitalWrite(9, HIGH);
          digitalWrite(10, HIGH);
          digitalWrite(11, LOW);
          break;
        case 2:
          digitalWrite(8, HIGH); 
          digitalWrite(9, HIGH);
          digitalWrite(10, LOW);
          digitalWrite(11, LOW);
          break;
      case 3:
        digitalWrite(8, HIGH); 
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        digitalWrite(11, HIGH);    
        break; 
      }
    }

    if(count == 3)
      count = -1;
    delay(100);

    int finish = Serial.read();
    int finish2 = keypad.getKey();
     
     if(finish == '#'|| finish2 == '#')
      break;
  }
}

void HalfCoil()
{
  for(count = 0; count <= 7;count++)
  {
    if(direct == '+')
    {
      switch(count)
    {
      case 0:
        digitalWrite(8, HIGH); 
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        break; 
      case 1:
        digitalWrite(8, HIGH); 
        digitalWrite(9, HIGH);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        break;
      case 2:
        digitalWrite(8, LOW); 
        digitalWrite(9, HIGH);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        break;
      case 3:
        digitalWrite(8, LOW); 
        digitalWrite(9, HIGH);
        digitalWrite(10, HIGH);
        digitalWrite(11, LOW);    
        break;  
      case 4:
        digitalWrite(8, LOW); 
        digitalWrite(9, LOW);
        digitalWrite(10, HIGH);
        digitalWrite(11, LOW);
        break; 
      case 5:
        digitalWrite(8, LOW); 
        digitalWrite(9, LOW);
        digitalWrite(10, HIGH);
        digitalWrite(11, HIGH);
        break;
      case 6:
        digitalWrite(8, LOW); 
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        digitalWrite(11, HIGH);
        break;
      case 7:
        digitalWrite(8, HIGH); 
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        digitalWrite(11, HIGH);    
        break;
    }
    }

    if(direct == '-')
    {
      switch(count)
    {
      case 0:
        digitalWrite(8, LOW); 
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        digitalWrite(11, HIGH);
        break; 
      case 1:
        digitalWrite(8, LOW); 
        digitalWrite(9, LOW);
        digitalWrite(10, HIGH);
        digitalWrite(11, HIGH);
        break;
      case 2:
        digitalWrite(8, LOW); 
        digitalWrite(9, LOW);
        digitalWrite(10, HIGH);
        digitalWrite(11, LOW);
        break;
      case 3:
        digitalWrite(8, LOW); 
        digitalWrite(9, HIGH);
        digitalWrite(10, HIGH);
        digitalWrite(11, LOW);    
        break;  
      case 4:
        digitalWrite(8, LOW); 
        digitalWrite(9, HIGH);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        break; 
      case 5:
        digitalWrite(8, HIGH); 
        digitalWrite(9, HIGH);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        break;
      case 6:
        digitalWrite(8, HIGH); 
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        break;
      case 7:
        digitalWrite(8, HIGH); 
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        digitalWrite(11, HIGH);    
        break;
     }
    }

    if(count == 7)
      count = 1;
    delay(100);

    int finish = Serial.read();
    int finish2 = keypad.getKey();
     
    if(finish == '#'|| finish2 == '#')
      break;
  }  
} // end of all definitions 
