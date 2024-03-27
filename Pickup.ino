void pickup(){
  //SerialNina.println("PICKUP");
    if (_pickup){
      set_motor_currents(0, 0);
      forwardUntil();
      fturn();
      door.write(doorOpen);
      waitFor(750);
      gripper.write(gripperOpen);
      waitFor(1000);
      door.write(doorClosed);
      waitFor(250);
      door.write(doorOpen);
      waitFor(250);
      door.write(doorClosed);
      _pickup = false;
    }
    else if (!_pickup){
      set_motor_currents(0, 0);
      char c = INSTRUCTIONS.charAt(currentINSTRUCTION-1);
      bool x = ((c == 'R') || (c == 'L') || (c == 'T'));
      waitFor(1000);
      gripper.write(gripperOpen);
      waitFor(1000);
      door.write(doorOpen);
      waitFor(1000);
      if (!x) { forwardfor(900); }
      else { forwardfor(260); }
      gripper.write(gripperClosed);
      waitFor(1000);
      door.write(doorClosed);
      waitFor(1000);
      waitFor(1000);
      forwardUntil();
      fturn();
      _pickup = true;
    }
    NEXTINSTRUCTION = true;
}