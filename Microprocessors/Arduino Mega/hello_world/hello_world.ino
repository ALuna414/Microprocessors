void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200, SERIAL_8N1);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Hello, World!\n");
  delay(5000);  //5000 ms = 5s
}
