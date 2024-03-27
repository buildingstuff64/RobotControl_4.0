float readDistance() {  // check if commented statemnets required or not
  //pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW);
  waitFor(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  waitFor(10);
  digitalWrite(TRIGGER_PIN, LOW);
  return getDistance(ECHO_PIN);
}

float getDistance(int PIN) {
  float t = pulseIn(PIN, HIGH);
  return t * 0.034 / 2;
}

bool isClose(float distance) {
  ULTChance += (readDistance() < distance) ? -1 : 1;
  ULTChance = constrain(ULTChance, -25, 25);
  return (ULTChance <= 0);
}