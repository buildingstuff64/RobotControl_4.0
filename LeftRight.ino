void rightUntil(){
  if (currentINSTRUCTION > 0) {fturn();}
  turnUntil(-turnspeed, turnspeed, 300);
}

void leftUntil(){
  if (currentINSTRUCTION > 0) {fturn();}
  turnUntil(turnspeed, -turnspeed, 300);
}

void turnAroundUntil(){
  if (currentINSTRUCTION > 0) {fturn();}
  turnUntil(-turnspeed, turnspeed, 2000);
}

void turnUntil(int l, int r, int e){
  rightMotor = r;
  leftMotor = l;
  updateMotors();
  char c = INSTRUCTIONS.charAt(currentINSTRUCTION);
  time_now = millis();
  while(millis() < time_now + 5000){
    scan(false);
    bool x = (irSensors == B010);
    if (c == 'R' || c == 'T'){
      x = (irSensors == B110);
    }
    if (c == 'L'){
      x = (irSensors == B011);
    }
    if ((millis() > time_now + e) && x){
      break;
    }
  }
  rightMotor = 0;
  leftMotor = 0;
  updateMotors();
  forward_and_reverse(l, r, 200);
  waitFor(250);
  NEXTINSTRUCTION = true;
}