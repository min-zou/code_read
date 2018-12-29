#!/usr/bin/python2.7

from time import *
import rospy
from sensor_msgs.msg import Imu,MagneticField
from math import sin,cos,pi
import i2c_itg3205,i2c_adxl345,i2c_hmc5883l

itg3205 = i2c_itg3205.i2c_itg3205(0)

adxl345 = i2c_adxl345.i2c_adxl345(0)

hmc5883l = i2c_hmc5883l.i2c_hmc5883l(0)
hmc5883l.setContinuousMode()
hmc5883l.setDeclination(9,54)


def GetImu():
	(itgready, dataready) = itg3205.getInterruptStatus()
	if dataready:
		(w_x, w_y, w_z) = itg3205.getDegPerSecAxes() 
	(acc_x, acc_y, acc_z) = adxl345.getAxes()
	(raw_x, raw_y, raw_z) = hmc5883l.getAxes()
	return (raw_x,raw_y,raw_z,w_x*pi/180,w_y*pi/180,w_z*pi/180,acc_x*9.8,acc_y*9.8,acc_z*9.8)


def Imupub():
	rate = rospy.get_param('~rate',10)
	base_frame_id = rospy.get_param('~base_frame_id','base_link')
	imu_frame_id = rospy.get_param('~imu_frame_id','imu_link')
	imu_pub = rospy.Publisher('imu/data_raw',Imu,queue_size = 5)
	mag_pub = rospy.Publisher('imu/mag',MagneticField,queue_size = 5)
	rospy.init_node('pingfang_Imu',anonymous=True)
	imu_rate = rospy.Rate(rate)
	imu_data = Imu()
	imu_mag = MagneticField()
	while not rospy.is_shutdown():
		(raw_x,raw_y,raw_z,w_x,w_y,w_z,acc_x,acc_y,acc_z) = GetImu()
		now = rospy.Time.now()
		imu_data.header.stamp = now
		imu_data.header.frame_id = imu_frame_id
		imu_data.angular_velocity.x = w_x
		imu_data.angular_velocity.y = w_y
		imu_data.angular_velocity.z = w_z
		imu_data.linear_acceleration.x = acc_x
		imu_data.linear_acceleration.y = acc_y
		imu_data.linear_acceleration.z = acc_z
		imu_mag.header.stamp = now
		imu_mag.header.frame_id = imu_frame_id
		imu_mag.magnetic_field.x = raw_x
		imu_mag.magnetic_field.y = raw_y
		imu_mag.magnetic_field.z = raw_z
		imu_pub.publish(imu_data)
		mag_pub.publish(imu_mag)		
		imu_rate.sleep()


if __name__ == '__main__':
	try:
		Imupub()
	except rospy.ROSInterruptException:
		pass
	


