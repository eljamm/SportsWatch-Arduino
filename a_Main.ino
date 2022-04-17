/*
 * Code that runs once
 */
void setup() {
  setup_bluetooth();
  setup_sensor();
}

/*
 * Code that loops
 */
void loop() {
  // Get current time in milliseconds
  get_time();

  // --------------------------------------

  // Check for if connection is initialized
  if (UNO.available()) {
    data = UNO.read();
    // Start signal received
    if (data == '*') {
      constantSend = true;  // Start sending data
    }
    data = 0;
  }

  // --------------------------------------

  // Read pulse from sensor and Calculate BPM
  read_pulse();

  // Calculate BPM from simulated data
  //simulateBPM();

  generate();

  // Send BPM value to bluetooth module
  send_bpm();
}
