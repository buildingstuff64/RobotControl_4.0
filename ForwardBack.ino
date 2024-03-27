void forward() {
  errorLast = error;
  switch (irSensors) {
    case B000: // no sensor detects the line
      if (errorLast < 0) {
        error = -200;
      }
      else if (errorLast > 0) {
        error = 200;
      }
      break;
    case B100: // left sensor on the line
      error = -200;
      break;
    case B110:
      error = -150;
      break;
    case B010:
      error = 0;
      break;
    case B011:
      error = 150;
      break;
    case B001: // right sensor on the line
      error = 200;
      break;
    case B111:
      return;
    default:
      error = errorLast;
  }
  if (error >= 0) {
    leftMotor = maxSpeed;
    rightMotor = maxSpeed - error;
  }
  else if (error < 0) {
    leftMotor = maxSpeed + error;
    rightMotor = maxSpeed;
  }
}

void fturn(){
  forward_and_reverse(turnspeed, turnspeed, FORWARD_DUR);
}

void forwardUntil(){
  time_now = millis();
  while(millis() < time_now + 2000){
        scan(false);
        if (irSensors == B111 && (millis() > time_now + 300)) {break;}
        forward();
        updateMotors();
  }
  leftMotor = 0;
  rightMotor = 0;
  updateMotors();
}

void forwardfor(int t){
  time_now = millis();
  while(millis() < time_now + t){
        scan(false);
        forward();
        updateMotors();
  }
  leftMotor = 0;
  rightMotor = 0;
  updateMotors();
}switch
