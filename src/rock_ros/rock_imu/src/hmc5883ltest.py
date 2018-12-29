
from time import *
import i2c_hmc5883l
hmc5883l = i2c_hmc5883l.i2c_hmc5883l(0)
hmc5883l.setContinuousMode()
hmc5883l.setDeclination(9,54)
while True:
	print(hmc5883l)

	sleep(1)
