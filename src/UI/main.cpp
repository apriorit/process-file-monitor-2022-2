#include "pch.h"
#include "mainwindow.h"
#include "mymodel.h"
#include "processesmodel.h"

#include "processesseeker.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProcessesModel processesModel;
    MyModel logModel;

    MainWindow window(nullptr,&processesModel,&logModel);
    ProcessesSeeker seeker;
    auto y = seeker.getSystemProcesses();
    for(auto x : y){
        qDebug() << x.Name;
    }
    //window.show();
    //return a.exec();
}
