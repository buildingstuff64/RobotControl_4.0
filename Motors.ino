void set_motor_pwm(int pwm, int IN1_PIN, int IN2_PIN) {
  if (pwm < 0) {  // reverse speeds
    analogWrite(IN1_PIN, -pwm);
    digitalWrite(IN2_PIN, LOW);
  } else if (pwm > 0) {  // stop or forward
    analogWrite(IN2_PIN, pwm);
    digitalWrite(IN1_PIN, LOW);
  } else if (pwm == 0) {
    analogWrite(IN1_PIN, 0);
    analogWrite(IN2_PIN, 0);
  }
}

void set_motor_currents(int pwm_A, int pwm_B) {
  set_motor_pwm(pwm_A, MOT_A1_PIN, MOT_A2_PIN);
  set_motor_pwm(pwm_B, MOT_B1_PIN, MOT_B2_PIN);
}

// ================================== FUNCTIONS =============================================

void forward_and_reverse(int pwm_A, int pwm_B, int duration) {
  set_motor_currents(0, 0);
  set_motor_currents(pwm_A, pwm_B);
  delay(duration);
  set_motor_currents(0, 0);
}

void updateMotors() {
  set_motor_currents(leftMotor, rightMotor);
}