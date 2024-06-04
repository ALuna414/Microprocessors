int count,sum,average,remainder,temp;
char buffer[20];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200, SERIAL_8N1);  
  // set up serial port for communication 
  // at 115200 baud with 8 data bits,
  // no parity bit, and 1 stop bit
  // The serial port on the host must match this
  Serial.setTimeout(100000);
} //end of setup

void loop() {
  // put your main code here, to run repeatedly:
  count = 0;   
  sum = 0;
  
  while(1)
  {
    Serial.println("Enter a number (0-100) ");
    //buffer=Serial.readString();
   //temp=atoi(buffer);
   temp=Serial.parseInt();
   Serial.println(temp);
    if ((temp < 0)||(temp > 100))
    {break;}
    sum += temp;
    count++;
  }
    if (count != 0)
  {
    average = sum/count;
    remainder = sum%count;
  }
  else
  {
    average = 0;
    remainder = 0;
  }
  Serial.print("The average is ");
  Serial.print(average);
  if (remainder != 0)
  {
    Serial.print(" and ");
    Serial.print(remainder);
    Serial.print("/");
    Serial.print(count);
  }
  Serial.println(" ");
} //end of loop
