/**
 * @file /include/pingfang_gui/main_window.hpp
 *
 * @brief Qt based gui for pingfang_gui.
 *
 * @date November 2010
 **/
#ifndef pingfang_gui_MAIN_WINDOW_H
#define pingfang_gui_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace pingfang_gui {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();


	void initSetting();

	void closeEvent(QCloseEvent *event); // Overloaded function
	void showNoMasterMessage();

public Q_SLOTS:

	void on_forwardBtn_clicked();
	void on_backBtn_clicked();
	void on_leftBtn_clicked();
	void on_rightBtn_clicked();
	void on_stopBtn_clicked();

Q_SIGNALS:
	void setRobotSpeed(double linear,double angular);


private:
	Ui::MainWindowDesign ui;
	QString master_url;
	QString host_url;
	QNode qnode;
};

}  // namespace pingfang_gui

#endif // pingfang_gui_MAIN_WINDOW_H
