#pragma once

#include "ui_mainwindow.h"
#include "processesmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent,ProcessesModel  *processesModel);

private:
    Ui::MainWindow m_ui;
};
