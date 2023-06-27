#define HEAD_LED 9

bool isLight = true;

void setup() {
  pinMode(HEAD_LED, OUTPUT);
  digitalWrite(HEAD_LED, LOW);

}

void loop() {

  if (isLight) {
    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue++) {
      analogWrite(HEAD_LED, fadeValue);
      delay(160);
    }
    isLight = false;
    digitalWrite(HEAD_LED, LOW);
  }
}
