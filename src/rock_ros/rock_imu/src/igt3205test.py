from time import *
import i2c_itg3205

itg3205 = i2c_itg3205.i2c_itg3205(0)

while True:
	(itgready, dataready) = itg3205.getInterruptStatus()
	if dataready:
		print(itg3205.getDegPerSecAxes())
		print(itg3205.getDieTemperature())
		print(itg3205.getWhoAmI())
	sleep(1)
