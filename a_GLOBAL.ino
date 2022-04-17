/* ======================================
                 Libraries
   ====================================== */

#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

/* ======================================
                 Variables
   ====================================== */

// LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Bluetooth module
static const uint8_t RX = 9;
static const uint8_t TX = 8;
boolean atmode = false;
bool constantSend = false;
int data = 0;

SoftwareSerial UNO(TX, RX); // Define Bluetooth Serial

// Heart-rate sensor
const uint8_t LOp = 11;
const uint8_t LOm = 10;

// BPM calculation
//int BPM = 0;
int beat_old = 0;
float beats[60];  // Used to calculate average BPM
int beatIndex;
float threshold = 500.0;  //Threshold at which BPM calculation occurs
boolean belowThreshold = true;
int j = 1;

// BPM calculation: Second Method
int UpperThreshold = 518;
int LowerThreshold = 490;
int reading = 0;
float BPM = 0.0;
bool IgnoreReading = false;
bool FirstPulseDetected = false;
unsigned long FirstPulseTime = 0;
unsigned long SecondPulseTime = 0;
unsigned long PulseInterval = 0;

// Time
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
const long sendInterval = 3500;

unsigned long currentMillisBPM = 0;
unsigned long previousMillisBPM = 0;
long simulateInterval = random(600, 1500);
/* ======================================
            Function Prototypes
   ====================================== */

// Initializes the heart-rate sensor.
void setup_sensor();

// #TODO
void setup_bluetooth();

// Initializes the LCD and outputs a verification message.
void setup_lcd();

// Control AT mode
void enter_at_mode();

// #TODO
void detect_pulse();

// #TODO
void send_bpm();

/*
   lcd_print(String message, int x, int y)

   Prints the user's message at the specified location x,y
   where x is the column and y is the line.
*/
void lcd_print(String message, int x, int y);

/* ======================================
                  Test
   ====================================== */
void pulseWithoutDelay(long interval);
