#include "mainwindow.h"
#include "mymodel.h"
#include "processesmodel.h"
#include <QTableView>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ProcessesModel processesModel;
    QTableView processesTableView;
    processesTableView.setModel(&processesModel);

    MyModel logModel;
    QListView logListView;
    logListView.setModel(&logModel);

    MainWindow window(nullptr,&processesTableView,&logListView);

    window.show();
    return a.exec();
}