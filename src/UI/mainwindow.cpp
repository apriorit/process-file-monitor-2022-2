#include "pch.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent,ProcessesModel  *processesModel, LogModel *logModel)
    : QMainWindow(parent),
      logModel{logModel}
{
    m_ui = Ui::MainWindow();
    m_ui.setupUi(this);
    m_ui.ProcessesView->setModel(processesModel);
    m_ui.LogView->setModel(logModel);
}

void MainWindow::on_pushButton_clicked()
{
    logModel->clearData();
}

