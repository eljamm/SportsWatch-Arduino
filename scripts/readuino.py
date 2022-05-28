# Listen to serial port and write contents into a file

# requires pySerial to be installed
from serial import Serial

SERIAL_PORT = '/dev/ttyACM0'
BAUD_RATE = 9600  # In arduino, Serial.begin(baud_rate)
FILENAME = "output.txt"

output_file = open(FILENAME, "w+", encoding="utf-8")
ser = Serial(SERIAL_PORT, BAUD_RATE)
try:
    while True:
        line = ser.readline()
        # ser.readline returns a binary, convert to string
        line = line.decode("utf-8")
        print(line)
        output_file.write(line)
except KeyboardInterrupt():
    output_file.close()
