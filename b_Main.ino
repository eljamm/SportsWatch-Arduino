// Code that runs once
void setup() {
  //setup_lcd();
  setup_bluetooth();
  setup_sensor();
}

// Code that loops
void loop() {
  currentMillis = millis();
  currentMillisBPM = currentMillis;

  if (UNO.available()) {
    data = UNO.read();
    // Initiated connection
    if (data == '*') {
      constantSend = true;
    }
    data = 0;
  }

  //enter_at_mode();

  //read_pulse();

  simulateBPM();

  send_bpm();
}
