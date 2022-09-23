#include "pch.h"
#include "mainwindow.h"
#include "mymodel.h"
#include "processesmodel.h"
#include "processesseeker.h"


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

    ProcessesSeeker ps;
    ps.getSystemProcesses();

    window.show();
    return a.exec();

}
