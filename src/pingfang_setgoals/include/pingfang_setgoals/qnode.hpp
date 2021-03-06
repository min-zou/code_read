/**
 * @file /include/pingfang_setgoals/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef pingfang_setgoals_QNODE_HPP_
#define pingfang_setgoals_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <string>
#include <QThread>
//#include <QStringListModel>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace pingfang_setgoals {

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
	void addGoals(double px,double py,double pz ,double ox,double oy,double oz,double ow,double loop_rate);

Q_SIGNALS:
   	void rosShutdown();
	void isSucceed(bool isSucceeded);
	void isFinished();

private:
	int init_argc;
	char** init_argv;
	move_base_msgs::MoveBaseGoal goal;
	double rate;

};

}  // namespace pingfang_setgoals

#endif /* pingfang_setgoals_QNODE_HPP_ */
