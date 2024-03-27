void waitFor(int x){
  time_now = millis();
  while(millis() < time_now + x){
    //wait for x milliseconds
  }
}