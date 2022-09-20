#include "mainwindow.h"
#include "mymodel.h"
#include <QTableView>
#include <QTreeView>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //MainWindow w;
    QTreeView tableView;
    MyModel model;
    tableView.setModel(&model);
    tableView.show();
    //w.show();
    return a.exec();
}
