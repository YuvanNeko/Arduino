void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  Serial.println("Please enter the time in munutes :");
}

void loop() {
  while (Serial.available() == 0){
  }
  int a = 60*Serial.parseInt();
  while (a > 0){
    Serial.print(a);
    Serial.println(" Seconds remaining.");
    delay(1000);
    a --;
  }
}
