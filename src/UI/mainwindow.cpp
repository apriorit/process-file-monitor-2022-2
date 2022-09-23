#include "pch.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent,ProcessesModel  *processesModel, MyModel* logModel)
    : QMainWindow(parent)
{
    m_ui = Ui::MainWindow();
    m_ui.setupUi(this);
    m_ui.ProcessesView->setModel(processesModel);
    m_ui.logView->setModel(logModel);
}
