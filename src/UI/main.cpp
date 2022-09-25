#include "pch.h"
#include "mainwindow.h"
#include "processesmodel.h"
#include "processmonitor.h"
#include "processesseeker.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ProcessesSeeker processSeeker;

    ProcessMonitor processMonitor(&processSeeker);
    ProcessesModel processesModel(nullptr,&processMonitor);

    MainWindow window(nullptr,&processesModel);
    window.show();
    return a.exec();
}
