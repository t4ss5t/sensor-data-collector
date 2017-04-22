int ledPin = 13;
int inPin = 7;
int val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(inPin, INPUT);
}

void loop(){
  val = digitalRead(inPin);
  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.print("{'event':'button_pressed'}");
    Serial.println();
    delay(2000);
  }
  digitalWrite(ledPin, LOW);
}
