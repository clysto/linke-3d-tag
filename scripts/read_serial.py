import serial

ser = serial.Serial("/dev/tty.usbmodem144303")  # open serial port
print(ser.name)  # check which port was really used

s = ser.read(10)
print(s)
