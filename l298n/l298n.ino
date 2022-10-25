int ENA = 13; //D7
int IN1 = 5; //D1
int IN2 = 4; //D2

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void loop() {
  for (int i = 0; i <= 10; i++){
    makan();
  }
}

void makan() {
  analogWrite(ENA, 50);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(2000);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

