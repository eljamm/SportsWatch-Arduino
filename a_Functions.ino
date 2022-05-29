/* ======================================
                   Setup
   ====================================== */

void setup_sensor() {
  pinMode(LOp, INPUT); // Setup for leads off detection LO +
  pinMode(LOm, INPUT); // Setup for leads off detection LO -
}

// --------------------------------------

void setup_lcd() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("LCD is Ready.");      // welcome message
  delay(3000);
  lcd.clear();
}

// --------------------------------------

void setup_bluetooth() {
  pinMode(7, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode

  if (atmode == true) {
    digitalWrite(7, HIGH);
  } else {
    digitalWrite(7, LOW);
  }

  // Power the module
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);

  // Initialize the serial communication
  Serial.begin(9600);
  UNO.begin(9600);

  //Serial.println("Ready to receive.");
}

/* ======================================
                   Sensor
   ====================================== */

/*
   Deprecated
*/
void detect_pulse() {
  if ((digitalRead(LOp) == 1) || (digitalRead(LOm) == 1)) {
    Serial.println('!');  // Indicated that the Leads are Off
  }
  else {
    //Serial.println(analogRead(A0));  // For debugging (for now)
    if (analogRead(A0) > threshold && belowThreshold == true)
    {
      calculateBPM();
      belowThreshold = false;
    }
    else if (analogRead(A0) < threshold)
    {
      belowThreshold = true;
    }
  }
  if (currentMillisBPM - previousMillisBPM >= sendInterval) {
    // save the last time you blinked the LED
    previousMillisBPM = currentMillisBPM;

    Serial.print("BPM:\t");
    Serial.println(BPM);
  }
  //delay(1);
}

// --------------------------------------

/*
   Deprecated
*/
void calculateBPM () {
  int beat_new = millis();            // get the current millisecond
  int diff = beat_new - beat_old;     // find the time between the last two beats
  float currentBPM = 60000 / diff;    // convert to beats per minute
  beats[beatIndex] = currentBPM;      // store to array to convert the average
  float total = 0.0;
  for (int i = 0; i < j; i++) {
    total += beats[i];
  }
  BPM = int(total / j);
  beat_old = beat_new;
  if (j < 60) {
    j++;
  }
  beatIndex = (beatIndex + 1) % 60;  // cycle through the array instead of using FIFO queue
}

// --------------------------------------

void read_pulse() {
  reading = analogRead(0);  // Get value from sensor
  Serial.println(reading);  // If you want to visualize it with serial plotter

  // Heart beat leading edge detected.
  if (reading > UpperThreshold && IgnoreReading == false) {
    if (FirstPulseDetected == false) {
      FirstPulseTime = millis();
      FirstPulseDetected = true;
    }
    else {
      SecondPulseTime = millis();
      PulseInterval = SecondPulseTime - FirstPulseTime;
      FirstPulseTime = SecondPulseTime;
    }
    IgnoreReading = true;
  }

  // Heart beat trailing edge detected.
  if (reading < LowerThreshold) {
    IgnoreReading = false;
  }

  BPM = (1.0 / PulseInterval) * 60.0 * 1000;
}

// --------------------------------------

void simulateBPM() {
  if (currentMillisBPM - previousMillisBPM >= simulateInterval) {
    PulseInterval = currentMillisBPM - previousMillisBPM;
    previousMillisBPM = currentMillisBPM;

    simulateInterval = random(600, 1200);

    //Serial.print("Interval:\t");
    //Serial.println(simulateInterval);

    BPM = (1.0 / PulseInterval) * 60.0 * 1000;
  }
}

/* ======================================
                    LCD
   ====================================== */

void lcd_print(String message, int x, int y) {
  lcd.clear();
  lcd.setCursor(x, y);
  lcd.print(message);
}

/* ======================================
                 Bluetooth
   ====================================== */

void enter_at_mode() {
  if (atmode == true) {
    // Enter AT mode
    Serial.println("Enter AT commands:");
    UNO.begin(38400);
    while (true) {
      // Keep reading from HC-05 and send to Arduino Serial Monitor
      if (UNO.available())
        Serial.write(UNO.read());

      // Keep reading from Arduino Serial Monitor and send to HC-05
      if (Serial.available())
        UNO.write(Serial.read());
    }
  }
}

// --------------------------------------

void print_bpm() {
  UNO.print('#');
  UNO.print(BPM);

  UNO.println();
  UNO.flush();
}

void send_bpm() {
  if (currentMillis - previousMillis >= sendInterval && constantSend == true) {
    previousMillis = currentMillis;

    //Serial.print(reading);
    //Serial.print("\t");
    //Serial.print(PulseInterval);
    //Serial.print("\t");
    //Serial.print(BPM);
    //Serial.println(" BPM");
    //Serial.flush();

    print_bpm();
  }
}

void print_ecg() {
    for (int i = 0; i < ecgIndex; i++) {
      Serial.println(ecg[i]);
    }
    Serial.flush();
}

void send_ecg() {
  if (currentMillisECG - previousMillisECG >= sendIntervalECG) {
    previousMillisECG = currentMillisECG;

    print_ecg();
  }
}

/* ======================================
                  Test
   ====================================== */

void generate() {
  readingECG = analogRead(0);
  //readingECG = random(300, 600);

  ecg[ecgIndex] = readingECG;

  ecgIndex = (ecgIndex + 1) % 10;  // cycle through the array instead of using FIFO queue
}

void get_time() {
  currentMillis = millis();
  currentMillisBPM = currentMillis;
  currentMillisECG = currentMillis;
}
