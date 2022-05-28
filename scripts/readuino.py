# Listen to serial port and write contents into a file

# requires pySerial to be installed
from serial import Serial
import datetime

SERIAL_PORT = '/dev/ttyACM0'
BAUD_RATE = 9600  # In arduino, Serial.begin(baud_rate)
FILENAME = "data.csv"

output_file = open(FILENAME, "a+", encoding="utf-8")
ser = Serial(SERIAL_PORT, BAUD_RATE)
try:
    while True:
        now = datetime.datetime.now().strftime("%Y-%m-%d_%H:%M:%S")
        line = ser.readline()
        # ser.readline returns a binary, convert to string
        line = line.decode("utf-8")
        message = "Time,{0},ECG,{1}".format(now, line)
        print(message)
        output_file.write(message)
except Exception:
    output_file.close()
