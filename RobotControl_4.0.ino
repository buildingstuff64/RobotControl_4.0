#include <Arduino_LSM6DS3.h>
#include <Servo.h>
#include <math.h>

#include <Wire.h>
#include <SPI.h>
#include "Adafruit_TCS34725.h"

#define MOT_A1_PIN 5
#define MOT_A2_PIN 6

#define MOT_B1_PIN 9  //change back to 9 and 10 if not using servo motor
#define MOT_B2_PIN 10

#define buzzer 11

#define doorpin 3
#define grippin 4

#define TRIGGER_PIN 8
#define ECHO_PIN 7

const int gripperOpen = 160;
const int gripperClosed = 90;

const int doorOpen = 130;
const int doorClosed = 40;

Servo door;
Servo gripper;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

boolean reverseL = 0;
boolean reverseR = 0;

float x, y, z;
float curx, cury, curz;

/* variables to keep track of current speed of motors */
int leftMotor = 0;
int rightMotor = 0;

int FORWARD_DUR = 540;
int LEFT_DUR = 1500;
int RIGHT_DUR = 1400;
const int turnspeed = 125;

int ir[3] = { A1, A2, A3 };
int IR[3] = { 0, 0, 0 };
int threshhold = 500;

bool onJunc = 0;
bool JuncChange = false;

char currentAction = 'N';
String INSTRUCTIONS = "";
int currentINSTRUCTION = 0;
bool NEXTINSTRUCTION = false;

int irSensors = B000;  // binary representation of the sensor reading. 1 when the sensor detects the line, 0 otherwise
int error = 0;         // A score to determine deviation from the line [-180 ; +180]. Negative means the robot is left of the line.
int errorLast = 0;
int maxSpeed = 200;

bool _pickup = false;
bool fint = false;
bool buzz = false;
int ULTChance = 25;

const int STOP_TIME = 500;
unsigned long stoptimer = STOP_TIME;
unsigned long lasttime = 0;
unsigned long time_now = 0;
int sonictimer = 0;

void setup() {

  digitalWrite(NINA_RESETN, HIGH);
  pinMode(MOT_A1_PIN, OUTPUT);
  pinMode(MOT_A2_PIN, OUTPUT);
  pinMode(MOT_B1_PIN, OUTPUT);
  pinMode(MOT_B2_PIN, OUTPUT);
  pinMode(buzzer, OUTPUT);
  // Start with drivers off, motors coasting.
  digitalWrite(MOT_A1_PIN, LOW);
  digitalWrite(MOT_A2_PIN, LOW);
  digitalWrite(MOT_B1_PIN, LOW);
  digitalWrite(MOT_B2_PIN, LOW);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  door.attach(doorpin);
  gripper.attach(grippin);

  gripper.write(gripperClosed);
  door.write(doorOpen);
  waitFor(2000);
  gripper.write(gripperOpen);
  waitFor(2000);
  gripper.write(gripperClosed);
  waitFor(2000);
  door.write(doorClosed);

  for (int i = 0; i < 3; i++) {
    pinMode(ir[i], INPUT);
  }

  SerialNina.begin(115200);
  Serial.begin(9600);
  while (!SerialNina)
    ;

  runTone(1000, 250, 5, 100);

  if (!IMU.begin()) {
    SerialNina.println("IMU Initilization Failed");
  }

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
  }
}

void loop() {
  stoptimer -= (millis() - lasttime);
  stoptimer = constrain(stoptimer, 0, STOP_TIME);
  sonictimer -= (millis() - lasttime);
  sonictimer = constrain(sonictimer, 0, 300);
  JuncChange = false;
  SerialRead();
  if (isClose(22) && (sonictimer <= 0 || sonictimer > 300)) {
    leftMotor = 0;
    rightMotor = 0;
    updateMotors();
    if (((int)round(stoptimer) % 20) == 0) { flipBuzzer(); }
    if (buzz) {
      tone(buzzer, 1000);
    } else {
      noTone(buzzer);
    }
    if (stoptimer <= 10 || stoptimer > STOP_TIME) {
      stoptimer = STOP_TIME;
      char c = INSTRUCTIONS.charAt(currentINSTRUCTION-1);
      if (c != 'R' || c != 'T' || c != 'L'){
        forwardUntil();
        fturn();
      }
      waitFor(3000);
      doInstructions(true);
      waitFor(100);
      SerialNina.print("REROUTE");
      SerialNina.println(currentINSTRUCTION);
      sonictimer = 300;
      noTone(buzzer);
      waitFor(1000);
      currentINSTRUCTION = 0;
      SerialRead();
    }
  } else {
    stoptimer = STOP_TIME;
    buzz = false;
    noTone(buzzer);
    scan(false);
    checkJunc();
    doInstructions((JuncChange || NEXTINSTRUCTION));
    updateAction();
    updateMotors();
  }
  lasttime = millis();
  waitFor(1);
}