/**
 * @file /include/pingfang_gui/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef pingfang_gui_QNODE_HPP_
#define pingfang_gui_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <string>
#include <QThread>
#include <geometry_msgs/Twist.h>
//#include <QStringListModel>


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace pingfang_gui {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
	bool init();
	bool init(const std::string &master_url, const std::string &host_url);
	void run();
	
public Q_SLOTS:
	void setSpeed(double linear,double angular);

	/*********************
	** Logging
	**********************/
//	enum LogLevel {
//	         Debug,
//	         Info,
//	         Warn,
//	         Error,
//	         Fatal
//	 };

//	QStringListModel* loggingModel() { return &logging_model; }
//	void log( const LogLevel &level, const std::string &msg);

Q_SIGNALS:
//	void loggingUpdated();
    void rosShutdown();

private:
	int init_argc;
	char** init_argv;
	ros::Publisher cmd_publisher;
	geometry_msgs::Twist cmd;
//    QStringListModel logging_model;
};

}  // namespace pingfang_gui

#endif /* pingfang_gui_QNODE_HPP_ */
