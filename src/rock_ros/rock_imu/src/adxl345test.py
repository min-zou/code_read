from time import *
import i2c_adxl345
adxl345 = i2c_adxl345.i2c_adxl345(0)
while True:
	print(adxl345)
	#print(adxl345.getRawAxes())
	sleep(1)
