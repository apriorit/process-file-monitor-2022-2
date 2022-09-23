#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include "processesmodel.h"
#include "mymodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent,ProcessesModel  *processesModel, MyModel* logModel);

private:
    Ui::MainWindow m_ui;
};
#endif // MAINWINDOW_H
