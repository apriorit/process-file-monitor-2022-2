#include "pch.h"
#include "mainwindow.h"
#include "processesmodel.h"
#include "logmodel.h"
#include "processmonitor.h"
#include "processesseeker.h"
#include "pipeserver.h"
#include "logbuffer.h"

DWORD WINAPI ServerThreadStart(LPVOID pipeServer){
    ((PipeServer *)pipeServer)->startServerLoop();
    return 0;
}

int main(int argc, char *argv[])
{
    /*TODO
     * 1.Find cleaner way to kill server thread (probably overlaped will fix that)
     * 2.Refactor it for overlaped (before that I must make communication scheme and dependence)
    */
    QApplication a(argc, argv);

    LogBuffer logBuffer;
    LogModel logModel(nullptr, &logBuffer);

    ProcessesSeeker processSeeker;
    ProcessMonitor processMonitor(&processSeeker);
    ProcessesModel processesModel(nullptr,&processMonitor);

    PipeServer pipeServer(&processMonitor, &logBuffer);
    HANDLE serverThreadHandle = CreateThread(
                NULL,
                0,
                ServerThreadStart,
                &pipeServer,
                0,
                NULL);
    if(serverThreadHandle == NULL){
        exit(-1);
    }

    MainWindow window(nullptr, &processesModel, &logModel);
    window.show();
    a.exec();

    return 0;
}
