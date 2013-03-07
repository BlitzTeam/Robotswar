import serial

ser = serial.Serial('/dev/ttyACM0',115200,timeout=5)
ser.write("1 512\n")
ser.readline()
ser.close()
