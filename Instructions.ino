void updateAction() {
  if (INSTRUCTIONS.length() < 1)return;
  switch (currentAction) {
    case 'N':
      leftMotor = 0;
      rightMotor = 0;
      return;
    case 'F':
      forward();
      return;
    case 'R':
      rightUntil();
      return;
    case 'L':
      leftUntil();
      return;
    case 'P':
      pickup();
      return;
    case 'T':
      turnAroundUntil();
      return;
    case 'E':
      if (fint == true and INSTRUCTIONS.length() > 0){
        SerialNina.println("FIN");
        fint = false;
        INSTRUCTIONS = "";
        currentINSTRUCTION = 0;
        INSTRUCTIONS = "";
      }
    default:
      return;
  }
}

void doInstructions(bool next) {
  if (INSTRUCTIONS.length() < 1) return;
  if(next){
    currentINSTRUCTION += 1;
    SerialNina.print("NEXT");
    SerialNina.println(currentINSTRUCTION);
    if (currentINSTRUCTION >= INSTRUCTIONS.length()-1){
      SerialNina.println("FIN");
    }
    }
  char currentChar = INSTRUCTIONS.charAt(currentINSTRUCTION);
  if (currentChar == 'F') {
    currentAction = 'F';
  } else if (currentChar == 'R') {
    currentAction = 'R';
  } else if (currentChar == 'L') {
    currentAction = 'L';
  }else if (currentChar == 'P'){
    currentAction = 'P';
  }else if (currentChar == 'T'){
    currentAction = 'T';
  }
  else if (currentChar == 'E'){
    currentAction = 'E';
  }
  else if (currentChar = 'S'){
    currentAction = 'N';
    currentINSTRUCTION = 0;
    INSTRUCTIONS = "";
    //SerialNina.println("NextInstruction");
  }
  NEXTINSTRUCTION = false;
  //Serial.println(currentAction);
  
}

void checkJunc() {
  int x = false;
  if (IR[0] == 1 && IR[1] == 1 && IR[2] == 1) {
    x = true;
  }
  if (x != onJunc) {
    flipJuncState();
  }
  for (int i = 0; i < 3; i++) {
    //Serial.print(IR[i]);
    //Serial.print(" :");
  }
}

void flipJuncState() {
  onJunc = !onJunc;
  if (onJunc == true) JuncChange = true;
}