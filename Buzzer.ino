void runTone(int freq, int dur, int beeps, int bfreq){
  for (int i=0; i < beeps; i++){
      tone(buzzer, freq);
      waitFor(dur);
      noTone(buzzer);
      if (beeps>1){delay(bfreq);}
  }
}

void flipBuzzer(){
  buzz = buzz ? false : true;
}