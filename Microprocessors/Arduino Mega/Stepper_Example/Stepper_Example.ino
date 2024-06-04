#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 


Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


#define STEPPER_PIN_1 8
#define STEPPER_PIN_2 9
#define STEPPER_PIN_3 10
#define STEPPER_PIN_4 11

int step_number = 0;

int step_number2 = 0;

int step_number3 = 0;

bool motorDirec = true;

int rate = 100;

char userInput = 'Z';

int maxSteps = 3;

int mode = 1;


void setup() {

  Serial.begin(9600);
  
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);

}

void loop() {

  if( mode == 1)
  {
    singleCoil();
    delay(rate);
  }
  else if( mode == 2)
  {
    doubleCoil();
    delay(rate);
  }
  else if(mode == 3)
  {
    halfStep();
    delay(rate);
  }

  char customKey = customKeypad.getKey();

  if(customKey)
  {
    userInput = customKey;
    menu(userInput);
  }
  
}
//**************************************
// Code block for single coil full step
//
//*************************************
void singleCoil()
{
   if(motorDirec == true)
   {
    switch(step_number)
    {
      case 0:
        digitalWrite(STEPPER_PIN_1, HIGH); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break; 
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);    
        break;     
    }
   }
   else
   {
    switch(step_number)
    {
      case 0:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break; 
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, HIGH); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);    
        break;     
    }    
   }

  step_number++; 

  if(step_number > 3)
  {
    step_number = 0;
  }
  
}


//************************************************
//
//Code for double coil full step 
//
//
//************************************************

void doubleCoil()
{
   if(motorDirec == true)
   {
    switch(step_number2)
    {
      case 0:
        digitalWrite(STEPPER_PIN_1, HIGH); 
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break; 
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, HIGH); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);    
        break;     
    }
   }
   else
   {
    switch(step_number2)
    {
      case 0:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break; 
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, HIGH); 
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, HIGH); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);    
        break;     
    }    
   }

  step_number2++; 

  if(step_number2 > 3)
  {
    step_number2 = 0;
  }
  
}


//*************************************************
//
//Code for half step 
//
//*************************************************
void halfStep()
{
   if(motorDirec == true)
   {
    switch(step_number3)
    {
      case 0:
        digitalWrite(STEPPER_PIN_1, HIGH); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break; 
      case 1:
        digitalWrite(STEPPER_PIN_1, HIGH); 
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);    
        break;  
      case 4:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break; 
      case 5:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
      case 6:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
      case 7:
        digitalWrite(STEPPER_PIN_1, HIGH); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);    
        break;
    }
   }
   else
   {
    switch(step_number3)
    {
      case 0:
        digitalWrite(STEPPER_PIN_1, HIGH); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);       
        break; 
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);    
        break;  
      case 4:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);  
        break; 
      case 5:
        digitalWrite(STEPPER_PIN_1, LOW); 
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);  
        break;
      case 6:
        digitalWrite(STEPPER_PIN_1, HIGH); 
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 7:
        digitalWrite(STEPPER_PIN_1, HIGH); 
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);    
        break;    
    }    
   }

  step_number3++; 

  if(step_number3 > 7)
  {
    step_number3 = 0;
  }
  
}


void menu(char userInput)
{

  switch(userInput)
  {
    case 'A':
      motorDirec = true;
      Serial.println("Changing to clock-wise direction");
      //loop();
      break;
    case 'B':
      motorDirec = false;
      Serial.println("Chaning to counter clock-wise direction");
      //loop();
     break;
    case 'C':
      if(rate < 1000)
      {
        rate++;
        Serial.println("Decreasing number of steps per second!!");
      }
      else 
      {
        Serial.println("1000 limit has been reached!!!!");
      }
     break;
    case 'D':
      if(rate > 1)
      {
        rate--; 
        Serial.println("Increasing number of steps per second!");
      }
      else 
      {
        Serial.println("1 limit has been reached!!!!"); 
      }
     break;
    case '1':
      Serial.println("Now entering mode 1");
      mode = 1;
      break;
    case '2':
      Serial.println("Now entering mode 2");
      mode = 2;
      break;
    case '3':
      Serial.println("Now entering mode 3");
      mode = 3;
      break;
  }  
}
