#include "pch.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent,ProcessesModel  *processesModel)
    : QMainWindow(parent)
{
    m_ui = Ui::MainWindow();
    m_ui.setupUi(this);
    m_ui.ProcessesView->setModel(processesModel);
}
