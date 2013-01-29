import pygame
import time
from pygame.locals import *
import serial
import socket

min_value =  0.5 #avoid noise
refresh_rate = 0.01
speedAxis = 1
rotationAxis = 0
host = '192.168.0.50'
port = 12345
count = 0

def main():
    logo()
    pygame.init()

    #global sock
    #sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #sock.connect((host, port))
    global ser
    ser = serial.Serial('/dev/ttyACM0', 1000000)
    
    if pygame.joystick.get_count() == 0:
        print("No gamepad detected!")
    else:
        pad = pygame.joystick.Joystick(0)
        pad.init()
        print("Gamepad found: " + pad.get_name())
        

        if pad.get_numaxes() < 2:
            print("Invalid gamepad")
        else:
            print("valid gamepad: " + str(pad.get_numaxes()) + " axes")

            while True:
                pygame.event.pump()
                speed = noiseRemover(-pad.get_axis(speedAxis))
                rotation = noiseRemover(pad.get_axis(rotationAxis))
                sendPaquet(speed, rotation)           
                time.sleep(refresh_rate)

def noiseRemover(value):
    return 1 if value > min_value else -1 if value < -min_value else 0

def packetFormater(speed, rotation):
    return str(speed + 1) + str(rotation + 1) + '\r'

def sendPaquet(speed, rot):
    global count
    count += 1
    currentPacket = packetFormater(speed, rot)
    print(str(count) + ' ' + currentPacket)
    ser.write(currentPacket)
    #sock.send(packetFormater(speed, rot).encode())

def logo():
    print("  _    _ _ _       ___                              _         ")
    print(" | |__| (_) |_ ___/ __|___ _ __  _ __  __ _ _ _  __| |___ _ _ ")
    print(" | '_ \ | |  _|_ / (__/ _ \ '  \| '  \/ _` | ' \/ _` / -_) '_|")
    print(" |_.__/_|_|\__/__|\___\___/_|_|_|_|_|_\__,_|_||_\__,_\___|_|  ")
    print("")

if __name__=="__main__":
    main()

#UP: axis_id = 1, value = -1
#DOWN: axis_id = 1, value = 1
#LEFT: axis_id = 0, value = -1
#RIGHT: axis_id = 0, value = 1
