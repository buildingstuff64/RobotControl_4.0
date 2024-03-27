void SerialRead() {
  if (SerialNina.available()) {
    String command = SerialNina.readStringUntil('\n');
    command.trim();
    if (command.substring(0, 4) == "T#DO") {
      door.write(doorOpen);
      SerialNina.println("Door OPEN");
    }
    if (command.substring(0, 4) == "T#DC") {
      door.write(doorClosed);
      SerialNina.println("Door CLOSE");
    }
    if (command.substring(0, 4) == "T#GO") {
      gripper.write(gripperOpen);
      SerialNina.println("Gripper OPEN");
    }
    if (command.substring(0, 4) == "T#GC") {
      gripper.write(gripperClosed);
      SerialNina.println("Gripper CLOSE");
    }
    if (command.substring(0, 4) == "T#MT"){
      SerialNina.println("Motor Test");
      forward_and_reverse(maxSpeed, maxSpeed, 5000);
      delay(1000);
      forward_and_reverse(-maxSpeed, maxSpeed, 5000);
      delay(1000);
      forward_and_reverse(maxSpeed, -maxSpeed, 5000);
      delay(1000);
      forward_and_reverse(-maxSpeed, -maxSpeed, 5000);
      delay(1000);
    }
    if (command.substring(0, 4) == "T#LT"){
      for(int i=0; i < 100; i++){
        scan(true);
        delay(500);
      }
    }
    if (command.substring(0, 2) == "I#"){
      command.remove(0, 2);
      SerialNina.println(command);
      INSTRUCTIONS = decode(command);
      currentINSTRUCTION = 0;
      fint = true;
    }
    if (command.substring(0, 5) == "C#get"){
      SerialNina.println(getColor());
    }
    if (command.substring(0, 5) == "T#COL"){
      SerialNina.println(getColor());
    }
    if (command.substring(0, 5) == "T#HUE"){
      SerialNina.println(getHue());
    }
    if (command.substring(0, 4) == "T#IR"){
      SerialNina.println("RACK SETUP INIT");
      door.write(180);
      delay(5000);
      door.write(doorOpen);
      delay(2000);
      door.write(doorClosed);
    }
    //if (command != "") { SerialNina.println(command); }
  }
}

String decode(String cp) {
  size_t len = cp.length();
  String dp = "";
  int count = 0;
  for (size_t i = 0; i < len; ++i) {
    char currentChar = cp.charAt(i);
    if (currentChar == 'F') {
      if (i + 1 < len && cp.charAt(i + 1) >= '0' && cp.charAt(i + 1) <= '9') {
        count = cp.charAt(i + 1) - '0';
        i++;
      } else {
        count = 1;
      }

      for (int j = 0; j < count; ++j) {
        dp += "F";
      }
    } else {
      dp += currentChar;
    }
  }
  dp += '\n';
  return dp;
}