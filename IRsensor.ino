void scan(bool debug) {
  irSensors = B000;
  for (int i = 0; i < 3; i++) {
    int x = analogRead(ir[i]);
    IR[i] = (x >= threshhold) ? 1 : 0;
    int b = 2 - i;
    irSensors = irSensors + (IR[i] << b);
  }
}