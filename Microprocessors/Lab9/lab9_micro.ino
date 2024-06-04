/*
 * lab9.ino
 * revision date: 18 November 2022
 * Written by: Seth Mills
 * 
 * This coded program of the lab is responsible for establishing the real time
 * clock and setting the interrupt to trigger every second through the 
 * establishment of a 1 Hz square wave. At each interrupt the program 
 * samples the analog devices (air sensor, light sensor, temp) and
 * triggers an LED depending on the air quality reading. The program 
 * then sends the data to a scond mircro procssor.
 * 
 * 
 * Pins:
 * A1: input for light sensor
 * A6: input for air quality sensor
 * 
 * 2: interrupt pin for sampling
 * 38: output for green LED
 * 39: output for yellow LED
 * 40: output for red LED
 */

//#define DEBUG

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

//added header files needed
#include <Wire.h>
#include <SPI.h>

// real time clock functions
#include "RTClib.h"

RTC_DS3231 rtc;

//Matrix to track exit sequence
char key_matrix[3] = {0,0,0};

//Matrices to track date
const char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char monthNames[12][12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October" , "November", "December"};


int current_year, current_month, current_day, current_hour, current_minute, current_second; // variables to track current date/time
int current_temperature; // temperature variable
char charBuffer[80]; // buffer used to store/send data

int clock_ready=false; // intrerupt trigger
int g_volts; //air analog variable
int t_volts; // temp analo variablee
int l_volts; // light analo variable


void setup() {
  // put your setup code here, to run once:

  //initialize the serial port that will communicate to the host computer and 2nd microprocessor
  Serial.begin(115200, SERIAL_8N1);
  Serial1.begin(115200, SERIAL_8N1);
  Serial.setTimeout(60000);

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

//starts DS3231
  Wire.begin();
  Wire.setClock(100000);

// loop to reset time if power lost
  if (rtc.lostPower()) 
  {
    prompt_and_set_RTC();
  }  //if (rtc.lostPower() || Serial.available())


  const int interruptPin = 2;
  
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(A1, INPUT);
  pinMode(A6, INPUT);
  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(40, OUTPUT);
  
  rtc.writeSqwPinMode(DS3231_SquareWave1Hz);
  attachInterrupt(digitalPinToInterrupt(interruptPin), clock_action, FALLING);
  
  while(Serial.available()) {Serial.read();}  //clear any serial input from buffer 
   
}  //end of setup()



void loop() {
  // put your main code here, to run repeatedly:

  if(clock_ready) //loop is entered when interrupt triggers
  {
    clock_ready=false;
    
    DateTime now = rtc.now();

    //prints time/date
    sprintf(charBuffer,"%s, %s %d, %d %d:%02d:%02d %c.M.", daysOfTheWeek[now.dayOfTheWeek()], 
    monthNames[now.month()-1],now.day(), now.year(), now.twelveHour(), now.minute(), 
    now.second(), (now.isPM()?'P':'A'));
    Serial.println(charBuffer);

    //reads and prints temperature from ds3231
    Serial.print(F("DS3231 Temperature: "));
    current_temperature=rtc.getTemperature();
    current_temperature = ((1.8*current_temperature)+32.0);
    Serial.print(current_temperature);
    Serial.println(F(" F"));
    
    //reads A1 for light input
    Serial.print(F("Resistance: "));
    int temp = analogRead(A1);
    int resistance = calculate_photocell_resistance(temp);
    Serial.println(resistance);
    
    //reads A6 for air quality input
    Serial.print(F("Gas Level (mV): "));
    int temp2 = analogRead(A6);
    g_volts = calculate_millivolts(temp2);
    Serial.println(g_volts);
    

    if(g_volts >= 0 && g_volts <= 500) //loop triggers if air quality is good
     {
       digitalWrite(39, LOW);
       digitalWrite(40, LOW);
       digitalWrite(38, HIGH); // green LED
     }

    else if(g_volts > 500 && g_volts <=  1000) // if air quality is moderate
     {
       digitalWrite(38, LOW);
       digitalWrite(40, LOW);
       digitalWrite(39, HIGH); // yellow LED
     }

    else if(g_volts > 1000 && g_volts <= 5000) //air quality is bad
     {
       digitalWrite(39, LOW);
       digitalWrite(38, LOW);
       digitalWrite(40, HIGH); //red LED
     }

    //prints all data into the buffer and sends it to 2nd microprocessor
    sprintf(charBuffer, "%d/%d/%d, %d:%d:%d, %d, %d, %d", now.month(), now.day(), 
       now.year(), now.hour(), now.minute(), now.second(), current_temperature, 
       resistance, g_volts);
    Serial1.println(charBuffer);
  }


  //function to exit program
  char input_key = keypad.getKey();
 
  key_matrix[2] = key_matrix[1];
  key_matrix[1] = key_matrix[0];
  key_matrix[0] = input_key;

  if ((key_matrix[0] == '*') && (key_matrix[1] == '*') && (key_matrix[2] == '*'))
  {
    Serial.println("Exiting program");
    Serial1.print("Exiting program");
  }
  
}  //end of loop()

/*
 * Function: clock_action
 * 
 * Used in combination with the interrupt pin to trigger the sampling 
 * by making the action true
 * 
 * No parameters
 * 
 * void: no returns
 */

 
void clock_action()
{
  clock_ready=true;
}


/*
 * Function: prompt_and_set_RTC
 * 
 * Used to update the time and date in the DS3231 if power is lost
 * 
 * No parameters
 * 
 * Void: No returns 
 */


void prompt_and_set_RTC()
{
      while(Serial.available()) {Serial.read();}  //clear any serial input from buffer 
        
    temp=-1;
    while(temp <2000 || temp > 2099)
    {
    Serial.println(F("Enter the current year as 2000-2099 as 4 digits: "));
    temp=Serial.parseInt();
    Serial.print(F("\nYou entered: "));
    Serial.println(temp);
    }
    Serial.print(F("Storing year as "));
    Serial.println(temp);
    current_year=temp;
     
    temp=-1;
    while(temp <1 || temp > 12)
    {
    Serial.println(F("Enter the current month as 1-12 with 1 as January and 12 as December: "));
    temp=Serial.parseInt();
    Serial.print(F("\nYou entered: "));
    Serial.println(temp);
    }
    Serial.print(F("Storing month as "));
    Serial.println(temp);
    current_month = temp;  
  
    temp=-1;
    while(temp <1 || temp > 31)
    {
    Serial.println(F("Enter the current day of the month as 1-31: "));
    temp=Serial.parseInt();
    Serial.print(F("\nYou entered: "));
    Serial.println(temp);
    }
    Serial.print(F("Storing day of the month as "));
    Serial.println(temp);
  
    current_day = temp ;  
  
    temp=-1;
    while(temp <0 || temp > 23)
    {
    Serial.println(F("Enter the current hour as 0-23: "));
    temp=Serial.parseInt();
    Serial.print(F("\nYou entered: "));
    Serial.println(temp);
    }
    Serial.print(F("Storing hour as "));
    Serial.println(temp);
  
    current_hour = temp ;  
  
    temp=-1;
    while(temp <0 || temp > 59)
    {
    Serial.println(F("Enter the current minute as 0-59: "));
    temp=Serial.parseInt();
    Serial.print(F("\nYou entered: "));
    Serial.println(temp);
    }
    Serial.print(F("Storing minute as "));
    Serial.println(temp);
  
    current_minute = temp ;  
  
    temp=-1;
    while(temp <0 || temp > 59)
    {
    Serial.println(F("Enter the current second as 0-59: "));
    temp=Serial.parseInt();
    Serial.print(F("\nYou entered: "));
    Serial.println(temp);
    }
    Serial.print(F("Storing second as "));
    Serial.println(temp);
  
    current_second = temp ;  //struct tm stores minute as 0-59
  
    while(Serial.available()) {Serial.read();}  //clear any serial input from buffer
  
#ifdef DEBUG
    Serial.println(F("\nTime entry summary:"));
    Serial.print(F("Year: "));
    Serial.println(current_year);
    Serial.print(F("Month: "));
    Serial.println(current_month);  
    Serial.print(F("Day: "));
    Serial.println(current_day);  
    Serial.print(F("Hour: "));
    Serial.println(current_hour);
    Serial.print(F("Minute: "));
    Serial.println(current_minute);  
    Serial.print(F("Second: "));
    Serial.println(current_second);  
#endif //#ifdef DEBUG
  
#ifdef DEBUG
    Serial.println(F("\nWriting time to DS3231")); 
#endif //#ifdef DEBUG
  
    rtc.adjust(DateTime(current_year, current_month, current_day, current_hour, current_minute, current_second));
}
