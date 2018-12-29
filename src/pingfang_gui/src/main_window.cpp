/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/pingfang_gui/main_window.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace pingfang_gui {

using namespace Qt;


MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, qnode(argc,argv)
	,master_url("http://radxa.local:11311")
	,host_url("robot.local")
{
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.

	initSetting();
	setWindowIcon(QIcon(":/images/icon.png"));
    	QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));
	QObject::connect(this, SIGNAL(setRobotSpeed(double,double)),&qnode,SLOT(setSpeed(double,double)));

	//qnode.start();
}

MainWindow::~MainWindow() {}


void MainWindow::showNoMasterMessage() {
	QMessageBox msgBox;
	msgBox.setText("Couldn't find the ros master.");
	msgBox.exec();
    close();
}


void MainWindow::on_forwardBtn_clicked()
{
	double linear= ui.linearSpinBox->value();
	Q_EMIT setRobotSpeed(linear,0);
}

void MainWindow::on_backBtn_clicked()
{
	double linear= -ui.linearSpinBox->value();
	Q_EMIT setRobotSpeed(linear,0);
}

void MainWindow::on_leftBtn_clicked()
{
	double angular= ui.angularSpinBox->value();
	Q_EMIT setRobotSpeed(0,angular);
}

void MainWindow::on_rightBtn_clicked()
{
	double angular= -ui.angularSpinBox->value();
	Q_EMIT setRobotSpeed(0,angular);
}

void MainWindow::on_stopBtn_clicked()
{
	Q_EMIT setRobotSpeed(0,0);
}


void MainWindow::initSetting()
{
	if ( ! qnode.init(master_url.toStdString(),host_url.toStdString()) ) 
	{
		showNoMasterMessage();
	}
}



void MainWindow::closeEvent(QCloseEvent *event)
{
//	WriteSettings();
	QMainWindow::closeEvent(event);
}

}  // namespace pingfang_gui

