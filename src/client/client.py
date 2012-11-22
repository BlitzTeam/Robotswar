import serial

ser = serial.Serial('/dev/ttyACM0',115200,timeout=5)
ser.write("test")
ser.readline()
ser.close()
