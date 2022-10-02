#include "pch.h"
#include "mainwindow.h"
#include "processesmodel.h"
#include "logmodel.h"
#include "processmonitor.h"
#include "processesseeker.h"
#include "pipeserver.h"

int main(int argc, char *argv[])
{
    PipeServer();
    QApplication a(argc, argv);

    LogModel logModel;

    ProcessesSeeker processSeeker;
    ProcessMonitor processMonitor(&processSeeker);
    ProcessesModel processesModel(nullptr,&processMonitor);

    MainWindow window(nullptr, &processesModel, &logModel);
    window.show();
    return a.exec();
}
