#include "mainwindow.h"
#include "mymodel.h"
#include <QTableView>
#include <QTreeView>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyModel processesModel;
    QTableView processesTableView;
    processesTableView.setModel(&processesModel);

    MyModel logModel;
    QListView logListView;
    logListView.setModel(&logModel);

    MainWindow window(nullptr,&processesTableView,&logListView);
    QTreeView tableView;

    window.show();
    return a.exec();
}
