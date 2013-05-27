import time
import math
import threading
from pypad import *

def writeDirection(connexion, x, y):
	direction = math.degrees(math.atan2(y, x))
	connexion.write("dir " + str(direction))

if __name__ == "__main__":
	xAxis = 1
	yAxis = 0
	noiseMin = 0.3
	aButton = 0
	gamepad = None
	xValue = 0.0
	yValue = 0.0
	maxTurnSpeed = 5.0
	
	connexion = serial.Serial('/dev/ttyACM0', 115200)
	
	while True:
		if gamepad != None:
			event = gamepad.getEvent()
			if event.eventType == 'axis' and event.index == xAxis and math.sqrt(event.value**2 + yValue**2) > noiseMin:
				xValue = -event.value
				writeDirection(connexion, xValue, yValue)
			elif event.eventType == 'axis' and event.index == yAxis and math.sqrt(event.value**2 + xValue**2) > noiseMin:
				yValue = event.value
				writeDirection(connexion, xValue, yValue)
			elif event.eventType == 'button' and event.index == aButton and event.value == True:
				connexion.write('move')			
				
			x = GamepadHandler.xValue
			y = GamepadHandler.yValue
			direction = direction + min(max(-GamepadHandler.maxTurnSpeed, math.degrees(math.atan2(y, x)) - direction), maxTurnSpeed)		
		else:
			time.sleep(0.5)
			gamepad = PyPad('/dev/input/js0')
			print("Joystick Enabled")


