#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QTableView>
#include <QListView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent, QTableView *processesTableView, QListView* logListView);

private:
    Ui::MainWindow m_ui;
    QTableView* processesTableView;
    QListView* logListView;

};
#endif // MAINWINDOW_H
