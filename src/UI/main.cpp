#include "pch.h"
#include "mainwindow.h"
#include "processesmodel.h"
#include "logmodel.h"
#include "processmonitor.h"
#include "processesseeker.h"
#include "pipeserver.h"
#include "logbuffer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LogBuffer logBuffer;
    LogModel logModel(nullptr, &logBuffer);

    ProcessesSeeker processSeeker;
    ProcessMonitor processMonitor(&processSeeker);
    ProcessesModel processesModel(nullptr,&processMonitor);

    PipeServer pipeServer(&processMonitor, &logBuffer);

    MainWindow window(nullptr, &processesModel, &logModel);
    window.show();
    a.exec();

    return 0;
}
