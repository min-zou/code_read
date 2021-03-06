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
#include "../include/pingfang_setgoals/main_window.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace pingfang_setgoals {

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, qnode(argc,argv)
	,master_url("http://radxa.local:11311")
	,host_url("robot.local")
	,amount(0)
	,goalsNum(0)
{
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.

	setWindowIcon(QIcon(":/images/icon.png"));
	times = (ui.countLine->text()).toInt();
	loop_rate =1/(ui.timeLine->text()).toInt();
	initSetting();
    	QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));
	QObject::connect(&qnode,SIGNAL(isSucceed(bool)),this,SLOT(isSucceed(bool)));
	QObject::connect(&qnode,SIGNAL(isFinished()),this,SLOT(on_runBtn_clicked()));
        QObject::connect(this,SIGNAL(sendGoals(double,double,double,double,double,double,double,double)),&qnode,SLOT(addGoals(double,double,double ,double,double,double,double,double)));
	QObject::connect(ui.countLine,SIGNAL(textChanged(QString)),this,SLOT(timesChanged(QString)));
	QObject::connect(ui.timeLine,SIGNAL(textChanged(QString)),this,SLOT(rateChanged(QString)));
	
}

MainWindow::~MainWindow() {}


void MainWindow::showNoMasterMessage() {
	QMessageBox msgBox;
	msgBox.setText("Couldn't find the ros master.");
	msgBox.exec();
    close();
}


void MainWindow::on_addPosBtn_clicked()
{	
	int currentrow = ui.posTable->currentRow();
	int count =ui.posTable->columnCount();	
	QString pos =ui.posTable->verticalHeaderItem(currentrow)->text();
	pos +=":";
	for(int column=0;column<count;column ++)
	{
		pos +=ui.posTable->item(currentrow,column)->text();
		pos += "  ";
		value[amount][column] = (ui.posTable->item(currentrow,column)->text()).toDouble();
	}
	ui.goalsList->addItem(pos);
	amount +=1;
		
}

void MainWindow::on_runBtn_clicked()
{
	if(times != 0)
	{
	
		if(goalsNum != amount)
		{
			for(int i=0;i<7;i++)
			{
				goals[i]=value[goalsNum][i];
			}
			
			goalsNum ++;
			if(goalsNum == amount)
			{
				times --;
				goalsNum =0;
				ui.countLine->setText(QString::number(times));
			}
			Q_EMIT sendGoals(goals[0],goals[1],goals[2],goals[3],goals[4],goals[5],goals[6],loop_rate);
		}
		
	}else{
		times =(ui.countLine->text()).toInt();
	}
	qnode.start();		
}

void MainWindow::on_deleteGoalsBtn_clicked()
{
	remove(ui.goalsList->currentRow());
	ui.goalsList->takeItem(ui.goalsList->currentRow());
	amount -=1;
}

void MainWindow::on_pauseBtn_clicked()
{
	qnode.terminate();
	qnode.wait();
}

void MainWindow::isSucceed(bool isSucceeded)
{
	if(isSucceeded)
	{
	QMessageBox msgBox;
	msgBox.setText("达到目标点！！！");
	msgBox.exec();
    	}else
	{
	QMessageBox msgBox;
	msgBox.setText("无法到达目标点！！！");
	msgBox.exec();
	}
}

void MainWindow::remove(int count)
{
	for(int i=count;i<amount;i++)
	{
		for(int j=0;j<7;j++)
		{
			value[i][j]=value[i+1][j];
		}
	}
}

void MainWindow::timesChanged(QString count)
{
	times=(count).toInt();
}

void MainWindow::rateChanged(QString rate)
{
	loop_rate=1/(rate).toDouble();
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
	QMainWindow::closeEvent(event);
}

}  // namespace pingfang_setgoals

